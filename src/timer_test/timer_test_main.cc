/*
 * timer_test_main.cc
 *
 *  Created on: Dec 13, 2014
 *	  Author: "enjolras"
 */

#include "Timer.h"
#include "Time_Value.h"
#include "Date_Time.h"
#include "Log.h"
#include "Time_Test.h"

int g_counter = 0;
void add_g_counter(void) {
	++g_counter;
}

void input_to_test(void) {
	int jif;
	int type;
	uint32_t id;
	rec_log(Log::LVL_INFO, "input type 0 (add) 1 (del) 2(mod)");
	while(std::cin>>type) {
		switch (type) {
		case 0: {
			rec_log(Log::LVL_INFO, "input jif");
			std::cin>>jif;
			Date_Time date;
			Time_Value now = Time_Value::gettimeofday();
			sTimer.add_timer(jif, [date, now, jif] () -> void {
				Time_Value tigger_time = Time_Value::gettimeofday();
				rec_log(Log::LVL_INFO, "register at time : (%d:%d:%d)%d-%d, tigger at %d-%d jiffies : %d", date.hour(), date.minute(), date.second()
						,now.sec(), now.usec(), tigger_time.sec(), tigger_time.usec(), jif);
			}, id);
			break;
		}
		case 1: {
			sTimer.del_timer(id);
			rec_log(Log::LVL_INFO, "del timer %d", id);
			break;
		}
		case 2: {
			rec_log(Log::LVL_INFO, "input jif");
			uint32_t old_id = id;
			std::cin>>jif;
			Date_Time date;
			Time_Value now = Time_Value::gettimeofday();
			sTimer.mod_timer(jif, [date, now, jif] () -> void {
				Time_Value tigger_time = Time_Value::gettimeofday();
				rec_log(Log::LVL_INFO, "register at time : (%d:%d:%d)%d-%d, tigger at %d-%d jiffies : %d", date.hour(), date.minute(), date.second()
						,now.sec(), now.usec(), tigger_time.sec(), tigger_time.usec(), jif);
			}, id, id);
			rec_log(Log::LVL_INFO, "mod timer from %d to %d", old_id, id);
			break;
		}
		default:
			rec_log(Log::LVL_INFO, "wrong input %d input type 0 (add) 1 (del) 2(mod)", type);
			break;
		}


	}
}

void random_test(void) {
	uint32_t id;
	std::vector<int> jiffies_vec(100000);
	for (size_t i = 0; i < jiffies_vec.size(); ++i) {
		jiffies_vec[i] = rand() % 50;
	}
	{
		Time_Test test("random test");
		for (int i : jiffies_vec) {
			// Date_Time now;
			// sTimer.add_timer(i, [now, i] () -> void { rec_log(Log::LVL_INFO, "register at time : %d-%d-%d, jiffies : %d", now.hour(), now.minute(), now.second(), i); });
			sTimer.add_timer(i, add_g_counter, id);
		}
	}
}

void other_thr_fun(void) {	// 测试signal是否也会打断其它线程(不会)
	timeval wait_time;
	wait_time.tv_sec = std::numeric_limits<time_t>::max();
	wait_time.tv_usec = 0;

	while (1) {
		int ret = select(0, nullptr, nullptr, nullptr, &wait_time);
		if (ret != 0 && errno == EINTR) {
			rec_log(Log::LVL_ABORT, "select ret %d errno %d", ret, errno);
		}
	}
}

typedef std::array<std::thread, 16> thr_arr;

int main(void)
{
	srandom(time(0));
//	std::thread other_thr(other_thr_fun);
//	other_thr.detach();
	sTimer.init();
	sTimer.start();
	g_counter = 0;
	input_to_test();
//	thr_arr arr;
//	for (auto &thr : arr) {
//		thr = std::thread(random_test);
//		thr.detach();
//	}
//	getchar();
//	std::cout<<g_counter<<std::endl;

	return 0;
}
