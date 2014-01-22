/*
 * Obj_Pool.h
 *
 *  Created on: Jan 14, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef OBJ_POOL_H_
#define OBJ_POOL_H_

#include "Pre_Header.h"
#include "Thr_Mutex.h"
#include "Thr_Mutex_Guard.h"
#include "Log.h"

template <typename Obj, typename LOCK = Spin_Lock>
class Obj_Pool : private noncopyable {
public:
	typedef std::vector<Obj*> Obj_Vec;
	typedef std::unordered_set<Obj*> Obj_Set;
	typedef Mutex_Guard<LOCK > Guard;

	Obj_Pool(void) = default;
	~Obj_Pool(void) = default;

	Obj *pop(void);
	int push(Obj *obj);
	void init(uint32_t free, uint32_t used);
	void reserve(uint32_t nums);
	void reset(void);

private:
	LOCK lock_;
	Obj_Vec free_;
	Obj_Set used_;
};

template <typename Obj, typename LOCK>
Obj * Obj_Pool<Obj, LOCK>::pop(void) {
	Obj *obj = nullptr;
	Guard guard(lock_);
	if (!free_.empty()) {
		obj = free_.back();
		free_.pop_back();
	} else {
		obj = new Obj;
	}
	if (!used_.insert(obj).second) {
		rec_log(Log::LVL_TRACE_ERROR, "insert failure.");
	}
	obj->reset();
	return obj;
}

template <typename Obj, typename LOCK>
int Obj_Pool<Obj, LOCK>::push(Obj *obj) {
	if (nullptr == obj) {
		return FAIL;
	}
	obj->reset();
	Guard guard(lock_);
	auto used_obj_it = used_.find(obj);
	if (used_obj_it == used_.end()) {
		rec_log(Log::LVL_TRACE_ERROR, "not in used.");
		return FAIL;
	}
	used_.erase(used_obj_it);
	free_.push_back(obj);
	return 0;
}

template <typename Obj, typename LOCK>
void Obj_Pool<Obj, LOCK>::init(uint32_t free, uint32_t used) {
	Guard guard(lock_);
	uint32_t size = free_.size();
	if (size < free) {
		free_.reserve(free);
	}
	while (size < free) {
		free_.push_back(new Obj);
		++size;
	}
	used_.rehash(used);
}

template <typename Obj, typename LOCK>
void Obj_Pool<Obj, LOCK>::reserve(uint32_t nums) {
	Guard guard(lock_);
	uint32_t size = free_.size();
	if (size < nums) {
		free_.reserve(nums);
	}
	while (size < nums) {
		free_.push_back(new Obj);
		++size;
	}
}

template <typename Obj, typename LOCK>
void Obj_Pool<Obj, LOCK>::reset(void) {
	Guard guard(lock_);
	for (auto obj : free_) {
		delete obj;
	}
	for (auto obj : used_) {
		delete obj;
	}
	free_.clear();
	used_.clear();
}

#endif /* OBJ_POOL_H_ */
