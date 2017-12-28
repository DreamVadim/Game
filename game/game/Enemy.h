#pragma once
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "gameMap.h" //подключили код с картой
#include "Entity.h" 
#include <list>

using namespace sf;

class Enemy :public Entity
{
public:
	int direction;//направление движения врага

	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	void checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy);//ф-ция проверки столкновений с картой
	void update(GameMap &gameMap, float time);

};//класс Enemy закрыт