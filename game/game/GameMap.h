#pragma once
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 53;//размер карты ширина 
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