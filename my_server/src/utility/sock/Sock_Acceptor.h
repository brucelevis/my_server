/*
 * Sock_Acceptor.h
 *
 *  Created on: Jan 9, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef SOCK_ACCEPTOR_H_
#define SOCK_ACCEPTOR_H_

#include "Sock.h"

class Sock_IO;
class Sock_Acceptor : public Sock {
public:
	Sock_Acceptor(void);
	~Sock_Acceptor(void);

	int init(int domain, int type, int protocol, int port, int backlog);
	int accept(void);
};

#endif /* SOCK_ACCEPTOR_H_ */
