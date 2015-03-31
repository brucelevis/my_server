/*
 * Time_Test.h
 *
 *  Created on: Nov 9, 2014
 *	  Author: "enjolras"
 */

#ifndef TIME_TEST_H_
#define TIME_TEST_H_

#include "Log.h"

long get_time_usec_gap(const timeval &start, const timeval &end) {
	return (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
}

class Time_Test : private noncopyable {
public:
	Time_Test(std::string &&str) : what(str) {
		gettimeofday(&t_start, 0);
	}
	~Time_Test(void) {
		gettimeofday(&t_end, 0);
		rec_log(Log::LVL_INFO, "%s | usec : %d", what.c_str(), get_time_usec_gap(t_start, t_end));
	}
private:
	std::string what;
	struct timeval t_start;
	struct timeval t_end;
};

#endif /* TIME_TEST_H_ */
