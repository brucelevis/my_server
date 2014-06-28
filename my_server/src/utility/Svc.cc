/*
 * Svc.cc
 *
 *  Created on: Jan 13, 2014
 *      Author: "enjolras@163.com"
 */

#include "Svc.h"
#include "Log.h"
#include "Net_Define.h"
#include "Msg_Block.h"

Svc::Svc(void) : input_(new Msg_Block) {
}

Svc::~Svc(void) {
	Sock::fini();
}

void Svc::reset(void) {
	Event::reset();
	Sock::fini();
	IPC_SAP::set_fd(nullfd);
	recv_cb_ = nullptr;
	close_cb_ = nullptr;
	output_.clear();
}

void Svc::handle_input(void) {
	input_->recv_msg(recv_func_, 0);
	while (input_->readable_bytes() > sizeof(uint32_t)) {
		uint32_t len;
		input_->read_uint32(len);
		if (input_ ->readable_bytes() >= len) {	// 长度足够打包了 组包，std::move 交给上层处理
			Msg_Block packed_msg;
			packed_msg.write_uint32_tohead(get_cid());
			packed_msg.write_bytes(input_->get_rptr(), len);
			recv_cb_(std::move(packed_msg));
			input_->back_rptr(sizeof(uint32_t));
			input_->back_wptr(len + sizeof(uint32_t));
		} else {
			input_->back_rptr(sizeof(uint32_t));
			break;
		}
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
	close_cb_(get_cid());
}

int Svc::get_fd(void) const {
	return Sock_IO::get_fd();
}

void Svc::set_fd(int fd) {
	Sock_IO::set_fd(fd);
}

void Svc::push_send_msg(Msg_Block &&msg) {
	Mutex_Guard<Thread_Mutex> guard(output_lock_);
	if (output_.empty()) {
		if (SUCCESS == msg.send_msg(send_func_, 0)) {
			return;
		}
	}
	output_.push_back(msg);
}
