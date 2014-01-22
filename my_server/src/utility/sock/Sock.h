/*
 * Sock.h
 *
 *  Created on: Jan 8, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef SOCK_H_
#define SOCK_H_

#include "Pre_Header.h"
#include "IPC_SAP.h"

class Sock : public IPC_SAP {
public:
	int init(int domain, int type, int protocol);
	int fini(void);
	int set_option(int level, int option, void *optval, socklen_t optlen);
	int get_option(int level, int option, void *optval, socklen_t &optlen) const;
};

#endif /* SOCK_H_ */
