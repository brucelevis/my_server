/*
 * Aoi.h
 *
 *  Created on: Oct 20, 2014
 *      Author: "enjolras"
 *      只负责 aoi 计算 是否可走的判定，建议放在场景中，obj id在地图进程中，由专门的生成器生成
 */

#ifndef AOI_H_
#define AOI_H_

#include "Pre_Header.h"
#include "Define.h"
#include "Object.h"

class Aoi {
public:
	Aoi(void) = default;
	~Aoi(void) = default;

	typedef Object::SObject SObject;
	typedef Object::SObjList SObjList;
	typedef Object::PosIt PosIt;
	typedef Object::RPosIt RPosIt;
	typedef std::unordered_map<uint32_t, SObject> SObjUnorderMap;
	typedef std::set<SObject> SObjectOrderSet;
	typedef std::vector<SObject> SObjectVec;

	// new_ob object 进入场景 返回new_ob视野范围内的对象
	void enter(SObject &new_ob, SObjectOrderSet &new_ob_i);
	// 移动 返回需要通知object离开的leave_i 需要通知object移动的move_i 需要通知object出现的enter_i
	void move(int id, int x_add, int y_add, SObjectOrderSet &leave_i, SObjectOrderSet &move_i, SObjectOrderSet &enter_i);
	// object 离开场景，返回object视野范围的对象
	void leave(uint32_t id, SObjectOrderSet &leave_object_i);

	// 获得object 视野范围内的对象
	void get_range(const SObject &object, SObjectOrderSet &obj_i);

	// 根据ID获得对象，测试用，Aoi服务没必要提供Object资源管理
	inline int get_object(uint32_t id, SObject &object);

	// 打印X链 Y链
	void output_all_object(void);

private:
	// 更新object 的位置信息
	void update_position(SObject &object, int x, int y);
	void output_object(const SObjList &list, const std::string &str);

private:
	SObjList x_list_;				// 十字链表的x
	SObjList y_list_;				// 十字链表的y
	SObjUnorderMap exist_map_;		// 存在集合	长时间存在的，内有大量对象, 此种情况下 unordered_map 性能要优于 基于平衡二叉树的 map
};

inline int Aoi::get_object(uint32_t id, SObject &object) {
	SObjUnorderMap::const_iterator it = exist_map_.find(id);
	if (it != exist_map_.end()) {
		object = it->second;
		return SUCCESS;
	} else {
		return FAIL;
	}
}

#endif /* AOI_H_ */
