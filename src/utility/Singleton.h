/*
 * Singleton.h
 *
 *  Created on: Jan 6, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "Thr_Mutex.h"
#include "Thr_Mutex_Guard.h"
#include "Copy_Control.h"

template<typename T, typename LOCK = Null_Mutex>
class Singleton : private noncopyable
{
public:
	static T& Instance(void);

protected:
	Singleton(void)
	{
	}

private:
	// data structure
	static LOCK lock;
	static std::atomic<T*> si_instance;
};

template<typename T, typename LOCK>
LOCK Singleton<T, LOCK>::lock;
template<typename T, typename LOCK>
std::atomic<T*> Singleton<T, LOCK>::si_instance(nullptr);

template<typename T, typename LOCK>
T& Singleton<T, LOCK>::Instance(void)
{
	T* tmp = si_instance.load(std::memory_order_relaxed);
	// prevents the memory reordering of any read which precedes it in program order with any read or write which follows it in program order
	// prevents #loadload #loadstore
	std::atomic_thread_fence(std::memory_order_acquire);
	if (nullptr == tmp)
	{
		Mutex_Guard<LOCK> guard(lock);
		tmp = si_instance.load(std::memory_order_relaxed);
		if (nullptr == tmp)
		{
			tmp = new T;
			// prevents the memory reordering of any read or write which precedes it in program order with any write which follows it in program order
			// prevents #loadstore #storestore
			std::atomic_thread_fence(std::memory_order_release);
			si_instance.store(tmp, std::memory_order_relaxed);
		}
	}
	return *tmp;
}

#endif /* SINGLETON_H_ */
