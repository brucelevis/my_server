/*
 * Nonblock_Worker.h
 *
 *  Created on: Feb 3, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef NONBLOCK_WORKER_H_
#define NONBLOCK_WORKER_H_

#include "Base_Worker.h"

class Nonblock_Worker : public Base_Worker {
public:
	inline void push(const Functor &opt);
	inline void process(void);
};

inline void Nonblock_Worker::push(const Functor &opt) {
	if (is_in_loop_thread()) {
		opt();
	} else {
		Mutex_Guard<Thread_Mutex> guard(lock_);
		waiting_opt_.push_back(opt);
	}
}

inline void Nonblock_Worker::process(void) {
	{
		Mutex_Guard<Thread_Mutex> guard(lock_);
		if (!waiting_opt_.empty()) {
			std::swap(handleing_opt_, waiting_opt_);
		}
	}
	while (!handleing_opt_.empty()) {
		Functor &opt = handleing_opt_.front();
		opt();
		handleing_opt_.pop_front();
	}
}

#endif /* NONBLOCK_WORKER_H_ */
