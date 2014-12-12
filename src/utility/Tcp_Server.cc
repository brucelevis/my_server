/*
 * Tcp_Server.cc
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#include "Tcp_Server.h"
#include "Reactor.h"
#include "Acceptor.h"
#include "Sock_Acceptor.h"
#include "Net_Define.h"
#include "Log.h"
#include "Tcp_Connection.h"
#include "Msg_Block.h"
#include "Nonblock_Worker.h"
#include "Block_Worker.h"

Tcp_Server::Tcp_Server(void) {
}

Tcp_Server::~Tcp_Server(void) {
}

void Tcp_Server::accept_loop(void) {
	while (1) {
		accept_reactor_->handle_event();
	}
}

void Tcp_Server::scream_loop(void) {
	scream_worker_->set_loop_thrid();
	scream_reactor_->set_wait_ms(10);
	while (1) {
		scream_worker_->process();
		scream_reactor_->handle_event();
	}
}

void Tcp_Server::accept_handle(int sock_fd) {
	auto conn = std::make_shared<Tcp_Connection>();
	conn->set_fd(sock_fd);
	conn->enable(IPC_SAP::NONBLOCK);
	// conn->set_tcpnodelay(true);
	conn->set_reactor(scream_reactor_.get());

	conn->set_recv_cb(recv_cb_);
	conn->set_close_cb(close_cb_);

	scream_worker_->push([conn, this] {
		conn_holder_.insert(conn);
		scream_reactor_->register_handler(conn, Event::READ_WRITE_MASK);
	});
}

void Tcp_Server::send_to_client(const int cid, Msg_Block &&msg) {
	SConn conn = conn_holder_.find(cid);
	if (conn) {
		conn->push_send_msg(std::move(msg));
	}
}

void Tcp_Server::drop_handle(int cid) {
	rec_log(Log::LVL_DEBUG, "cid %d drop handle", cid);
	conn_holder_.erase(cid);
}

void Tcp_Server::init(const int listen_port, const int max_listen, const Recv_Callback &recv_cb, const Close_Callback &close_cb) {
	// reactor
	accept_reactor_.reset(new Reactor);
	accept_reactor_->init(1);
	scream_reactor_.reset(new Reactor);
	scream_reactor_->init(DEFAULT_MAX_EVENT);

	// acceptor
	acceptor_.reset(new Acceptor(accept_reactor_.get()));
	Sock_Acceptor *sock_acceptor = new Sock_Acceptor;
	sock_acceptor->init(AF_INET, ACCEPT_SOCK_TYPE, 0, listen_port, max_listen);
	using namespace std::placeholders;
	acceptor_->set_cid(0);
	acceptor_->init(sock_acceptor, std::bind(&Tcp_Server::accept_handle, this, _1));

	// worker
	scream_worker_.reset(new Nonblock_Worker);

	recv_cb_ = recv_cb;
	close_cb_ = close_cb;
}

void Tcp_Server::start(void) {
	accept_thr_ = std::thread(std::bind(&Tcp_Server::accept_loop, this));
	accept_thr_.detach();
	scream_thr_ = std::thread(std::bind(&Tcp_Server::scream_loop, this));
	scream_thr_.detach();
}

