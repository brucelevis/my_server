/*
 * Block_Worker.h
 *
 *  Created on: Feb 3, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef BLOCK_WORKER_H_
#define BLOCK_WORKER_H_

#include "Base_Worker.h"
#include "Thr_Mutex_Guard.h"
#include "Condition.h"

class Block_Worker : public Base_Worker {
public:
	Block_Worker(void) : cond_(lock_) {}

	inline void push(const Functor &opt);
	inline void process(void);
private:
	Condition cond_;
};

inline void Block_Worker::push(const Functor &opt) {
	if (is_in_loop_thread()) {
		opt();
	} else {
		Mutex_Guard<Thread_Mutex> guard(lock_);
		waiting_opt_.push_back(opt);
		cond_.notify();
	}
}

inline void Block_Worker::process(void) {
	while (!handleing_opt_.empty()) {
		Functor &opt = handleing_opt_.front();
		opt();
		handleing_opt_.pop_front();
	}
	{
		Mutex_Guard<Thread_Mutex> guard(lock_);
		while (waiting_opt_.empty()) {
			cond_.wait();
		}
		std::swap(handleing_opt_, waiting_opt_);
	}
}

#endif /* BLOCK_WORKER_H_ */
