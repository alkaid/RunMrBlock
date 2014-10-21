#pragma once

namespace Constants{
	/*玩家等待多少距离后开始*/
	static const float PLAYER_READY_DISTANCE=600;
	/*Hero Y轴位置*/
	static const float HERO_POSITION_Y = 350;
	/*障碍之间的距离*/
	static const float THORN_SPACING=280;
	/*障碍种类数量*/
	static const int THORN_TYPE_COUNT = 5;
	/*障碍池存放的最大障碍数量*/
	static const int THORNS_POOL_MAX = THORN_TYPE_COUNT * 8;
	/*障碍初始速度*/
	static const float ORIGIN_SPEED = 15;
	/*每通过多少障碍后加速*/
	static const int THRON_INTERVAL = 10;
	/*每次迭代的加速度*/
	static const float THRON_ACCELERATION = 2;
	/*障碍速度上限*/
	static const float THRON_SPEED_LIMIT = 50;


	/*障碍回收时机：回收时距离Y轴原点的距离*/
	static const float THORN_RECYLE_DISTANCE = 200;

	static const float HERO_ACCELERATION = 1000;
	static const float HERO_ORIGIN_SPEED = 1000;

	
	static const int TAG_THORN_LEFT_BIG = 1;
	static const int TAG_THORN_RIGHT_BIG = 2;
	static const int TAG_THORN_SIDE_SMALL = 3;
	static const int TAG_THORN_MIDDLE_SMALL = 4;
	static const int TAG_THORN_MIDDLE_BIG = 5;
	static const int TAG_HERO_LEFT = 11;
	static const int TAG_HERO_RIGHT = 12;
	static const int TAG_WALL_LEFT = 21;
	static const int TAG_WALL_RIGHT = 22;

	static const char* PROP_INT_BEST_SCORE = "PROP_INT_BEST_SCORE";
	static const char* PROP_BOOL_FIRST_TIME = "PROP_BOOL_FIRST_TIME";
}