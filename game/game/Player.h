#ifndef _Player_H_
#define _Player_H_
	//--������--//
		#include "Entity.h"
		
		class Player :public Entity
		{
		public:
			Player(Image &image, float X, float Y, int W, int H, std::string Name);
			void control(); //���� ����� ����� ���� ������ � ������
			void update(GameMap &gameMap, float time);
			void checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy);
		};
	//--�����--//
#endif
