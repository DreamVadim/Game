#ifndef _GameMap_H_
#define _GameMap_H_
	//--������--//
		#include <SFML\Graphics.hpp>
		const int HEIGHT_MAP = 25; //������ ����� ������
		const int WIDTH_MAP = 53; //������ ����� ������ 

		class GameMap
		{
		public:
			GameMap();
			std::string TileMap[HEIGHT_MAP];
		};
	//--�����--//
#endif