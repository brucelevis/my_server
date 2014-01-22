/*
 * Singleton.h
 *
 *  Created on: Jan 6, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "Thr_Mutex.h"
#include "Thr_Mutex_Guard.h"

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
	static T* si_instance;
};

template<typename T, typename LOCK>
LOCK Singleton<T, LOCK>::lock;
template<typename T, typename LOCK>
T* Singleton<T, LOCK>::si_instance = nullptr;

template<typename T, typename LOCK>
T& Singleton<T, LOCK>::Instance(void)
{
	if (!si_instance)
	{
		// double-checked Locking pattern
		Mutex_Guard<LOCK> guard(lock);
		if (!si_instance)
		{
			si_instance = new T;
		}
	}
	return *si_instance;
}

#endif /* SINGLETON_H_ */
