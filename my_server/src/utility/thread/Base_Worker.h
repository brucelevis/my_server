/*
 * Base_Worker.h
 *
 *  Created on: Feb 3, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef BASE_WORKER_H_
#define BASE_WORKER_H_

#include "Pre_Header.h"
#include "Thr_Mutex.h"

class Base_Worker : private noncopyable {
public:
	typedef std::function<void()> Functor;
	typedef std::deque<Functor> Functor_Deque;

	inline void set_loop_thrid(void);
	inline bool is_in_loop_thread(void);

protected:
	Base_Worker(void) = default;
	~Base_Worker(void) = default;

protected:
	std::thread::id thr_id_;
	Functor_Deque waiting_opt_;
	Functor_Deque handleing_opt_;
	Thread_Mutex lock_;
};

inline void Base_Worker::set_loop_thrid(void) {
	thr_id_ = std::this_thread::get_id();
}

inline bool Base_Worker::is_in_loop_thread(void) {
	return thr_id_ == std::this_thread::get_id();
}

#endif /* BASE_WORKER_H_ */
