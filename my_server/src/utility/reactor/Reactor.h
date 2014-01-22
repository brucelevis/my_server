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
	typedef std::array<Event*, MAX_EPOLL_EVENT> Event_Handlers;

	Reactor(void);
	~Reactor(void) = default;

	int init(void);
	int fini(void);
	int register_handler(Event *evh, int event_type);
	int remove_handler(Event *evh);
	void handle_event(void);

private:
	int epfd_;
	Epoll_Events events_;
	Event_Handlers handlers_;
};

#endif /* REACTOR_H_ */
