/*
 * Tcp_Server.h
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "Pre_Header.h"
#include "Obj_Pool.h"
#include "Cid_Obj_Map.h"

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
	typedef Cid_Obj_Map<SSvc> Cid_Svc_Map;

	struct Sended_Sum {
		Sended_Sum(void) { sended_sum_ = 0; }
	    void operator()(SSvc &svc);
	    void reset(void) {
	    	sended_sum_ = 0;
	    }
	    int sended_sum_;
	};

	Tcp_Server(void);
	~Tcp_Server(void);

	void init(const int listen_port, const int max_listen, const Recv_Callback &recv_cb, const Close_Callback &close_cb);
	void start(void);

	void send_to_client(const int cid, Msg_Block &&msg);
	void drop_handle(int cid);

private:
	void accept_loop(void);
	void recv_loop(void);
	void pack_loop(void);	// todo
	void send_loop(void);
	void release_loop(void); // todo 资源释放线程

	void accept_handle(int sock_fd);

private:
	Recv_Callback recv_cb_;
	Close_Callback close_cb_;

	boost::scoped_ptr<Reactor> accept_reactor_;
	boost::scoped_ptr<Reactor> input_reactor_;
	boost::scoped_ptr<Repo_Factory> repo_fac_;
	boost::scoped_ptr<Acceptor> acceptor_;
	std::thread accept_thr_;
	std::thread input_thr_;
	std::thread send_thr_;
	Cid_Svc_Map cid_svc_map_;
	Sended_Sum sended_sum_;
};

#endif /* TCP_SERVER_H_ */