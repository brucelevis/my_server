#include "Pre_Header.h"
#include "Start_Func.h"

int main(void) {
	signal(SIGPIPE, SIG_IGN);	// ignore broken pipe

	start_server();
	return 0;
}
