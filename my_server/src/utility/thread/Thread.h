/*
 * Thread.h
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "Pre_Header.h"

class Thr_Worker;
class Thread : private noncopyable {
public:
	typedef std::function<void(void)> Thr_Func;

	Thread(const Thr_Func &run, const Thr_Func &exit = nullptr);
	~Thread(void);

	static void *create_func(void *arg);
	static void cleanup_func(void *arg);

	int thr_create(void);
	int thr_cancel(void);
	int thr_join(void);
	int thr_cancel_join(void);
	void thr_exit(void *rval_ptr);
	inline pthread_t thread_id(void);
private:
	pthread_t tid;
	Thr_Func run_func_;
	Thr_Func exit_func_;
};

inline pthread_t Thread::thread_id(void) {
	return tid;
}

#endif /* THREAD_H_ */
