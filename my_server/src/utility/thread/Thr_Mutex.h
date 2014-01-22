/*
 * Thr_Mutex.h
 *
 *  Created on: Jan 14, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef THR_MUTEX_H_
#define THR_MUTEX_H_

#include "Pre_Header.h"

class Null_Mutex : private noncopyable {
public:
	Null_Mutex(void) { }
	~Null_Mutex(void) { }

	int acquire(void) {
		return 0;
	}
	int release(void) {
		return 0;
	}
	int acquire_read(void) {
		return 0;
	}
	int acquire_write(void) {
		return 0;
	}
};

class Thread_Mutex : private noncopyable {
public:
	Thread_Mutex(void) {
		::pthread_mutex_init(&lock_, NULL);
	}
	~Thread_Mutex(void) {
		::pthread_mutex_destroy(&lock_);
	}

	int acquire(void) {
		return ::pthread_mutex_lock(&lock_);
	}

	int release(void) {
		return ::pthread_mutex_unlock(&lock_);
	}

	int acquire_read(void) {
		return this->acquire();
	}

	int acquire_write(void) {
		return this->acquire();
	}
private:
	pthread_mutex_t lock_;
};

class RW_Mutex : private noncopyable {
public:
	RW_Mutex(void) {
		::pthread_rwlock_init(&lock_, NULL);
	}

	~RW_Mutex(void) {
		::pthread_rwlock_destroy(&lock_);
	}

	int acquire(void) {
		return ::pthread_rwlock_wrlock(&lock_);
	}

	int release(void) {
		return ::pthread_rwlock_unlock(&lock_);
	}

	int acquire_read(void) {
		return ::pthread_rwlock_rdlock(&lock_);
	}

	int acquire_write(void) {
		return ::pthread_rwlock_wrlock(&lock_);
	}
private:
	pthread_rwlock_t lock_;
};

class RE_Mutex : private noncopyable {
public:
	RE_Mutex(void) {
		::pthread_mutexattr_init(&attr);
		::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		::pthread_mutex_init(&lock_, &attr);
	}

	~RE_Mutex(void) {
		::pthread_mutex_destroy(&lock_);
		::pthread_mutexattr_destroy(&attr);
	}

	int acquire(void) {
		return ::pthread_mutex_lock(&lock_);
	}

	int release(void) {
		return ::pthread_mutex_unlock(&lock_);
	}

	int acquire_read(void) {
		return this->acquire();
	}

	int acquire_write(void) {
		return this->acquire();
	}
private:
	pthread_mutexattr_t attr;
	pthread_mutex_t lock_;
};

class Spin_Lock : private noncopyable {
public:
	Spin_Lock(void) {
		::pthread_spin_init(&lock_, 0);
	}

	~Spin_Lock(void) {
		::pthread_spin_destroy(&lock_);
	}

	int acquire(void) {
		return ::pthread_spin_lock(&lock_);
	}

	int release(void) {
		return ::pthread_spin_unlock(&lock_);
	}

	int acquire_read(void) {
		return this->acquire();
	}

	int acquire_write(void) {
		return this->acquire();
	}
private:
	pthread_spinlock_t lock_;
};

#endif /* THR_MUTEX_H_ */
