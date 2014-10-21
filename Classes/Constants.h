#pragma once

namespace Constants{
	/*��ҵȴ����پ����ʼ*/
	static const float PLAYER_READY_DISTANCE=600;
	/*Hero Y��λ��*/
	static const float HERO_POSITION_Y = 350;
	/*�ϰ�֮��ľ���*/
	static const float THORN_SPACING=280;
	/*�ϰ���������*/
	static const int THORN_TYPE_COUNT = 5;
	/*�ϰ��ش�ŵ�����ϰ�����*/
	static const int THORNS_POOL_MAX = THORN_TYPE_COUNT * 8;
	/*�ϰ���ʼ�ٶ�*/
	static const float ORIGIN_SPEED = 15;
	/*ÿͨ�������ϰ������*/
	static const int THRON_INTERVAL = 10;
	/*ÿ�ε����ļ��ٶ�*/
	static const float THRON_ACCELERATION = 2;
	/*�ϰ��ٶ�����*/
	static const float THRON_SPEED_LIMIT = 50;


	/*�ϰ�����ʱ��������ʱ����Y��ԭ��ľ���*/
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