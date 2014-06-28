/*
 * main.cc
 *
 *  Created on: Apr 23, 2014
 *      Author: "enjolras"
 */

#include "Pre_Header.h"
#include "Client.h"

void start_client(void) {
	Client client;
	client.init();
	client.start();
}

int main(void) {
	start_client();
	return 0;
}


