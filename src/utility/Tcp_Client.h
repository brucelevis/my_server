/*
 * Tcp_Client.h
 *
 *  Created on: Apr 23, 2014
 *	  Author: "enjolras"
 */

#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "Pre_Header.h"
#include "Copy_Control.h"

class Tcp_Connection;
class Msg_Block;
class Sock_Connector;
class Reactor;
class Tcp_Client : private noncopyable {
public:
	typedef std::function<void(Msg_Block &&)> Recv_Callback;
	typedef std::function<void(int)> Close_Callback;
	Tcp_Client(void);
	~Tcp_Client(void);

	int init(const std::string &ip, const int port, const Recv_Callback& recv_cb, const Close_Callback& close_cb);
	int send(Msg_Block &&msg);
	void start(void);
	void loop(void);

private:
	std::shared_ptr<Tcp_Connection> conn_;
	boost::scoped_ptr<Sock_Connector> sock_;
	boost::scoped_ptr<Reactor> scream_reactor_;
	std::string ip_;
	int port_;
	std::thread scream_thr_;
};

#endif /* TCP_CLIENT_H_ */
