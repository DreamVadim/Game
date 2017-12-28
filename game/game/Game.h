#ifndef _Game_H_
#define _Game_H_
	//--Начало--//
		#include "Player.h"
		#include "Enemy.h"
		class Game //Group all the components of the game
		{
		public:
			Game();
			void randomFoodGenerate(std::string TileMap[], int width, int height); //Генерация еды
		};
	//--Конец--//
#endif