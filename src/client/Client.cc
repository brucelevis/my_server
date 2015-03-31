/*
 * Client.cc
 *
 *  Created on: Apr 23, 2014
 *	  Author: "enjolras"
 */

#include "Client.h"
#include "Tcp_Client.h"
#include "Net_Define.h"
#include "Msg_Block.h"
#include "Log.h"
#include "login.pb.h"
#include "reg.pb.h"
#include "pb.h"
#include "Msg_Block_Stream.h"

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

	thr_ = std::thread(std::bind(&Client::protobuf_loop, this));
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
	Msg_Block msg_block;
	while (std::getline(std::cin, line)) {
		msg_block.reset();
		msg_block.write_string(line);
		rec_log(Log::LVL_INFO, "send to server %s", line.c_str());
		tcp_client_->send(std::move(msg_block));
	}
}

void Client::protobuf_loop(void) {
	Msg_Block msg_block;
	Msg_Block_OStream output_stream(&msg_block);
	while (1) {
		msg_block.reset();
		if (random() % 2 == 0) {
			MSG::login login;
			login.set_role_id(1);
			login.set_account("enjolras");
			msg_block.write_uint32(login.ByteSize() + sizeof(MSG_ID_TYPE));
			msg_block.write_uint32(MSG_LOGIN);
			login.SerializeToZeroCopyStream(&output_stream);
		} else {
			MSG::reg reg;
			reg.set_career(0);
			reg.set_sex(1);
			reg.set_account("yunonly");
			msg_block.write_uint32(reg.ByteSize() + sizeof(MSG_ID_TYPE));
			msg_block.write_uint32(MSG_REG);
			reg.SerializeToZeroCopyStream(&output_stream);
		}
		// msg_block.log_contain();
		tcp_client_->send(std::move(msg_block));
		sleep(3);
	}
}


