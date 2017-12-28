#pragma once
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "gameMap.h" //���������� ��� � ������
#include "Entity.h"


using namespace sf;

class Player :public Entity {

public:
	//int playerScore;

	Player(Image &image, float X, float Y, int W, int H, std::string Name);
	//��� ���������� ����� ���� ������ � ������
	void control();
	void update(GameMap &gameMap, float time);
	void checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy);
};