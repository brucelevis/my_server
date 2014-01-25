/*
 * Test_Func.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: "enjolras@163.com"
 */

#include "Test_Func.h"
#include "Msg_Block.h"

void test_msg_block(void) {
	Msg_Block msg_block;
	for (int i = 0; i < 10; ++i) {
		int remainder = i % 2;
		if (0 == remainder) {
			msg_block.write_uint32(123);
		} else if (1 == remainder) {
			msg_block.write_string("456");
		}
		// msg_block.log_contain();
	}
	for (int i = 0; i < 10; ++i) {
		msg_block.write_uint32_tohead(11111);
	}
	for (int i = 0; i < 10; ++i) {
		uint32_t value = 0;
		msg_block.read_uint32(value);
		rec_log(Log::LVL_DEBUG, "%d value : %d", i, value);
	}

	for (int i = 0; i < 10; ++i) {
		std::string str;
		uint32_t value = 0;
		int remainder = i % 2;
		if (0 == remainder) {
			msg_block.read_uint32(value);
			rec_log(Log::LVL_DEBUG, "%d value : %d", i, value);
		} else if (1 == remainder) {
			msg_block.read_string(str);
			rec_log(Log::LVL_DEBUG, "%d value : %s", i, str.c_str());
		}
	}
}
