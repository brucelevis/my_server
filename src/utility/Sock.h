/*
 * Sock.h
 *
 *  Created on: Jan 8, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef SOCK_H_
#define SOCK_H_

#include "Pre_Header.h"
#include "IPC_SAP.h"

class Sock : public IPC_SAP {
public:
	void set_reuseaddr(bool on);
	void set_tcpnodelay(bool on);

	int init(int domain, int type, int protocol);
	int fini(void);
};

#endif /* SOCK_H_ */
