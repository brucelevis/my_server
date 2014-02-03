/*
 * Reactor.h
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef REACTOR_H_
#define REACTOR_H_

#include "Pre_Header.h"

class Event;
class Reactor : private noncopyable {
public:
	enum {
		MAX_EPOLL_EVENT = 4096
	};

	typedef std::array<epoll_event, MAX_EPOLL_EVENT> Epoll_Events;
	typedef std::shared_ptr<Event> SEvent;
	typedef std::weak_ptr<Event> WEvent;
	typedef std::array<SEvent, MAX_EPOLL_EVENT> Event_Handlers;
	typedef std::function<void()> Functor;
	typedef std::deque<Functor> Functor_Deque;

	Reactor(void);
	~Reactor(void) = default;

	int init(void);
	int fini(void);
	int register_handler(const SEvent &evh, int event_type);
	int remove_handler(const SEvent &evh);

	void handle_event(void);
	inline void set_wait_ms(int wait_ms);

private:
	int epfd_;
	int wait_ms_;
	Epoll_Events events_;
	Event_Handlers handlers_;
};

inline void Reactor::set_wait_ms(int wait_ms) {
	wait_ms_ = wait_ms;
}

#endif /* REACTOR_H_ */
