/*
 * Thr_Mutex_Guard.h
 *
 *  Created on: Jan 14, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef THR_MUTEX_GUARD_H_
#define THR_MUTEX_GUARD_H_

#include "Thr_Mutex.h"

template <typename LOCK>
class Mutex_Guard {
public:
	Mutex_Guard(LOCK &l) : lock_(&l) { this->acquire();}
	~Mutex_Guard(void) { this->release(); }

	void acquire(void) { lock_->acquire(); }
	void release(void) { lock_->release(); }
	void acquire_read(void) { lock_->acquire_read(); }
	void acquire_write(void) { lock_->acquire_write(); }
private:
	LOCK *lock_;
};

template <typename LOCK>
class Read_Guard {
public:
	Read_Guard(LOCK &l) : lock_(&l) { acquire_read(); }
	~Read_Guard(void) { this->release(); }

	void release(void) { lock_->release(); }
	void acquire_read(void) { lock_->acquire_read(); }
private:
	LOCK *lock_;
};

template <typename LOCK>
class Write_Guard {
public:
	Write_Guard(LOCK &l): lock_(&l) { acquire_write(); }
	~Write_Guard(void) { this->release(); }

	void release(void) { lock_->release(); }
	void acquire_write(void) { lock_->acquire_write(); }
private:
	LOCK *lock_;
};

#endif /* THR_MUTEX_GUARD_H_ */
