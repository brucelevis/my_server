/*
 * Log.h
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef LOG_H_
#define LOG_H_

#include "Singleton.h"

class Log : private noncopyable {
public:
	enum Level {
		LVL_ABORT = 0,
		LVL_ERROR = 1,
		LVL_TRACE_ERROR = 2,
		LVL_INFO = 3,
		LVL_DEBUG = 4,
		LVL_MAX	= 4
	};

	Log(void);
	~Log(void);

	void rec(const Level level, const char *fmt, ...);

private:
	void rec_to_stdout(const int level, const char *fmt, va_list ap);

	const static uint32_t max_buf_size;
	const static uint32_t backtrace_size;
	const static std::string msg_lvl[];
};

#define sLog Singleton<Log>::Instance()

#define rec_log(level, FMT, ...) do {						\
	sLog.rec(level, "%s:%d function %s: "#FMT, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
} while (0)

inline void rec_errno_log(void) {
	rec_log(Log::LVL_ERROR, "%s", strerror(errno));
}

#endif /* LOG_H_ */
