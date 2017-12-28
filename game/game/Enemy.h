#ifndef _Enemy_H_
#define _Enemy_H_
	//--Начало--//
		#include "Entity.h"
		
		class Enemy :public Entity
		{
		public:
			int direction; //Направление движения врага
			
			Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
			void checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy); //Ф-ция проверки столкновений с картой
			void update(GameMap &gameMap, float time);
		};
	//--Конец--//
#endif