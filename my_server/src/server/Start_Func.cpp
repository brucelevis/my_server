/*
 * Start_Func.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: "enjolras@163.com"
 */

#include "Start_Func.h"
#include "Game_Server.h"

void start_server(void) {
	Game_Server game_server;
	game_server.init();
	game_server.start();
}

