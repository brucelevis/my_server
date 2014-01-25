/*
 * Svc.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: "enjolras@163.com"
 */

#include "Svc.h"
#include "Log.h"
#include "Net_Define.h"
#include "Msg_Block.h"

Svc::Svc(void) : cid_(nullcid) {
}

Svc::~Svc(void) {
}

void Svc::reset(void) {
	Sock::fini();
	IPC_SAP::set_fd(nullfd);
	cid_ = nullcid;
	recv_cb_ = nullptr;
	close_cb_ = nullptr;
	output_.clear();
}

void Svc::handle_input(void) {
	Msg_Block msg_block;
	msg_block.recv_msg(recv_func_, 0);
	if (msg_block.readable_bytes() > 0) {
		msg_block.write_uint32_tohead(cid_);
		recv_cb_(std::move(msg_block));
	}
}

int Svc::handle_output(void) {
	Mutex_Guard<Thread_Mutex> guard(output_lock_);
	for (Msg_Block_Deque::iterator it = output_.begin(); it != output_.end(); ) {
		if (SUCCESS == (*it).send_msg(send_func_, 0)) {
			it = output_.erase(it);
		} else {
			break;
		}
	}
	if (output_.empty()) {
		return SUCCESS;
	} else {
		return FAIL;
	}
}

void Svc::handle_close(void) {
	// rec_log(Log::LVL_DEBUG, "close");
	close_cb_(cid_);
}

int Svc::get_fd(void) const {
	return Sock_IO::get_fd();
}

void Svc::set_fd(int fd) {
	Sock_IO::set_fd(fd);
}

void Svc::push_send_msg(Msg_Block &&msg) {
	Mutex_Guard<Thread_Mutex> guard(output_lock_);
	output_.push_back(msg);
}
