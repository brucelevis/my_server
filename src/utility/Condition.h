/*
 * Condition.h
 *
 *  Created on: Jan 24, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef CONDITION_H_
#define CONDITION_H_

#include "Pre_Header.h"
#include "Thr_Mutex.h"

class Condition : private noncopyable {
public:
	Condition(Thread_Mutex& mutex);
	~Condition(void);

	inline void wait(void);
	inline void notify(void);
	inline void notifyAll(void);

private:
	Thread_Mutex& mutex_;
	pthread_cond_t pcond_;
};

inline void Condition::wait(void)
{
	pthread_cond_wait(&pcond_, mutex_.get());
}

inline void Condition::notify(void)
{
	pthread_cond_signal(&pcond_);
}

inline void Condition::notifyAll(void)
{
	pthread_cond_broadcast(&pcond_);
}

#endif /* CONDITION_H_ */
