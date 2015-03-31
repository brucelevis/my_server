/*
 * Sock_IO.h
 *
 *  Created on: Jan 10, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef SOCK_IO_H_
#define SOCK_IO_H_

#include "Sock.h"

class Sock_IO :public Sock {
protected:
	int send(void *buf, size_t n, int flags) const;
	int recv(void *buf, size_t n, int flags) const;
	int sendv(const iovec iov[], int n) const;

protected:
	Sock_IO(void);

	typedef std::function<int(void *, size_t, int)> SendRecv_Func;
	SendRecv_Func send_func_;
	SendRecv_Func recv_func_;
};

#endif /* SOCK_IO_H_ */
