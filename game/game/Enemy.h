#pragma once
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "gameMap.h" //���������� ��� � ������
#include "Entity.h" 
#include <list>

using namespace sf;

class Enemy :public Entity
{
public:
	int direction;//����������� �������� �����

	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	void checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy);//�-��� �������� ������������ � ������
	void update(GameMap &gameMap, float time);

};//����� Enemy ������