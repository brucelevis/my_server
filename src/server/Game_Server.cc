/*
 * Game_Server.cc
 *
 *  Created on: Jan 20, 2014
 *	  Author: "enjolras@163.com"
 */

#include "Game_Server.h"
#include "Net_Define.h"
#include "Tcp_Server.h"
#include "Msg_Block.h"
#include "login.pb.h"
#include "reg.pb.h"
#include "pb.h"
#include "Msg_Block_Stream.h"

Game_Server::Game_Server(void) : msg_cond_(msg_lock_) {
}

Game_Server::~Game_Server(void) {
}

void Game_Server::init(void) {
	tcp_server_.reset(new Tcp_Server);
	using namespace std::placeholders;
	tcp_server_->init(LISTEN_PORT, MAX_LISTEN, std::bind(&Game_Server::push_msg, this, _1), std::bind(&Game_Server::close_handle, this, _1));
}

void Game_Server::start(void) {
	tcp_server_->start();

	msg_thr_ = std::thread(std::bind(&Game_Server::msg_loop, this));
	msg_thr_.join();
}

void Game_Server::msg_loop(void) {
	while (1) {
		while (!handling_msg_.empty()) {
			Msg_Block &msg = handling_msg_.front();
			int cid = 0;
			msg.read_int32(cid);
			// protobuf_msg_handle(cid, msg);
			msg_handle(cid, msg);
			handling_msg_.pop_front();
		}
		{
			Mutex_Guard<Thread_Mutex> guard(msg_lock_);
			while (waiting_msg_.empty()) {	// 防止spurious wakeup
				msg_cond_.wait();
			}
			using std::swap;
			swap(handling_msg_, waiting_msg_);	// 当消息都处理完了，并且有消息打包好了，将等待处理的消息，放入处理队列
		}
	}
}

void Game_Server::msg_handle(int cid, const Msg_Block &msg) {
	Msg_Block send_msg = msg;
	int32_t value = 0;
	send_msg.peek_int32(value);
	if (MSG_OFFLINE == value) {
		tcp_server_->drop_handle(cid);
	} else {
		tcp_server_->send_to_client(cid, std::move(send_msg));
	}
}

void Game_Server::protobuf_msg_handle(int cid, Msg_Block &msg) {
	uint32_t msg_id = 0;
	msg.read_uint32(msg_id);
	if (MSG_OFFLINE == msg_id) {
		tcp_server_->drop_handle(cid);
	} else {
		switch (msg_id) {
		case MSG_LOGIN: {
			MSG::login login;
			login.ParseFromArray(msg.get_rptr(), msg.readable_bytes());
			rec_log(Log::LVL_INFO, "login ret msg : role id : %ld, account : %s", login.role_id(), login.account().c_str());
			break;
		}
		case MSG_REG: {
			MSG::reg reg;
			reg.ParseFromArray(msg.get_rptr(), msg.readable_bytes());
			rec_log(Log::LVL_INFO, "reg ret msg : career : %d, sex : %d, account : %s", reg.career(), reg.sex(), reg.account().c_str());
			break;
		}
		default:
			rec_log(Log::LVL_INFO, "unandle message from server");
			msg.log_contain();
			break;
		}
	}
}

void Game_Server::push_msg(Msg_Block &&msg_block) {
	Mutex_Guard<Thread_Mutex> guard(msg_lock_);
	waiting_msg_.push_back(msg_block);
	msg_cond_.notify();
}

void Game_Server::close_handle(int cid) {
	// rec_log(Log::LVL_INFO, "cid %d drop handle", cid);
	Msg_Block msg;
	msg.write_int32(cid);
	msg.write_int32(MSG_OFFLINE);
	push_msg(std::move(msg));
}
