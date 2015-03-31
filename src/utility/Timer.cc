/*
 * Timer.cc
 *
 *  Created on: Dec 12, 2014
 *	  Author: "enjolras"
 */

#include "Timer.h"
#include "Log.h"
#include "Time_Value.h"

#define TICK_MS_GAP 100
#define TVN_BITS 4
#define TVR_BITS 8
#define TVN_SIZE (1 << TVN_BITS)
#define TVR_SIZE (1 << TVR_BITS)
#define TVN_MASK (TVN_SIZE - 1)
#define TVR_MASK (TVR_SIZE - 1)

struct Timer_Data {
	Timer_Data(uint32_t id_, unsigned long expires_, const Functor &functor_) : id(id_), expires(expires_), functor(functor_) {}

	uint32_t id;				// timer id 为0时 timer不可撤销，修改
	unsigned long expires;
	Functor functor;
};

typedef std::list<Timer_Data> Timer_List;

typedef std::array<Timer_List, TVN_SIZE> TVec;
typedef std::array<Timer_List, TVR_SIZE> TRec_Root;

struct TVec_Base {
	unsigned long timer_jiffies;
	unsigned long next_timer;			// interrupt when a smaller timer is add
	TRec_Root tv1;
	TVec tv2;
	TVec tv3;
	TVec tv4;
	TVec tv5;
};

inline void null_signal_handle(int signal) {}

Timer::Timer(void) : jiffies_(0), thr_id_(0), id_gen_(0) {

}

void Timer::init(void) {
	base_time_.reset(new Time_Value);
	base_.reset(new TVec_Base);
	base_->timer_jiffies = 0;
	base_->next_timer = ULONG_MAX;
	signal(SIGUSR1, null_signal_handle);
}

void Timer::start(void) {
	thr_ = std::thread(std::bind(&Timer::loop, this));
	thr_.detach();
}

inline unsigned long get_jiffies(unsigned long expires, const Time_Value &base) {
	return Time_Value::get_msec_gap(Time_Value::gettimeofday(), base) / TICK_MS_GAP + expires;
}

void Timer::add_timer(unsigned long expires, const Functor &functor) {
	uint32_t id;
	add_timer(expires, functor, id);
}

void Timer::add_timer(unsigned long expires, const Functor &functor, uint32_t &id) {
	unsigned long rel_expires = get_jiffies(expires, *base_time_);
	Mutex_Guard<Thread_Mutex> guard(lock_);
	++id_gen_;
	id = id_gen_;
	add_timer_opt(rel_expires, functor, id);
	if (rel_expires < base_->next_timer) {
		base_->next_timer = rel_expires;
		if (thr_id_ > 0) {
			pthread_kill(thr_id_, SIGUSR1);
		}
	}
}

void Timer::mod_timer(unsigned long expires, const Functor &functor, uint32_t old_id, uint32_t &new_id) {
	del_timer(old_id);
	add_timer(expires, functor, new_id);
}

void Timer::del_timer(uint32_t id) {
	Mutex_Guard<Thread_Mutex> guard(lock_);
	valid_set_.erase(id);
}

void Timer::add_timer_opt(unsigned long expires, const Functor &functor, uint32_t id) {
	unsigned long idx = expires - base_->timer_jiffies;
	rec_log(Log::LVL_DEBUG, "add_timer_opt idx %ul", idx);
	Timer_List *list;

	if (idx < TVR_SIZE) {
		int i = expires & TVR_MASK;
		list = &base_->tv1[i];
	} else if (idx < 1 << (TVR_BITS + TVN_BITS)) {
		int i = (expires >> TVR_BITS) & TVN_MASK;
		list = &base_->tv2[i];
	} else if (idx < 1 << (TVR_BITS + 2 * TVN_BITS)) {
		int i = (expires >> (TVR_BITS + TVN_BITS)) & TVN_MASK;
		list = &base_->tv3[i];
	} else if (idx < 1 << (TVR_BITS + 3 * TVN_BITS)) {
		int i = (expires >> (TVR_BITS + 2 * TVN_BITS)) & TVN_MASK;
		list = &base_->tv4[i];
	} else if ((signed long) idx < 0) {	// 若设置一个当前，或者过去的时间，立即执行
		list = &base_->tv1[base_->timer_jiffies & TVR_MASK];
	} else {
		if (idx > 0xffffffffUL) {
			idx = 0xffffffffUL;
			expires = idx + base_->timer_jiffies;
		}
		int i = (expires >> (TVR_BITS + 3 * TVN_BITS)) & TVN_MASK;
		list = &base_->tv5[i];
	}

	valid_set_.insert(id);
	list->push_back(Timer_Data(id, expires, functor));	// FIFO
}

void Timer::loop(void) {
	thr_id_ = pthread_self();
	jiffies_ = 0;
	*base_time_ = Time_Value::gettimeofday();

	timeval wait_time;
	wait_time.tv_sec = std::numeric_limits<time_t>::max();
	wait_time.tv_usec = 0;

	while (1) {
		int ret = select(0, nullptr, nullptr, nullptr, &wait_time);
		if (ret != 0 && errno != EINTR) {
			rec_log(Log::LVL_ABORT, "select ret %d errno %d", ret, errno);
		}
		unsigned long ms_gap = Time_Value::get_msec_gap(Time_Value::gettimeofday(), *base_time_);
		Mutex_Guard<Thread_Mutex> guard(lock_);
		jiffies_ = ms_gap / TICK_MS_GAP;
		timer_loop();
		get_next_wait_time(wait_time);
	}
}

void Timer::get_next_wait_time(timeval &wait) {
	if (jiffies_ >= base_->next_timer) {	// next timer is triggered need to find next
		base_->next_timer = jiffies_ + TVR_MASK;
		for (auto &timer_list : base_->tv1) {
			if (!timer_list.empty()) {
				base_->next_timer = timer_list.begin()->expires;
				rec_log(Log::LVL_DEBUG, "find the next %ul", base_->next_timer);
				break;
			}
		}
	}
	unsigned long jif_gap = base_->next_timer - jiffies_;
	wait.tv_sec = jif_gap / 10;
	wait.tv_usec = jif_gap % 10 * 100000;
}

int cascade(Timer &timer, TVec &tv, int index) {
	for (auto &timer_data : tv[index]) {
		timer.add_timer_opt(timer_data.expires, timer_data.functor, timer_data.id);
	}
	tv[index].clear();
	return index;
}

#define INDEX(N) ((base_->timer_jiffies >> (TVR_BITS + (N) * TVN_BITS)) & TVN_MASK)
void Timer::timer_loop(void) {
	while (jiffies_ >= base_->timer_jiffies) {
		int index = base_->timer_jiffies & TVR_MASK;
		/*
		 * Cascade timers: tvr index 为0时，tv1档的某index就到期了，要将该档里面的移动到tv1档
		 * 比如，60S时，某分钟档位内的timer要挂到60S的档位上
		 */
		if (!index && (!cascade(*this, base_->tv2, INDEX(0)))
				&& (!cascade(*this, base_->tv3, INDEX(1)))
				&& !cascade(*this, base_->tv4, INDEX(2))) {
			cascade(*this, base_->tv5, INDEX(3));
		}
		++base_->timer_jiffies;
		for (auto &timer_data : base_->tv1[index]) {
			if (valid_set_.erase(timer_data.id) > 0) {
				timer_data.functor();
			}
		}
		base_->tv1[index].clear();
	}
}
