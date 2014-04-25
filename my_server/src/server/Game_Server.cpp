/*
 * Game_Server.cpp
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#include "Game_Server.h"
#include "Net_Define.h"
#include "Tcp_Server.h"
#include "Msg_Block.h"

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
			msg_handle(cid, msg);
			handling_msg_.pop_front();
		}
		{
			Mutex_Guard<Thread_Mutex> guard(msg_lock_);
			while (waiting_msg_.empty()) {
				msg_cond_.wait();
			}
			std::swap(handling_msg_, waiting_msg_);
		}
	}
}

void Game_Server::msg_handle(int cid, const Msg_Block &msg) {
	Msg_Block send_msg = msg;
	int8_t value = 0;
	send_msg.peek_int8(value);
	std::string str;
	send_msg.peek_string(str);
	rec_log(Log::LVL_INFO, "read from client %s", str.c_str());
	if (OFFLINE == value) {
		tcp_server_->drop_handle(cid);
	} else {
		tcp_server_->send_to_client(cid, std::move(send_msg));
	}
}

void Game_Server::push_msg(Msg_Block &&msg_block) {
	Mutex_Guard<Thread_Mutex> guard(msg_lock_);
	waiting_msg_.push_back(msg_block);
	msg_cond_.notify();
}

void Game_Server::close_handle(int cid) {
	Msg_Block msg;
	msg.write_int32(cid);
	msg.write_int8(OFFLINE);
	push_msg(std::move(msg));
}

void Game_Server::test_direct_echo(Msg_Block &&msg_block) {
	int cid = 0;
	msg_block.read_int32(cid);
	tcp_server_->send_to_client(cid, std::move(msg_block));
}
