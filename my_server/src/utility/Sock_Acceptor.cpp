/*
 * Sock_Acceptor.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: "enjolras@163.com"
 */

#include "Sock_Acceptor.h"
#include "Syscall_Wrapper.h"
#include "Net_Define.h"

Sock_Acceptor::Sock_Acceptor(void) {
}

Sock_Acceptor::~Sock_Acceptor(void) {
}

int Sock_Acceptor::init(int domain, int type, int protocol, int port, int backlog) {
	int ret = Sock::init(domain, type, protocol);
	if (ret == 0) {
		this->set_reuseaddr(true);
		struct sockaddr_in servaddr;
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = domain;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(port);
		ret = w_bind(fd_, (sockaddr *) &servaddr, sizeof(servaddr));
		if (ret == 0) {
			ret = w_listen(fd_, backlog);
		}
	}
	if (ret != 0) {
		Sock::fini();
	}
	return ret;
}

int Sock_Acceptor::accept(void) {
	return ::accept4(fd_, nullptr, nullptr, STREAM_SOCK_TYPE);
}
