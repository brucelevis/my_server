/*
 * Tcp_Server.h
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "Pre_Header.h"
#include "Cid_Obj_Map.h"
#include "Svc_Holder.h"
#include "Condition.h"

class Reactor;
class Svc;
class Repo_Factory;
class Acceptor;
class Thread;
class Msg_Block;
class Tcp_Server {
public:
	typedef std::function<void(Msg_Block &&)> Recv_Callback;
	typedef std::function<void(int)> Close_Callback;
	typedef std::shared_ptr<Svc> SSvc;
	typedef std::weak_ptr<Svc> WSvc;
	typedef Cid_Obj_Map<SSvc> Cid_Svc_Map;
	typedef Svc_Holder<Thread_Mutex, 4096> SVC_HOLDER;

	Tcp_Server(void);
	~Tcp_Server(void);

	void init(const int listen_port, const int max_listen, const Recv_Callback &recv_cb, const Close_Callback &close_cb);
	void start(void);

	void send_to_client(const int cid, Msg_Block &&msg);
	void drop_handle(int cid);

private:
	void accept_loop(void);
	void recv_loop(void);
	void send_loop(void);
	void pack_loop(void);	// todo
	void release_loop(void); // todo 资源释放线程

	void accept_handle(int sock_fd);
	void send_handle(SSvc &svc);

private:
	Recv_Callback recv_cb_;
	Close_Callback close_cb_;

	boost::scoped_ptr<Reactor> accept_reactor_;
	boost::scoped_ptr<Reactor> input_reactor_;
	boost::scoped_ptr<Reactor> output_reactor_;
	boost::scoped_ptr<Repo_Factory> repo_fac_;
	std::shared_ptr<Acceptor> acceptor_;
	std::thread accept_thr_;
	std::thread input_thr_;
	std::thread output_thr_;
	Cid_Svc_Map cid_svc_map_;
	SVC_HOLDER svc_holder_;
};

#endif /* TCP_SERVER_H_ */
