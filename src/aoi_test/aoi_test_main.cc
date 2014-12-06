/*
 * aoi_test_main.cc
 *
 *  Created on: Oct 21, 2014
 *      Author: "enjolras"
 */

#include "Aoi.h"
#include "Log.h"
#include "Time_Test.h"

typedef Object::SObject SObject;
typedef Aoi::SObjectOrderSet SObjectOrderSet;
const int32_t DISTANCE = 30;
const int32_t MAX_X = 300;
const int32_t MAX_Y = 300;
const uint32_t MAX_OBJECT = 300;
const uint32_t MOVE_TIMES = 10;
const int32_t MAX_MOVE_STEP = 2;
const int32_t MOVE_STEP_REM = MAX_MOVE_STEP * 2 + 1;

// object 创建函数，实际应用中用单例的产生器
SObject object_generate(uint32_t id, int x, int y) {
	SObject object = std::make_shared<Object>(id, Coord(x, y), DISTANCE);
	return object;
}

void time_test(Aoi &aoi) {
	rec_log(Log::LVL_INFO, "begin move object");
	SObjectOrderSet leave_set;
	SObjectOrderSet move_set;
	SObjectOrderSet enter_set;
	{
		char info[256] = {0};
		snprintf(info, sizeof(info), "object nums %d, move times %d", MAX_OBJECT, MOVE_TIMES);
		Time_Test tester(info);
		for (uint32_t i = 0; i < MAX_OBJECT; ++i) {
			for (uint32_t j = 0; j < MOVE_TIMES; ++j) {
				aoi.move(i, random() % MOVE_STEP_REM - MAX_MOVE_STEP, random() % MOVE_STEP_REM - MAX_MOVE_STEP, leave_set, move_set, enter_set);
			}
		}
	}
}

void output_set(const SObjectOrderSet &set, const char *str) {
	rec_log(Log::LVL_INFO, "%s", str);
	for (auto &it : set) {
		rec_log(Log::LVL_INFO, "object %d {%d,%d}", it->get_id(), it->get_x(), it->get_y());
	}
}

void correctness_test(Aoi &aoi) {
	SObject object;
	SObjectOrderSet leave_set;
	SObjectOrderSet move_set;
	SObjectOrderSet enter_set;
	aoi.output_all_object();
	for (uint32_t i = 0; i < MAX_OBJECT; ++i) {
		int result = aoi.get_object(i, object);
		if (SUCCESS == result) {
			int old_x = object->get_x();
			int old_y = object->get_y();
			aoi.move(i, random() % MOVE_STEP_REM - MAX_MOVE_STEP, random() % MOVE_STEP_REM - MAX_MOVE_STEP, leave_set, move_set, enter_set);
			int new_x = object->get_x();
			int new_y = object->get_y();
			rec_log(Log::LVL_INFO, "object %d, move from {%d,%d} to {%d,%d}", i, old_x, old_y, new_x, new_y);
			output_set(leave_set, "leave_set");
			output_set(move_set, "move_set");
			output_set(enter_set, "enter_set");
		} else {
			rec_log(Log::LVL_ERROR, "object %d can't be found", i);
		}
	}
	aoi.output_all_object();
}

int main() {
	srandom(time(NULL));
	Aoi aoi;

	rec_log(Log::LVL_INFO, "begin add object");
	SObjectOrderSet set;
	for (uint32_t i = 0; i < MAX_OBJECT; ++i) {
		SObject object = object_generate(i, random() % MAX_X, random() % MAX_Y);
		aoi.enter(object, set);
		// aoi.output_all_object();
	}

	int opt = 0;
	std::cout<<"input 1 to time test \n"
			"input 2 to correctness test\n"
			"input non-integer to exit"<<std::endl;
	while (std::cin>>opt) {
		switch (opt) {
		case 1:
			time_test(aoi);
			break;
		case 2:
			correctness_test(aoi);
			break;
		default:
			break;
		}
	}

	rec_log(Log::LVL_INFO, "begin leave object");
	for (uint32_t i = 0; i < MAX_OBJECT; ++i) {
		aoi.leave(i, set);
		// aoi.output_all_object();
	}

	return 0;
}



