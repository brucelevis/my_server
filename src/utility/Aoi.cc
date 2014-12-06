/*
 * Aoi.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: "enjolras"
 */

#include <Aoi.h>
#include "Log.h"

void Aoi::enter(SObject &new_ob, SObjectOrderSet &new_ob_i) {
	new_ob_i.clear();
	if (exist_map_.count(new_ob->get_id()) != 0) {
		return;
	}
	exist_map_.insert(std::make_pair(new_ob->get_id(), new_ob));

	// 因为是链表接口，不能用折半查找，可以看出这里是N*N的复杂度，因为enter leave相对move频率较低 暂不优化
	// 遍历x链，插入新的对象，计算有多少对象是新插入对象能够看到的
	int distance = new_ob->get_radius();
	bool first_bigger_flag = false;
	PosIt insert_pos = x_list_.end();
	for (PosIt iter = x_list_.begin(); iter != x_list_.end(); ++iter) {
		int diff = (*iter)->get_x() - new_ob->get_x();
		if (abs(diff) <= distance) {	// new_ob_i 能看到的对象
			new_ob_i.insert(*iter);
		}
		if (!first_bigger_flag && diff > 0) {	// 第一次找到比新插入对象X坐标大的对象，那么新对象将排在此对象前面
			insert_pos = iter;
			first_bigger_flag = true;
		}
		if (diff > distance) {
			break;
		}
	}
	insert_pos = x_list_.insert(insert_pos, new_ob);
	new_ob->set_x_it(insert_pos);

	// 遍历y链
	first_bigger_flag = false;
	insert_pos = y_list_.end();
	for (PosIt iter = y_list_.begin(); iter != y_list_.end(); ++iter) {
		int diff = (*iter)->get_y() - new_ob->get_y();
		if (abs(diff) <= distance) {	// 所有新进对象能看到的对象
			new_ob_i.insert(*iter);
		}
		if (!first_bigger_flag && diff > 0) {
			insert_pos = iter;
			first_bigger_flag = true;
		}
		if (diff > distance) {
			break;
		}
	}
	insert_pos = y_list_.insert(insert_pos, new_ob);
	new_ob->set_y_it(insert_pos);
}

void Aoi::leave(uint32_t id, SObjectOrderSet &leave_object_i) {
	leave_object_i.clear();

	SObjUnorderMap::iterator obj_iter = exist_map_.find(id);
	if (obj_iter == exist_map_.end()) {
		rec_log(Log::LVL_ERROR, "object %d not found", id);
		return;
	}
	SObject object = obj_iter->second;

	get_range(object, leave_object_i);

	x_list_.erase(object->get_x_it());
	y_list_.erase(object->get_y_it());
	exist_map_.erase(id);
}

void Aoi::get_range(const SObject &object, SObjectOrderSet &obj_i) {
	obj_i.clear();
	int distance = object->get_radius();

	// X链
	// ----------object - find distance ----------
	for (PosIt iter = ++object->get_x_it(); iter != x_list_.end(); ++iter) {	// 向上找
		if ((*iter)->get_x() - object->get_x() > distance) {
			break;
		}
		obj_i.insert(*iter);
	}
	// ---------find distance -object-----------------
	for (RPosIt iter = RPosIt(object->get_x_it()); iter != x_list_.rend(); ++iter) {	// 用反向迭代器向下找
		if (object->get_x() - (*iter)->get_x() > distance) {
			break;
		}
		obj_i.insert(*iter);
	}

	// y 链
	for (PosIt iter = ++object->get_y_it(); iter != y_list_.end(); ++iter) {
		if ((*iter)->get_y() - object->get_y() > distance) {
			break;
		}
		obj_i.insert(*iter);
	}
	for (RPosIt iter = RPosIt(object->get_y_it()); iter != y_list_.rend(); ++iter) {	// 用反向迭代器向下找
		if (object->get_y() - (*iter)->get_y() > distance) {
			break;
		}
		obj_i.insert(*iter);
	}
}

void Aoi::move(int id, int x_add, int y_add, SObjectOrderSet &leave_i, SObjectOrderSet &move_i, SObjectOrderSet &enter_i) {
	leave_i.clear();
	move_i.clear();
	enter_i.clear();
	if (x_add == 0 && y_add == 0) {
		return;
	}
	SObjUnorderMap::iterator obj_iter = exist_map_.find(id);
	if (obj_iter == exist_map_.end()) {
		return;
	}
	SObject object = obj_iter->second;

	SObjectOrderSet old_set;	// object 原所在地的对象
	get_range(object, old_set);

	int new_x = object->get_x() + x_add;
	int new_y = object->get_y() + y_add;
	update_position(object, new_x, new_y);

	SObjectOrderSet new_set;	// object 新所在地的对象
	get_range(object, new_set);

	for (SObjectOrderSet::iterator it = old_set.begin(); it != old_set.end(); ++it) {
		if (new_set.count(*it) > 0) {
			move_i.insert(*it);	// move_set = old_set MIX new_set
		} else {
			leave_i.insert(*it); // leave_set = old_set SUB new_set
		}
	}

	for (SObjectOrderSet::iterator it = new_set.begin(); it != new_set.end(); ++it) {
		if (move_i.count(*it) == 0) {
			enter_i.insert(*it);	// enter_set = new_set SUB move_set
		}
	}
}

void Aoi::update_position(SObject &object, int x, int y) {
	int old_x = object->get_x();
	int old_y = object->get_y();
	object->set_x(x);
	object->set_y(y);

	// 更新X链
	if (x > old_x) {
		PosIt x_it;
		for (x_it = x_list_.erase(object->get_x_it()); x_it != x_list_.end(); ++x_it) {
			if (object->get_x() - (*x_it)->get_x() < 0) {
				break;
			}
		}
		object->set_x_it(x_list_.insert(x_it, object));
	} else if (x < old_x) {
		RPosIt r_x_it(x_list_.erase(object->get_x_it()));
		for (; r_x_it != x_list_.rend(); ++r_x_it) {
			if (object->get_x() - (*r_x_it)->get_x() > 0) {
				break;
			}
		}
		object->set_x_it(x_list_.insert(r_x_it.base(), object));
	}

	// y 链
	if (y > old_y) {
		PosIt y_it;
		for (y_it = y_list_.erase(object->get_y_it()); y_it != y_list_.end(); ++y_it) {
			if (object->get_y() - (*y_it)->get_y() < 0) {
				break;
			}
		}
		object->set_y_it(y_list_.insert(y_it, object));
	} else if (y < old_y) {
		RPosIt r_y_it(y_list_.erase(object->get_y_it()));
		for (; r_y_it != y_list_.rend(); ++r_y_it) {
			if (object->get_y() - (*r_y_it)->get_y() > 0) {
				break;
			}
		}
		object->set_y_it(y_list_.insert(r_y_it.base(), object));
	}
}

void Aoi::output_all_object(void) {
	output_object(x_list_, "x_list");
	output_object(y_list_, "y_list");
}

void Aoi::output_object(const SObjList &list, const std::string &str) {
	rec_log(Log::LVL_INFO, "%s", str.c_str());
	for (auto &it : list) {
		rec_log(Log::LVL_INFO, "object %d {%d,%d}", it->get_id(), it->get_x(), it->get_y());
	}
}
