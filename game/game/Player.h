#pragma once
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
//#include "map.h" //подключили код с картой
#include "Entity.h"


using namespace sf;

class Player :public Entity {

public:
	int playerScore;

	Player(Image &image, float X, float Y, int W, int H, std::string Name);
	//эта переменная может быть только у игрока
	void control();
	void update(std::string TileMap[], float time);
	void checkCollisionWithMap(std::string TileMap[], float Dx, float Dy);
};