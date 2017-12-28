//#include "Map.h"
#include "GameMap.h"

GameMap::GameMap()
{
	int i = 0;
	while (i < HEIGHT_MAP) {                         //0123456789 123456789 123456789 123456789 123456789 12
		if (i == 0 || i == HEIGHT_MAP - 1) TileMap[i] = "00000000000000000000000000000000000000000000000000000";
		else TileMap[i] = "0                                                   0";
		i++;
	}
}