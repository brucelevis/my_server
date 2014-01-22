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

Tcp_Server::Tcp_Server(void) : max_cid_(min_cid) {

}

Tcp_Server::~Tcp_Server(void) {
}

void Tcp_Server::handle_input_event(void) {
	while (1) {
		reactor_->handle_event();
	}
}

void Tcp_Server::accept_handle(Reactor *reactor, int sock_fd) {
	Svc *svc = repo_fac_->pop_svc();
	svc->set_fd(sock_fd);
	svc->set_reactor(reactor);

	using namespace std::placeholders;
	svc->set_recv_cb(recv_cb_);
	svc->set_close_cb(std::bind(&Tcp_Server::drop_handle, this, _1));

	int cid = generate_cid();
	svc->set_cid(cid);
	inused_[cid] = svc;
	reactor->register_handler(svc, Event::READ_MASK);
}

void Tcp_Server::drop_handle(int cid) {
	Svc *svc = find_svc(cid);
	if (svc) {
		unused_.insert(cid);
		inused_.erase(cid);
		repo_fac_->push_svc(svc);
		if (close_cb_) {
			close_cb_(cid);
		}
	} else {
		rec_log(Log::LVL_ERROR, "svc cid %d not exist.", cid);
	}
}

void Tcp_Server::init(int listen_port, int max_listen) {
	// reactor
	reactor_.reset(new Reactor);
	reactor_->init();

	// repo
	repo_fac_.reset(new Repo_Factory);
	repo_fac_->init();

	// acceptor
	acceptor_.reset(new Acceptor(reactor_.get()));
	Sock_Acceptor *sock_acceptor = new Sock_Acceptor;
	sock_acceptor->init(AF_INET, ACCEPT_SOCK_TYPE, 0, listen_port, max_listen);
	using namespace std::placeholders;
	acceptor_->init(sock_acceptor, std::bind(&Tcp_Server::accept_handle, this, _1, _2));
}

void Tcp_Server::start(void) {
	input_thr_ = std::thread(std::bind(&Tcp_Server::handle_input_event, this));
	input_thr_.detach();
}
