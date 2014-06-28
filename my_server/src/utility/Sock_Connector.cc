/*
 * Sock_Connector.cc
 *
 *  Created on: Apr 21, 2014
 *      Author: "enjolras"
 */

#include "Sock_Connector.h"
#include "Syscall_Wrapper.h"

Sock_Connector::Sock_Connector(void) {
}

Sock_Connector::~Sock_Connector(void) {
}

int Sock_Connector::init(int domain, int type, int protocol, const char* dest, int port) {
	int ret = Sock::init(domain, type, protocol);
	if (ret == SUCCESS) {
		struct sockaddr_in servaddr;
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = domain;
		servaddr.sin_port = htons(port);
		ret = w_inet_pton(AF_INET, dest, &servaddr.sin_addr);
		if (ret == SUCCESS) {
			ret = w_connect(fd_, (struct sockaddr *)&servaddr, sizeof(servaddr));
		}
	}
	if (ret != SUCCESS) {
		Sock::fini();
	}
	return ret;
}
