/*
 * Client.h
 *
 *  Created on: Apr 23, 2014
 *	  Author: "enjolras"
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "Pre_Header.h"

class Tcp_Client;
class Msg_Block;
class Client {
public:
	Client(void);
	~Client(void);

	void init(void);
	void start(void);
private:
	void recv_handle(const Msg_Block &msg);
	void close_handle(int cid);
	void loop(void);

	void protobuf_loop(void);

private:
	boost::scoped_ptr<Tcp_Client> tcp_client_;
	std::thread thr_;
};

#endif /* CLIENT_H_ */
