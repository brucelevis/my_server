/*
 * Tcp_Connection.h
 *
 *  Created on: Jan 13, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef CONN_H_
#define CONN_H_

#include "Event.h"
#include "Sock_IO.h"
#include "Thr_Mutex.h"
#include "Thr_Mutex_Guard.h"

class Msg_Block;
class Tcp_Connection : public Event, public Sock_IO {
public:
	typedef std::deque<Msg_Block> Msg_Block_Deque;
	typedef std::function<void(Msg_Block &&)> Recv_Callback;
	typedef std::function<void(int)> Close_Callback;

	Tcp_Connection(void);
	~Tcp_Connection(void);

	inline void set_recv_cb(const Recv_Callback &cb);
	inline void set_close_cb(const Close_Callback &cb);
	void push_send_msg(Msg_Block &&msg);

	virtual void handle_input(void) override;
	virtual int handle_output(void) override;
	virtual void handle_close(void) override;
	virtual int get_fd(void) const override;
	virtual void set_fd(int fd) override;
	void reset(void);
private:
	Recv_Callback recv_cb_;
	Close_Callback close_cb_;
	Thread_Mutex output_lock_;
	Msg_Block_Deque output_;
	boost::scoped_ptr<Msg_Block> input_;
};

inline void Tcp_Connection::set_recv_cb(const Recv_Callback &cb) {
	recv_cb_ = cb;
}

inline void Tcp_Connection::set_close_cb(const Close_Callback &cb) {
	close_cb_ = cb;
}

#endif /* CONN_H_ */
