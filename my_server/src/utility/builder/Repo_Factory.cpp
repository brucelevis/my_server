/*
 * Reactor_Factory.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: "enjolras@163.com"
 */

#include "Repo_Factory.h"
#include "Svc.h"

Repo_Factory::Repo_Factory(void) {
}

Repo_Factory::~Repo_Factory(void) {
}

void Repo_Factory::init(void) {
	svc_pool_.init(SVC_NUMS, SVC_NUMS);
}

Svc *Repo_Factory::pop_svc(void) {
	Svc *svc = svc_pool_.pop();
	return svc;
}

void Repo_Factory::push_svc(Svc *svc) {
	svc_pool_.push(svc);
}
