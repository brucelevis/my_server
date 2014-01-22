/*
 * IPC_SAP.h
 *
 *  Created on: Jan 8, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef IPC_SAP_H_
#define IPC_SAP_H_

#include "Pre_Header.h"

class IPC_SAP : private noncopyable {
public:
	enum {
		NONBLOCK = 0,
		MAX_VALUE = 0,
	};

	inline void set_fd(int fd);
	inline int get_fd(void) const;
	int enable (int value);
	int disable (int value);

protected:
	IPC_SAP(void);
	~IPC_SAP(void);

protected:
	int fd_;
};

inline void IPC_SAP::set_fd(int fd) {
	fd_ = fd;
}

inline int IPC_SAP::get_fd(void) const {
	return fd_;
}

#endif /* IPC_SAP_H_ */
