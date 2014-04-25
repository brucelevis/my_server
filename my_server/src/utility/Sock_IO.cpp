/*
 * Sock_IO.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: "enjolras@163.com"
 */

#include "Sock_IO.h"

Sock_IO::Sock_IO(void) {
	using namespace std::placeholders;
	send_func_ = std::bind(&Sock_IO::send, this, _1, _2, _3);
	recv_func_ = std::bind(&Sock_IO::recv, this, _1, _2, _3);
}

int Sock_IO::send(void *buf, size_t n, int flags) const {
	return ::send(fd_, buf, n, flags);
}

int Sock_IO::recv(void *buf, size_t n, int flags) const {
	return ::recv(fd_, buf, n, flags);
}

int Sock_IO::sendv(const iovec iov[], int n) const {
	return ::writev(fd_, iov, n);
}

