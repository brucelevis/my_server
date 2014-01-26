/*
 * Tcp_Server.cpp
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#include "Tcp_Server.h"
#include "Reactor.h"
#include "Repo_Factory.h"
#include "Acceptor.h"
#include "Sock_Acceptor.h"
#include "Net_Define.h"
#include "Log.h"
#include "Svc.h"
#include "Msg_Block.h"

Tcp_Server::Tcp_Server(void) : cid_svc_map_(2048), cond_(lock_), busy_cid_(2048) {

}

Tcp_Server::~Tcp_Server(void) {
}

void Tcp_Server::accept_loop(void) {
	while (1) {
		accept_reactor_->handle_event();
	}
}

void Tcp_Server::recv_loop(void) {
	while (1) {
		input_reactor_->handle_event();
	}
}

void Tcp_Server::accept_handle(int sock_fd) {
	auto svc = std::make_shared<Svc>();
	svc->set_fd(sock_fd);
	svc->set_reactor(input_reactor_.get());

	svc->set_recv_cb(recv_cb_);
	svc->set_close_cb(close_cb_);

	cid_svc_map_.insert_obj(svc);
	input_reactor_->register_handler(svc.get(), Event::READ_MASK);
}

void Tcp_Server::send_to_client(const int cid, Msg_Block &&msg) {
	SSvc svc;
	cid_svc_map_.find_obj(cid, svc);
	if (svc) {
		svc->push_send_msg(std::move(msg));
		Mutex_Guard<Thread_Mutex> guard(lock_);
		busy_cid_.insert(cid);
		cond_.notify();
	}
}

void Tcp_Server::drop_handle(int cid) {
	{
		Mutex_Guard<Thread_Mutex> guard(lock_);
		busy_cid_.erase(cid);
	}
	SSvc svc = cid_svc_map_.erase_obj(cid);
	if (svc) {
		svc->fini();
	}
}

void Tcp_Server::init(const int listen_port, const int max_listen, const Recv_Callback &recv_cb, const Close_Callback &close_cb) {
	// reactor
	accept_reactor_.reset(new Reactor);
	accept_reactor_->init();
	input_reactor_.reset(new Reactor);
	input_reactor_->init();

	// repo
	repo_fac_.reset(new Repo_Factory);
	repo_fac_->init();

	// acceptor
	acceptor_.reset(new Acceptor(accept_reactor_.get()));
	Sock_Acceptor *sock_acceptor = new Sock_Acceptor;
	sock_acceptor->init(AF_INET, ACCEPT_SOCK_TYPE, 0, listen_port, max_listen);
	using namespace std::placeholders;
	acceptor_->init(sock_acceptor, std::bind(&Tcp_Server::accept_handle, this, _1));

	recv_cb_ = recv_cb;
	close_cb_ = close_cb;
}

void Tcp_Server::start(void) {
	accept_thr_ = std::thread(std::bind(&Tcp_Server::accept_loop, this));
	accept_thr_.detach();
	input_thr_ = std::thread(std::bind(&Tcp_Server::recv_loop, this));
	input_thr_.detach();
	send_thr_ = std::thread(std::bind(&Tcp_Server::send_loop, this));
	send_thr_.detach();
}

void Tcp_Server::send_loop(void) {
	SSvc svc;
	while (1) {
		Mutex_Guard<Thread_Mutex> guard(lock_);
		while (busy_cid_.empty()) {
			cond_.wait();
		}
		for (auto it = busy_cid_.begin(); it != busy_cid_.end(); ) {
			cid_svc_map_.find_obj(*it, svc);
			bool need_delete = true;
			if (svc) {
				if (SUCCESS != svc->handle_output()) {
					need_delete = false;
				}
			}
			if (need_delete) {
				it = busy_cid_.erase(it);
			} else {
				++it;
			}
		}
	}
}
