/*
 * Functor.h
 *
 *  Created on: Dec 13, 2014
 *	  Author: "enjolras"
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "Pre_Header.h"

typedef std::function<void()> Functor;
typedef std::deque<Functor> Functor_Deque;

typedef std::shared_ptr<Functor> SFunctor;
typedef std::weak_ptr<Functor> WFunctor;

#endif /* FUNCTOR_H_ */
