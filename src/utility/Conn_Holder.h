/*
 * Conn_Holder.h
 *
 *  Created on: Jan 26, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef CONN_HOLDER_H_
#define CONN_HOLDER_H_

#include "Pre_Header.h"
#include "Define.h"
#include "Thr_Mutex.h"
#include "Log.h"
#include "Tcp_Connection.h"

typedef std::shared_ptr<Tcp_Connection> SConn;
template <typename LOCK, int MAX_OBJ>
class Conn_Holder : public noncopyable {
public:
	typedef Mutex_Guard<LOCK> Guard;
	Conn_Holder(void) : current_max_cid_(nullcid) {}
	~Conn_Holder(void) = default;

	inline void insert(const SConn &conn);
	inline SConn erase(int cid);
	inline SConn find(int cid);
private:
	inline int generate_cid(void);

private:
	std::array<SConn, MAX_OBJ> conn_;
	std::array<LOCK, MAX_OBJ> conn_lock_;
	LOCK unused_lock_;
	std::unordered_set<int> unused_;
	int current_max_cid_;
	const static int max_cid_ = MAX_OBJ;
};

template <typename LOCK, int MAX_OBJ>
inline void Conn_Holder<LOCK, MAX_OBJ>::insert(const SConn &conn) {
	int cid = generate_cid();
	if (cid >= max_cid_) {
		rec_log(Log::LVL_ERROR, "larger than max cid %d", max_cid_);
		return;
	}
	conn->set_cid(cid);
	Guard guard(conn_lock_[cid]);
	conn_[cid] = conn;
}

template <typename LOCK, int MAX_OBJ>
inline SConn Conn_Holder<LOCK, MAX_OBJ>::erase(int cid) {
	SConn ret;
	if (cid >= max_cid_) {
		rec_log(Log::LVL_ERROR, "larger than max cid %d", max_cid_);
		return ret;
	}
	{
		Guard guard(unused_lock_);
		unused_.insert(cid);
	}
	{
		Guard guard(conn_lock_[cid]);
		ret.swap(conn_[cid]);
		return ret;
	}
}

template <typename LOCK, int MAX_OBJ>
inline SConn Conn_Holder<LOCK, MAX_OBJ>::find(int cid) {
	if (cid >= max_cid_) {
		rec_log(Log::LVL_ERROR, "larger than max cid %d", max_cid_);
		return nullptr;
	}
	{
		Guard guard(conn_lock_[cid]);
		return conn_[cid];
	}
}

template <typename LOCK, int MAX_OBJ>
inline int Conn_Holder<LOCK, MAX_OBJ>::generate_cid(void) {
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

#endif /* CONN_HOLDER_H_ */
