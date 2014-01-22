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

	Tcp_Server(void);
	~Tcp_Server(void);

	void init(int listen_port, int max_listen);
	void start(void);
	void set_recv_cb(const Recv_Callback &cb);
	void set_close_cb(const Close_Callback &cb);

private:
	void handle_input_event(void);
	void accept_handle(Reactor *reactor, int sock_fd);
	void drop_handle(int cid);

	inline Svc *find_svc(int cid);
	int generate_cid(void);

private:
	Recv_Callback recv_cb_;
	Close_Callback close_cb_;

	boost::scoped_ptr<Reactor> reactor_;
	boost::scoped_ptr<Repo_Factory> repo_fac_;
	boost::scoped_ptr<Acceptor> acceptor_;
	std::thread input_thr_;

	std::unordered_map<int, Svc*> inused_;
	std::unordered_set<int> unused_;
	int max_cid_;
};

void Tcp_Server::set_recv_cb(const Recv_Callback &cb) {
	recv_cb_ = cb;
}

void Tcp_Server::set_close_cb(const Close_Callback &cb) {
	close_cb_ = cb;
}

inline Svc *Tcp_Server::find_svc(int cid) {
	auto it = inused_.find(cid);
	if (it != inused_.end()) {
		return it->second;
	} else {
		rec_log(Log::LVL_TRACE_ERROR, "can't find svc %d", cid);
		return nullptr;
	}
}

inline int Tcp_Server::generate_cid(void) {
	if (!unused_.empty()) {
		return *unused_.begin();
	} else {
		rec_log(Log::LVL_DEBUG, "max cid %d", max_cid_);
		return max_cid_++;
	}
}

#endif /* TCP_SERVER_H_ */
