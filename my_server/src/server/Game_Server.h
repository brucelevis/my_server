/*
 * Game_Server.h
 *
 *  Created on: Jan 20, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef GAME_SERVER_H_
#define GAME_SERVER_H_

#include "Pre_Header.h"

class Msg_Block;
class Tcp_Server;
class Game_Server {
public:
	typedef std::deque<Msg_Block> Msg_Block_Deque;
	Game_Server(void);
	~Game_Server(void);

private:
	// when msg_ deque is empty try to move input_ to it
	Thread_Mutex input_lock_;
	std::deque<Msg_Block> input_;
	Thread_Mutex msg_lock_;
	std::deque<Msg_Block> msg_;

	// for client connect
	boost::scoped_ptr<Tcp_Server> tcp_server_;
};

#endif /* GAME_SERVER_H_ */
