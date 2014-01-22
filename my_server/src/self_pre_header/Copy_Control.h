/*
 * Copy_Control.h
 *
 *  Created on: Jan 15, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef COPY_CONTROL_H_
#define COPY_CONTROL_H_

class copyable {
};

class noncopyable {
protected:
	noncopyable(void) = default;
	~noncopyable(void) = default;
private:
	noncopyable(const noncopyable&) = delete;
	noncopyable(noncopyable&&) = delete;

	noncopyable& operator=(const noncopyable&) = delete;
	noncopyable& operator=(noncopyable&&) = delete;
};

#endif /* COPY_CONTROL_H_ */
