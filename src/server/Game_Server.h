/*
 * Game_Server.h
 *
 *  Created on: Jan 20, 2014
 *	  Author: "enjolras@163.com"
 */

#ifndef GAME_SERVER_H_
#define GAME_SERVER_H_

#include "Pre_Header.h"
#include "Condition.h"

class Msg_Block;
class Tcp_Server;
class Game_Server {
public:
	typedef std::deque<Msg_Block> Msg_Block_Deque;
	Game_Server(void);
	~Game_Server(void);

	void init(void);
	void start(void);

private:
	// main thread : msg handle loop
	void msg_loop(void);
	void push_msg(Msg_Block &&msg_block);
	void close_handle(int cid);

	void msg_handle(int cid, const Msg_Block &msg);
	void protobuf_msg_handle(int cid, Msg_Block &msg);

private:
	Thread_Mutex msg_lock_;
	Condition msg_cond_;
	std::deque<Msg_Block> waiting_msg_;
	std::deque<Msg_Block> handling_msg_;

	// for client connect
	boost::scoped_ptr<Tcp_Server> tcp_server_;
	std::thread msg_thr_;
};

#endif /* GAME_SERVER_H_ */
