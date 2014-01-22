/*
 * Sock.cpp
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
	return ::close(fd_);
}

int Sock::set_option(int level, int option, void *optval, socklen_t optlen) {
	return setsockopt(fd_, level, option, optval, optlen);
}

int Sock::get_option(int level, int option, void *optval, socklen_t &optlen) const {
	return getsockopt(fd_, level, option, optval, &optlen);
}
