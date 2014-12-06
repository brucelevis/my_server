/*
 * Object.h
 *
 *  Created on: Oct 20, 2014
 *      Author: "enjolras"
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Pre_Header.h"

struct Coord {
	Coord(int32_t x, int32_t y) : x_(x), y_(y) {}
	~Coord(void) {}
	int32_t x_;
	int32_t y_;
};

class Object {
public:
	Object(uint32_t id, const Coord &coord, uint32_t radius);
	virtual ~Object(void);

	typedef std::shared_ptr<Object> SObject;
	typedef std::list<SObject> SObjList;
	typedef SObjList::iterator PosIt;
	typedef SObjList::reverse_iterator RPosIt;

	inline uint32_t get_id(void) const;
	inline const Coord& get_coord(void) const;
	inline int32_t get_x(void) const;
	inline int32_t get_y(void) const;
	inline PosIt get_x_it(void) const;
	inline PosIt get_y_it(void) const;
	inline int32_t get_radius(void) const;

	inline void set_x_it(const PosIt &it);
	inline void set_y_it(const PosIt &it);
	inline void set_x(int x);
	inline void set_y(int y);

private:
	uint32_t id_;			// 一组aoi对象中的唯一ID
	Coord coord_;			// 坐标
	int32_t radius_;		// object的关注半径 所有object关注半径一致
	PosIt x_it_;			// 十字链表的pos记录
	PosIt y_it_;
};

inline uint32_t Object::get_id(void) const {
	return id_;
}

inline const Coord& Object::get_coord(void) const {
	return coord_;
}

inline int32_t Object::get_x(void) const {
	return coord_.x_;
}

inline int32_t Object::get_y(void) const {
	return coord_.y_;
}

inline int32_t Object::get_radius(void) const {
	return radius_;
}

inline Object::PosIt Object::get_x_it(void) const{
	return x_it_;
}

inline Object::PosIt Object::get_y_it(void) const {
	return y_it_;
}

inline void Object::set_x_it(const PosIt &it) {
	x_it_ = it;
}

inline void Object::set_y_it(const PosIt &it) {
	y_it_ = it;
}

inline void Object::set_x(int x) {
	coord_.x_ = x;
}

inline void Object::set_y(int y) {
	coord_.y_ = y;
}

#endif /* OBJECT_H_ */
