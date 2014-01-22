/*
 * Acceptor.cpp
 *
 *  Created on: Jan 8, 2014
 *      Author: "enjolras@163.com"
 */

#include "Acceptor.h"
#include "Reactor.h"
#include "Log.h"
#include "Sock_Acceptor.h"

Acceptor::Acceptor(Reactor *reactor) : sock_acceptor_(nullptr) {
	set_reactor(reactor);
}

Acceptor::~Acceptor(void) {
}

int Acceptor::init(Sock_Acceptor *sock_acceptor, const Accept_Callback &accept_cb) {
	sock_acceptor_.reset(sock_acceptor);
	accept_cb_ = accept_cb;
	return get_reactor()->register_handler(this, ACCEPT_MASK);
}

void Acceptor::handle_input(void) {
	while (1) {
		int fd = sock_acceptor_->accept();
		if (fd > 0) {
			accept_cb_(get_reactor(), fd);
		} else {
			break;
		}
	}
}

void Acceptor::handle_output(void) {

}

void Acceptor::handle_close(void) {
	get_reactor()->remove_handler(this);
}

int Acceptor::get_fd(void) const {
	return sock_acceptor_->get_fd();
}

void Acceptor::set_fd(int fd) {
	return sock_acceptor_->set_fd(fd);
}
