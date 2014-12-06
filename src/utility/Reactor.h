/*
 * Reactor.h
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef REACTOR_H_
#define REACTOR_H_

#include "Pre_Header.h"
#include "Copy_Control.h"

class Event;
class Reactor : private noncopyable {
public:
	enum {
		DEFAULT_MAX_EVENT = 4096,
		MAX_MAX_EVENT = 8192
	};

	typedef std::shared_ptr<Event> SEvent;
	typedef std::vector<epoll_event> Epoll_Events;
	typedef std::vector<SEvent> Event_Handlers;

	Reactor(void);
	~Reactor(void) = default;

	int init(int max_event = DEFAULT_MAX_EVENT);
	int fini(void);
	int register_handler(const SEvent &evh, int event_type);
	int remove_handler(const SEvent &evh);

	void handle_event(void);
	inline void set_wait_ms(int wait_ms);

private:
	int epfd_;
	int max_event_;
	int wait_ms_;
	Epoll_Events events_;
	Event_Handlers handlers_;
};

inline void Reactor::set_wait_ms(int wait_ms) {
	wait_ms_ = wait_ms;
}

#endif /* REACTOR_H_ */
