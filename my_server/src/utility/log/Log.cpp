/*
 * Log.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#include "Log.h"
#include "Pre_Header.h"

Log::Log(void) {

}

Log::~Log(void) {

}

const uint32_t Log::max_buf_size = 4096;
const uint32_t Log::backtrace_size = 256;
const std::string Log::msg_lvl[] = {
		"[LVL_ABORT] ",
		"[LVL_ERROR] ",
		"[LVL_DEBUG] ",
		"[LVL_TRACE_ERROR] "
};

void Log::rec(const Level level, const char *fmt, ...) {
	if (level > LVL_MAX || level < 0) {
		return;
	}

	va_list	ap;
	va_start(ap, fmt);
	rec_to_stdout(level, fmt, ap);
	va_end(ap);
}

void Log::rec_to_stdout(const int level, const char *fmt, va_list ap) {
	struct tm tm_v;
	time_t time_v = time(NULL);
	localtime_r(&time_v, &tm_v);

	std::stringstream msg_stream;
	msg_stream << msg_lvl[level];
	msg_stream << "<pid=" << (int)getpid() << "|tid=" << std::this_thread::get_id()
			<< "> (" << (tm_v.tm_hour) << ":" << (tm_v.tm_min) << ":" << (tm_v.tm_sec) << ") ";

	char line_buf[max_buf_size];
	memset(line_buf, 0, sizeof(line_buf));
	vsnprintf(line_buf, sizeof(line_buf), fmt, ap);

	msg_stream << line_buf;

	if (level == LVL_TRACE_ERROR) {
		int nptrs;
		void *buffer[backtrace_size];
		char **strings;
		nptrs = backtrace(buffer, backtrace_size);
		strings = backtrace_symbols(buffer, nptrs);
		if (strings == NULL)
			return ;

		msg_stream << std::endl;
		for (int i = 0; i < nptrs; ++i) {
			msg_stream << (strings[i]) << std::endl;
		}
		free(strings);
	}

	std::cout<<msg_stream.str()<<std::endl;
}
