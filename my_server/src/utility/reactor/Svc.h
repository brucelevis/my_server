/*
 * Svc.h
 *
 *  Created on: Jan 13, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef SVC_H_
#define SVC_H_

#include "Event.h"
#include "Sock_IO.h"
#include "Thr_Mutex.h"
#include "Thr_Mutex_Guard.h"

class Msg_Block;
class Svc : public Event, public Sock_IO {
public:
	typedef std::deque<Msg_Block> Msg_Block_Deque;
	typedef std::function<void(Msg_Block &&)> Recv_Callback;
	typedef std::function<void(int)> Close_Callback;

	Svc(void);
	~Svc(void);

	inline void set_cid(int cid);
	inline int get_cid(void);
	inline void set_recv_cb(const Recv_Callback &cb);
	inline void set_close_cb(const Close_Callback &cb);
	void push_send_msg(Msg_Block &&msg);

	virtual void handle_input(void) override;
	virtual void handle_output(void) override;
	virtual void handle_close(void) override;
	virtual int get_fd(void) const override;
	virtual void set_fd(int fd) override;
	void reset(void);
private:
	int cid_;
	Recv_Callback recv_cb_;
	Close_Callback close_cb_;
	Thread_Mutex output_lock_;
	Msg_Block_Deque output_;
};

inline void Svc::set_cid(int cid) {
	cid_ = cid;
}

inline int Svc::get_cid(void) {
	return cid_;
}

inline void Svc::set_recv_cb(const Recv_Callback &cb) {
	recv_cb_ = cb;
}

inline void Svc::set_close_cb(const Close_Callback &cb) {
	close_cb_ = cb;
}

#endif /* SVC_H_ */
