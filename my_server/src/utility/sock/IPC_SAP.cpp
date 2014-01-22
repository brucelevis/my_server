/*
 * IPC_SAP.cpp
 *
 *  Created on: Jan 8, 2014
 *      Author: "enjolras@163.com"
 */

#include "IPC_SAP.h"
#include "Log.h"

IPC_SAP::IPC_SAP(void) :fd_(nullfd) {
}

IPC_SAP::~IPC_SAP(void) {
}

int IPC_SAP::enable (int value) {
	int ret = SUCCESS;
	switch (value) {
	case NONBLOCK: {
		int val = ::fcntl(fd_, F_GETFL, 0);
		if (val == -1) {
			rec_errno_log();
			return FAIL;
		}
		::fcntl(fd_, F_SETFL, val | O_NONBLOCK);
		break;
	}
	default:
		ret = FAIL;
		break;
	}
	return ret;
}

int IPC_SAP::disable (int value) {
	int ret = SUCCESS;
	switch (value) {
	case NONBLOCK: {
		int val = ::fcntl(fd_, F_GETFL, 0);
		if (val == -1) {
			rec_errno_log();
			return FAIL;
		}
		::fcntl(fd_, F_SETFL, val &= ~(O_NONBLOCK));
		break;
	}
	default:
		ret = FAIL;
		break;
	}
	return ret;
}
