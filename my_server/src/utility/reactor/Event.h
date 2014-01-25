/*
 * Event_Handler.h
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include "Pre_Header.h"

class Reactor;
class Event : private noncopyable {
public:
	enum {
		READ_MASK = (1 << 0),
		WRITE_MASK = (1 << 1),
		EXCEPT_MASK = (1 << 2),
		ACCEPT_MASK = (1 << 3),
		CONNECT_MASK = (1 << 4),
		TIMER_MASK = (1 << 5),
		READ_WRITE_MASK = READ_MASK | WRITE_MASK,
	};

	virtual void handle_input(void) = 0;
	virtual int handle_output(void) = 0;
	virtual void handle_close(void) = 0;
	virtual int get_fd(void) const = 0;
	virtual void set_fd(int fd) = 0;

	inline Reactor *get_reactor(void) const;
	inline void set_reactor(Reactor * const reactor);

protected:
	Event(void);
	virtual ~Event(void) = default;

private:
	Reactor* reactor_;
};

inline Reactor *Event::get_reactor(void) const {
	return reactor_;
}

inline void Event::set_reactor(Reactor * const reactor) {
	reactor_ = reactor;
}

#endif /* EVENT_HANDLER_H_ */
