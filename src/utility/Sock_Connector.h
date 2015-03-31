/*
 * Sock_Connector.h
 *
 *  Created on: Apr 21, 2014
 *	  Author: "enjolras"
 */

#ifndef SOCK_CONNECTOR_H_
#define SOCK_CONNECTOR_H_

#include "Sock.h"

class Sock_Connector : public Sock {
public:
	Sock_Connector(void);
	~Sock_Connector(void);

	int init(int domain, int type, int protocol, const char* dest, int port);
};

#endif /* SOCK_CONNECTOR_H_ */
