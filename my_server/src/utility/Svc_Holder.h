/*
 * Svc_Holder.h
 *
 *  Created on: Jan 26, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef SVC_HOLDER_H_
#define SVC_HOLDER_H_

#include "Pre_Header.h"
#include "Thr_Mutex.h"
#include "Log.h"
#include "Svc.h"

typedef std::shared_ptr<Svc> SSvc;
template <typename LOCK, int MAX_OBJ>
class Svc_Holder : public noncopyable {
public:
	typedef Mutex_Guard<LOCK> Guard;
	Svc_Holder(void) : current_max_cid_(nullcid) {}
	~Svc_Holder(void) = default;

	inline void insert_svc(const SSvc &svc);
	inline SSvc erase_obj(int cid);
	inline SSvc find_svc(int cid);
private:
	inline int generate_cid(void);

private:
	std::array<SSvc, MAX_OBJ> svc_;
	std::array<LOCK, MAX_OBJ> svc_lock_;
	LOCK unused_lock_;
	std::unordered_set<int> unused_;
	int current_max_cid_;
	const static int max_cid_ = MAX_OBJ;
};

template <typename LOCK, int MAX_OBJ>
inline void Svc_Holder<LOCK, MAX_OBJ>::insert_svc(const SSvc &svc) {
	int cid = generate_cid();
	if (cid >= max_cid_) {
		rec_log(Log::LVL_ERROR, "larger than max cid %d", max_cid_);
		return;
	}
	svc->set_cid(cid);
	Guard guard(svc_lock_[cid]);
	svc_[cid] = svc;
}

template <typename LOCK, int MAX_OBJ>
inline SSvc Svc_Holder<LOCK, MAX_OBJ>::erase_obj(int cid) {
	SSvc ret;
	if (cid >= max_cid_) {
		rec_log(Log::LVL_ERROR, "larger than max cid %d", max_cid_);
		return ret;
	}
	{
		Guard guard(unused_lock_);
		unused_.insert(cid);
	}
	{
		Guard guard(svc_lock_[cid]);
		ret.swap(svc_[cid]);
		return ret;
	}
}

template <typename LOCK, int MAX_OBJ>
inline SSvc Svc_Holder<LOCK, MAX_OBJ>::find_svc(int cid) {
	if (cid >= max_cid_) {
		rec_log(Log::LVL_ERROR, "larger than max cid %d", max_cid_);
		return nullptr;
	}
	{
		Guard guard(svc_lock_[cid]);
		return svc_[cid];
	}
}

template <typename LOCK, int MAX_OBJ>
inline int Svc_Holder<LOCK, MAX_OBJ>::generate_cid(void) {
	{
		Guard guard(unused_lock_);
		if (!unused_.empty()) {
			int cid = *unused_.begin();
			unused_.erase(unused_.begin());
			return cid;
		}
	}
	++current_max_cid_;
	rec_log(Log::LVL_DEBUG, "max cid %d", current_max_cid_);
	return current_max_cid_;
}

#endif /* SVC_HOLDER_H_ */
