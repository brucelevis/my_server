/*
 * Tcp_Server.h
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "Pre_Header.h"
#include "Conn_Holder.h"
#include "Condition.h"

class Reactor;
class Tcp_Connection;
class Repo_Factory;
class Acceptor;
class Thread;
class Msg_Block;
class Block_Worker;
class Nonblock_Worker;
class Tcp_Server {
public:
	typedef std::function<void(Msg_Block &&)> Recv_Callback;
	typedef std::function<void(int)> Close_Callback;
	typedef std::shared_ptr<Tcp_Connection> SConn;
	typedef Conn_Holder<Thread_Mutex, DEFAULT_MAX_EVENT> CONN_HOLDER;

	Tcp_Server(void);
	~Tcp_Server(void);

	void init(const int listen_port, const int max_listen, const Recv_Callback &recv_cb, const Close_Callback &close_cb);
	void start(void);

	void send_to_client(const int cid, Msg_Block &&msg);
	void drop_handle(int cid);

private:
	void accept_loop(void);
	void scream_loop(void);

	void accept_handle(int sock_fd);

private:
	Recv_Callback recv_cb_;
	Close_Callback close_cb_;

	boost::scoped_ptr<Reactor> accept_reactor_;
	boost::scoped_ptr<Reactor> scream_reactor_;
	boost::scoped_ptr<Nonblock_Worker> scream_worker_;
	std::shared_ptr<Acceptor> acceptor_;
	std::thread accept_thr_;
	std::thread scream_thr_;
	CONN_HOLDER conn_holder_;
};

#endif /* TCP_SERVER_H_ */
