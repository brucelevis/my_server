/*
 * Msg_Block.cc
 *
 *  Created on: Jan 14, 2014
 *	  Author: "enjolras@163.com"
 */

#include "Msg_Block.h"
#include "Tcp_Connection.h"

Msg_Block::Msg_Block(void) : Msg_Block(DEFAULT_RESERVE, DEFAULT_CONTENT) {

}

Msg_Block::Msg_Block(size_t reserve_size, size_t content_size) : data_(reserve_size + content_size), rptr_(reserve_size), wptr_(rptr_) {

}

void Msg_Block::recv_msg(const SendRecv_Func &func, int flags) {
	while (1) {
		int recv_able = writable_bytes();
		int recved = func(get_wptr(), recv_able, flags);
		if (recved > 0) {
			wptr_ += recved;
			if (recved == recv_able) {
				make_space(recved);
				continue;
			} else {
				// recved less than recv_able
				break;
			}
		} else {
			break;
		}
	}
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
