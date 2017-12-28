#ifndef _Enemy_H_
#define _Enemy_H_
	//--������--//
		#include "Entity.h"
		
		class Enemy :public Entity
		{
		public:
			int direction; //����������� �������� �����
			
			Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
			void checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy); //�-��� �������� ������������ � ������
			void update(GameMap &gameMap, float time);
		};
	//--�����--//
#endif