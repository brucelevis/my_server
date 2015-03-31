/*
 * rank_test.cpp
 *
 *  Created on: Nov 7, 2014
 *	  Author: "enjolras"
 */

#include "Pre_Header.h"
#include "Log.h"
#include "Time_Test.h"

const uint32_t MAX_PLAYER = 10000000;							// 最大玩家数
const uint32_t EACH_BUCKET_PLAYER = 50;							// 一个桶期望的玩家数
const uint32_t BUCKET_NUMS = MAX_PLAYER / EACH_BUCKET_PLAYER;	// 桶数
const uint32_t MAX_POWER_HASHER = 1000000;						// 战力高于这个值的，映射到最高的一个桶
const uint32_t DIVISOR = 1000000 / BUCKET_NUMS;					// 每XX战力分一个桶
const uint32_t MAX_ARRAY_INDEX = BUCKET_NUMS;
const uint32_t ARRAY_SIZE = MAX_ARRAY_INDEX + 1;

uint32_t hash_func(uint32_t power) {	// 哈希函数，不使用标准库的unordered_map，通过hash_func保证不冲突，使用数组，INDEX有排序的含义
	if (power > MAX_POWER_HASHER) {
		return MAX_ARRAY_INDEX;
	}
	return power / DIVISOR;
}

// 榜单存储的玩家信息
struct Player_Info {
	Player_Info(uint64_t role_id_, uint32_t power_) : role_id(role_id_), power(power_), new_power(0) {}
	Player_Info(void) : Player_Info(0, 0) {}
	uint64_t role_id;		// role_id
	uint32_t power;			// 战力
	uint32_t new_power;		// 临时存储随机增加的新战力
};

struct Bucket_Info {
	typedef std::list<Player_Info> Player_Info_List;
	Player_Info_List player_list;				// 玩家信息列表，按战力排序
	uint32_t prev_nums;							// 此桶前面的玩家数
};

typedef std::array<Bucket_Info, ARRAY_SIZE> Charts;
typedef std::array<Player_Info, MAX_PLAYER> Player_Info_Array;

void init_to_charts(const Player_Info &player_info, Charts &charts) {
	uint32_t power = player_info.power;
	uint32_t index = hash_func(power);
	Bucket_Info::Player_Info_List &list = charts[index].player_list;
	list.push_back(player_info);
}

// 构造排行榜数据
void init_charts(Charts &charts, Player_Info_Array &player_info_array) {
	Player_Info player_info;
	for (uint32_t i = 0; i < MAX_PLAYER; ++i) {
		player_info.role_id = i;
		player_info.power = rand() % MAX_POWER_HASHER;
		player_info_array[i] = player_info;
		init_to_charts(player_info, charts);
	}
	uint32_t player_nums = 0;
	for (int32_t i = charts.size() - 1; i >= 0; --i) {
		Bucket_Info &bucket_info = charts[i];
		bucket_info.prev_nums = player_nums;
		bucket_info.player_list.sort([](const Player_Info &info1, const Player_Info &info2)
			{ return info1.power < info2.power; });
		player_nums += bucket_info.player_list.size();	// 记录排前面的榜单的大小
	}
}

// 玩家战力改变，只记录上升，不记录下降
void chg_charts(uint64_t role_id, uint32_t old_val, uint32_t new_val, Charts &charts) {
	if (old_val >= new_val) {
		rec_log(Log::LVL_ERROR, "%ld old val %d > new val %d", role_id, old_val, new_val);
		return;
	}
	uint32_t old_index = hash_func(old_val);
	uint32_t new_index = hash_func(new_val);
	if (old_index == new_index) {	// 同一个桶内的名次改变 只需要调整列表
		Bucket_Info &bucket_info = charts[old_index];
		auto it = std::find_if(bucket_info.player_list.begin(), bucket_info.player_list.end(), [role_id](const Player_Info &info)
			{ return info.role_id == role_id; });
		if (it == bucket_info.player_list.end()) {
			rec_log(Log::LVL_ERROR, "%ld not found in charts", role_id);
		} else {
			auto it_insert = std::find_if(bucket_info.player_list.erase(it), bucket_info.player_list.end(), [new_val](const Player_Info &info)
				{ return info.power >= new_val; });
			bucket_info.player_list.insert(it_insert, Player_Info(role_id, new_val));
		}
	} else {	// 不同桶内的名次改变，从旧桶移除，在新桶插入，并调整prev_nums
		Bucket_Info &old_bucket_info = charts[old_index];
		auto it = std::find_if(old_bucket_info.player_list.begin(), old_bucket_info.player_list.end(), [role_id](const Player_Info &info)
			{ return info.role_id == role_id; });
		if (it == old_bucket_info.player_list.end()) {
			rec_log(Log::LVL_ERROR, "%ld not found in charts", role_id);
		} else {
			old_bucket_info.player_list.erase(it);
		}
		Bucket_Info &new_bucket_info = charts[new_index];
		auto it_insert = std::find_if(new_bucket_info.player_list.begin(), new_bucket_info.player_list.end(), [new_val](const Player_Info &info)
			{ return info.power >= new_val; });
		new_bucket_info.player_list.insert(it_insert, Player_Info(role_id, new_val));
		for (uint32_t i = old_index; i < new_index; ++i) {
			Bucket_Info &bucket_info = charts[i];
			++bucket_info.prev_nums;
		}
	}
}

void output_charts(const Charts &charts) {
	for (int32_t i = charts.size() - 1; i >= 0; --i) {
		const Bucket_Info &bucket_info = charts[i];
		rec_log(Log::LVL_INFO, "prev_nums : %d, player_list_size %d", bucket_info.prev_nums, bucket_info.player_list.size());
		for (auto it = bucket_info.player_list.rbegin(); it != bucket_info.player_list.rend(); ++it) {
			rec_log(Log::LVL_INFO, "role_id %ld, power %d", it->role_id, it->power);
		}
	}
}

Charts charts;
Player_Info_Array player_info;

int main()
{
	srandom(time(0));
	init_charts(charts, player_info);
	rec_log(Log::LVL_INFO, "init complete with %d player", MAX_PLAYER);
	rec_log(Log::LVL_INFO, "input num to test, other to exit");
	uint32_t opt;
	while (std::cin>>opt) {
		std::unordered_map<uint64_t, Player_Info> change_player;
		for (uint64_t i = 0; i < 100000; ++i) {
			uint32_t index = rand() % MAX_PLAYER;
			if (change_player.count(player_info[index].role_id) == 0) {
				uint32_t add = rand() % (10 * DIVISOR) + 1;
				Player_Info new_info = player_info[index];
				new_info.new_power = new_info.power + add;
				change_player[player_info[index].role_id] = new_info;
				new_info.power = new_info.new_power;	// 记录改变
				player_info[index] = new_info;
			}
		}
		rec_log(Log::LVL_INFO, "changed player nums : %d", change_player.size());
		{
			Time_Test tester("player power change");
			for (auto it = change_player.begin(); it != change_player.end(); ++it) {
				chg_charts(it->first, it->second.power, it->second.new_power, charts);
			}
		}
	}

	// 查看排行榜情况 输出的内容很长，在验证正确性的时候取消注释
	// output_charts(charts);
	return 0;
}


