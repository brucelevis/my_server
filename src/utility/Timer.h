/*
 * Timer.h
 *
 *  Created on: Dec 12, 2014
 *	  Author: "enjolras"
 *	  timer wheel 参考了 linux kernel timer.c
 *	  1、TVN_BITS
 *	  考虑到游戏服务端的需要
 *	  timer每tick是100ms
 *	  数组的第一维都是一些临近的timer(25s inner) 几乎没有超过1周的timer
 *	  TVR_BITS为8 TVN_BITS为4
 *	  tv1 的tick范围是 [0, 2^8)，即25.5s内的timer会放在tv1中
 *	  tv2 的tick范围是 [2^8, 2^12)，即25.6s至409.5s会放在tv2中
 *	  tv3 的tick范围是 [2^12, 2^16)，即409.6s至6553.5s会放在tv3中
 *	  tv4 的tick范围是 [2^16, 2^20)，即6553.6s至104857.5s会放在tv4中
 *	  tv5 的tick范围是 [2^20, 2^24)，即104857.6s(29hours)至1677721.5(19 days)会放在tv5中
 *	  2、timer不加锁，对timer的修改，将修改操作复制到timer_thr的执行队列中
 *	  3、单例封装，一般来说一个进程一个timer线程足够了，但不强制使用此单例
 *	  4、修改、删除接口不能是异步式的，考虑到同步式增加timer的性能也可以接受，去掉异步式接口
 *	  Intel(R) Core(TM) i7-3630QM CPU @ 2.40GHz 虚拟机
 *	  16个线程，每个增加10W个5S内的timer,最晚完成的在3.8S左右
 *
 *	  ps:
 *	  占用了SIGUSR1信号
 *	  todo 确认多线程情况下同一个信号的复用，不同的线程是否能都用同时使用自己的handler函数，不影响其它线程
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Functor.h"
#include "Singleton.h"

class Nonblock_Worker;
struct TVec_Base;
class Time_Value;
class Timer : private noncopyable {
public:
	Timer(void);
	~Timer(void) = default;

	void init(void);
	void start(void);
	void add_timer(unsigned long expires, const Functor &functor);
	void add_timer(unsigned long expires, const Functor &functor, uint32_t &id);
	void mod_timer(unsigned long expires, const Functor &functor, uint32_t old_id, uint32_t &new_id);
	void del_timer(uint32_t id);
	void add_timer_opt(unsigned long expires, const Functor &functor, uint32_t id);
private:
	void loop(void);
	void timer_loop(void);
	void get_next_wait_time(timeval &wait);
private:
	unsigned long jiffies_;		// 节拍，每次timer_loop之前根据当前时间计算
	std::thread thr_;			// timer 线程
	pthread_t thr_id_;			// 线程pid std::thread 返回的 pthread id有问题
	boost::scoped_ptr<TVec_Base> base_;				// timing wheel
	boost::scoped_ptr<Time_Value> base_time_;		// jiffies的基础计算时间
	Thread_Mutex lock_;
	uint32_t id_gen_;								// 唯一标记timer
	std::unordered_set<uint32_t> valid_set_;		// 有效的timer
};

#define sTimer Singleton<Timer>::Instance()

#endif /* TIMER_H_ */
