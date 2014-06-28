/*
 * Sock.cc
 *
 *  Created on: Jan 8, 2014
 *      Author: "enjolras@163.com"
 */

#include "Sock.h"
#include "Log.h"
#include "Syscall_Wrapper.h"

int Sock::init(int domain, int type, int protocol) {
	if (fd_ != nullfd) {
		return FAIL;
	}

	int fd = w_socket(domain, type, protocol);
	if (nullfd == fd) {
		return FAIL;
	}

	fd_ = fd;
	return 0;
}

int Sock::fini(void) {
	if (fd_ == nullfd) {
		return FAIL;
	}
	::close(fd_);
	fd_ = nullfd;
	return SUCCESS;
}

void Sock::set_reuseaddr(bool on) {
	int optval = on ? 1 : 0;
	::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
}

void Sock::set_tcpnodelay(bool on) {
	int optval = on ? 1 : 0;
	::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
}
