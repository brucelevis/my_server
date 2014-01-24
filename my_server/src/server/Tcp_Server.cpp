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

Tcp_Server::Tcp_Server(void) : cid_svc_map_(2048) {

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

	using namespace std::placeholders;
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
	}
}

void Tcp_Server::drop_handle(int cid) {
	SSvc svc;
	cid_svc_map_.find_obj(cid, svc);
	if (svc) {
		svc->fini();
		cid_svc_map_.erase_obj(cid);
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

	cid_svc_map_.set_obj_cb(sended_sum_);
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
	while (1) {
		cid_svc_map_.foreach_cb();
		if (0 == sended_sum_.sended_sum_) {
			::usleep(100);	// todo remove it
		}
	}
}

void Tcp_Server::Sended_Sum::operator()(SSvc &svc) {
	if (svc) {
		svc->handle_output();
	}
}

