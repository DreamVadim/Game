#ifndef _GameMap_H_
#define _GameMap_H_
	//--Начало--//
		#include <SFML\Graphics.hpp>
		const int HEIGHT_MAP = 25; //Размер карты высота
		const int WIDTH_MAP = 53; //Размер карты ширина 

		class GameMap
		{
		public:
			GameMap();
			std::string TileMap[HEIGHT_MAP];
		};
	//--Конец--//
#endif