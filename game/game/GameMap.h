#pragma once
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;//������ ����� ������
const int WIDTH_MAP = 53;//������ ����� ������ 
class GameMap
{
public:
	GameMap();
	std::string TileMap[HEIGHT_MAP];
};

/*
std::string TileMap[HEIGHT] = {
"00000000000000000000000000000000000000000000000000000",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"0                                                   0",
"00000000000000000000000000000000000000000000000000000",
};
*/