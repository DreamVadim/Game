#pragma once
#include "Player.h"
#include "Enemy.h"
class Game //group all the components of the game
{
public:
	Game();
	void randomFoodGenerate(std::string TileMap[], int width, int height);//генерация еды
																		  //void randomEnemyGenerate(std::string TileMap[], int width, int height);
																		  //генерация врагов
};