/*
 * Object.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: "enjolras"
 */

#include <Object.h>
#include "Log.h"

Object::Object(uint32_t id, const Coord &coord, uint32_t radius) : id_(id)
	,coord_(coord)
	,radius_(radius) {
	rec_log(Log::LVL_DEBUG, "object %d create", id_);
}

Object::~Object(void) {
	rec_log(Log::LVL_DEBUG, "object %d destroy", id_);
}
