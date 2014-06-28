/*
 * Condition.cc
 *
 *  Created on: Jan 24, 2014
 *      Author: "enjolras@163.com"
 */

#include "Condition.h"

Condition::Condition(Thread_Mutex& mutex) : mutex_(mutex) {
	pthread_cond_init(&pcond_, NULL);
}

Condition::~Condition(void) {
	pthread_cond_destroy(&pcond_);
}

