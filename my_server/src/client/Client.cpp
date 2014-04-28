/*
 * Client.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: "enjolras"
 */

#include "Client.h"
#include "Tcp_Client.h"
#include "Net_Define.h"
#include "Msg_Block.h"
#include "Log.h"

Client::Client(void) {
}

Client::~Client(void) {
}

void Client::init(void) {
	tcp_client_.reset(new Tcp_Client);
	using namespace std::placeholders;
	tcp_client_->init("127.0.0.1", LISTEN_PORT, std::bind(&Client::recv_handle, this, _1), std::bind(&Client::close_handle, this, _1));
}

void Client::start(void) {
	tcp_client_->start();

	thr_ = std::thread(std::bind(&Client::loop, this));
	thr_.join();
}

void Client::recv_handle(const Msg_Block &msg) {
	Msg_Block ret_msg = msg;
	uint32_t cid;
	ret_msg.read_uint32(cid);
	std::string line;
	ret_msg.peek_string(line);
	rec_log(Log::LVL_INFO, "ret from server %d : %s", cid, line.c_str());
}

void Client::close_handle(int cid) {
	exit(0);
}

void Client::loop(void) {
	rec_log(Log::LVL_INFO, "start of client loop");
	std::string line;
	Msg_Block msg;
	while (std::getline(std::cin, line)) {
		msg.reset();
		msg.write_string(line);
		rec_log(Log::LVL_INFO, "send to server %s", line.c_str());
		tcp_client_->send(std::move(msg));
	}
}
