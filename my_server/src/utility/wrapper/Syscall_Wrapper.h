/*
 * Syscall_Wrapper.h
 *
 *  Created on: Jan 9, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef SYSCALL_WRAPPER_H_
#define SYSCALL_WRAPPER_H_

#include "Pre_Header.h"
#include "Log.h"

inline int w_socket (int __domain, int __type, int __protocol) __THROW {
	int fd = ::socket(__domain, __type, __protocol);
	if (nullfd == fd) {
		rec_errno_log();
	}
	return fd;
}

inline int w_bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) __THROW {
	int ret = ::bind(__fd, __addr, __len);
	if (FAIL == ret) {
		rec_errno_log();
	}
	return ret;
}

inline int w_listen (int __fd, int __n) __THROW {
	int ret = ::listen(__fd, __n);
	if (FAIL == ret) {
		rec_errno_log();
	}
	return ret;
}

#endif /* SYSCALL_WRAPPER_H_ */
