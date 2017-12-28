#include "GameMap.h"

GameMap::GameMap()
{
	int i = 0;
	while (i < HEIGHT_MAP)
	{
		if (i == 0 || i == HEIGHT_MAP - 1) TileMap[i] = "00000000000000000000000000000000000000000000000000000";
		else TileMap[i] = "0                                                   0";
		i++;
	}
}