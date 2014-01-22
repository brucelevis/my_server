/*
 * Msg_Block.cpp
 *
 *  Created on: Jan 14, 2014
 *      Author: "enjolras@163.com"
 */

#include "Msg_Block.h"
#include "Svc.h"

Msg_Block::Msg_Block(void) : Msg_Block(DEFAULT_RESERVE, DEFAULT_CONTENT) {

}

Msg_Block::Msg_Block(size_t reserve_size, size_t content_size) : data_(reserve_size + content_size), rptr_(reserve_size), wptr_(rptr_) {

}

int Msg_Block::recv_msg(const SendRecv_Func &func, int flags) {
	while (1) {
		int recv_able = writable_bytes();
		int recved = func(get_wptr(), recv_able, flags);
		if (recved > 0) {	// nothing left to read
			wptr_ += recved;
			if (recved == recv_able) {
				make_space(recved);
				continue;
			} else {
				// recved less than recv_able
				// be likely to no more bytes left to read
				// in case of some bytes left, wait for next handle_input
				break;
			}
		} else {
			return FAIL;
		}
	}
	return SUCCESS;
}

int Msg_Block::send_msg(const SendRecv_Func &func, int flags) {
	int total_send = readable_bytes();
	while (total_send > 0) {
		int send_able = readable_bytes();
		int sended = func(const_cast<char *>(get_rptr()), send_able, flags);
		if (sended < 0) {
			return FAIL;
		} else {
			total_send -= sended;
			rptr_ += sended;
		}
	}
	return SUCCESS;
}
