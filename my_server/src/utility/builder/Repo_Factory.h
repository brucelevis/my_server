/*
 * Reactor_Factory.h
 *
 *  Created on: Jan 11, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef REPO_FACTORY_H_
#define REPO_FACTORY_H_

#include "Obj_Pool.h"

class Svc;
class Repo_Factory {
public:
	enum {
		SVC_NUMS = 8192
	};

	typedef Obj_Pool<Svc> Svc_Pool;

	Repo_Factory(void);
	~Repo_Factory(void);

	void init(void);
	Svc *pop_svc(void);
	void push_svc(Svc *svc);
private:
	Svc_Pool svc_pool_;
};

#endif /* REPO_FACTORY_H_ */
