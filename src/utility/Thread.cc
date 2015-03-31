/*
 * Thread.cc
 *
 *  Created on: Jan 7, 2014
 *	  Author: "enjolras@163.com"
 */

#include "Thread.h"
#include "Log.h"

Thread::Thread(const Thr_Func &run, const Thr_Func &exit) : tid(0), run_func_(run), exit_func_(exit) {

}

Thread::~Thread(void) {

}

void *Thread::create_func(void *arg) {
	Thread *self = (Thread *)arg;
	pthread_cleanup_push(cleanup_func, arg);
	if (self->run_func_) {
		self->run_func_();
	}
	pthread_cleanup_pop(1);
	return self;
}

void Thread::cleanup_func(void *arg) {
	Thread *self = (Thread *)arg;
	if (self->exit_func_) {
		self->exit_func_();
	}
}

int Thread::thr_create(void) {
	return ::pthread_create(&tid, NULL, create_func, this);
}

int Thread::thr_cancel(void) {
	return ::pthread_cancel(tid);
}

int Thread::thr_join(void) {
	return ::pthread_join(tid, NULL);
}

int Thread::thr_cancel_join(void) {
	int ret;
	if ((ret = thr_cancel()) == 0) {
		ret = thr_join();
	} else {
		rec_log(Log::LVL_ERROR, "thr_cancel return ret = %d", ret);
	}
	return ret;
}

void Thread::thr_exit(void *rval_ptr) {
	::pthread_exit(rval_ptr);
}

