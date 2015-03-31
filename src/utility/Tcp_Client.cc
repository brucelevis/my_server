/*
 * Tcp_Client.cc
 *
 *  Created on: Apr 23, 2014
 *	  Author: "enjolras"
 */

#include "Tcp_Client.h"
#include "Define.h"
#include "Tcp_Connection.h"
#include "Sock_Connector.h"
#include "Net_Define.h"
#include "Reactor.h"
#include "Log.h"
#include "Msg_Block.h"

Tcp_Client::Tcp_Client(void) : port_(nullfd) {

}

Tcp_Client::~Tcp_Client(void) {
}

int Tcp_Client::init(const std::string &ip, const int port, const Recv_Callback& recv_cb, const Close_Callback& close_cb) {
	conn_.reset(new Tcp_Connection);
	sock_.reset(new Sock_Connector);
	scream_reactor_.reset(new Reactor);
	ip_ = ip;
	port_ = port;
	int ret = sock_->init(AF_INET, SOCK_STREAM, 0, ip_.c_str(), port);
	if (SUCCESS == ret) {
		ret = sock_->enable(Sock::NONBLOCK);
		if (SUCCESS == ret) {
			conn_->set_fd(sock_->get_fd());
			scream_reactor_->init(1);
			conn_->set_reactor(scream_reactor_.get());
			conn_->set_recv_cb(recv_cb);
			conn_->set_close_cb(close_cb);
			conn_->set_cid(0);
			scream_reactor_->register_handler(conn_, Event::READ_WRITE_MASK);
		}
	}
	return ret;
}

int Tcp_Client::send(Msg_Block &&msg) {
	conn_->push_send_msg(std::move(msg));
	return SUCCESS;
}

void Tcp_Client::loop(void) {
	scream_reactor_->set_wait_ms(10);
	while (1) {
		scream_reactor_->handle_event();
	}
}

void Tcp_Client::start(void) {
	scream_thr_ = std::thread(std::bind(&Tcp_Client::loop, this));
	scream_thr_.detach();
}

