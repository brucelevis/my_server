/*
 * Cid_Obj_Map.h
 *
 *  Created on: Jan 22, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef CID_OBJ_MAP_H_
#define CID_OBJ_MAP_H_

#include "Pre_Header.h"
#include "Thr_Mutex.h"
#include "Log.h"

template <typename OBJ, typename LOCK = Thread_Mutex>
class Cid_Obj_Map {
public:
	typedef Mutex_Guard<LOCK> Guard;
	typedef std::function<void(OBJ&)> Obj_Callback;

	Cid_Obj_Map(int reserve) : inused_(reserve), max_cid_(nullcid) {};
	~Cid_Obj_Map(void) = default;

	inline void insert_obj(OBJ &obj);
	inline OBJ erase_obj(int cid);
	inline void find_obj(int cid, OBJ &obj);

private:
	inline int generate_cid(void);
private:
	LOCK inused_lock_;
	LOCK unused_lock_;
	std::unordered_map<int, OBJ> inused_;
	std::unordered_set<int> unused_;
	int max_cid_;
	Obj_Callback cb_;
};

template <typename OBJ, typename LOCK>
inline void Cid_Obj_Map<OBJ, LOCK>::insert_obj(OBJ &obj) {
	int cid = generate_cid();
	obj->set_cid(cid);
	Guard guard(inused_lock_);
	inused_[cid] = obj;
}

template <typename OBJ, typename LOCK>
inline OBJ Cid_Obj_Map<OBJ, LOCK>::erase_obj(int cid) {
	{
		Guard guard(unused_lock_);
		unused_.insert(cid);
	}
	OBJ obj;
	{
		Guard guard(inused_lock_);
		auto it = inused_.find(cid);
		if (it != inused_.end()) {
			obj.swap(it->second);
			inused_.erase(it);
		}
	}
	return obj;
}

template <typename OBJ, typename LOCK>
inline void Cid_Obj_Map<OBJ, LOCK>::find_obj(int cid, OBJ &obj) {
	Guard guard(inused_lock_);
	auto it = inused_.find(cid);
	if (it != inused_.end()) {
		obj = it->second;
	} else {
		rec_log(Log::LVL_TRACE_ERROR, "can't find svc %d", cid);
		obj.reset();
	}
}

template <typename OBJ, typename LOCK>
inline int Cid_Obj_Map<OBJ, LOCK>::generate_cid(void) {
	Guard guard(unused_lock_);
	if (!unused_.empty()) {
		int cid = *unused_.begin();
		unused_.erase(unused_.begin());
		return cid;
	} else {
		++max_cid_;
		rec_log(Log::LVL_DEBUG, "max cid %d", max_cid_);
		return max_cid_;
	}
}

#endif /* CID_OBJ_MAP_H_ */
