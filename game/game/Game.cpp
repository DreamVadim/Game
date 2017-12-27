//#include "Map.h"
#include "Game.h"

Game::Game()
{

}

void Game::randomFoodGenerate(std::string TileMap[], int width, int height) {//рандомно расставл¤ем еду

	int randomElementX = 0;//переменна¤ дл¤ хранени¤ случайного элемента по горизонтали
	int randomElementY = 0;//переменна¤ дл¤ хранени¤ случайного элемента по вертикали

	int countFood = 5;//количество еды

	while (countFood > 0) {
		randomElementX = 1 + rand() % (width - 1);//псевдослучайное значение по УxФ от 1 до
												  //ширина карты-1. ќграничение введено чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (height - 1);//по УyФ

		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's';  //то ставим туда камень.
			countFood--;
		}
	}
}

void Game::randomEnemyGenerate(std::string TileMap[], int width, int height) {//рандомно расставл¤ем врагов

	int randomElementX = 0;//переменна¤ дл¤ хранени¤ случайного элемента по горизонтали
	int randomElementY = 0;//переменна¤ дл¤ хранени¤ случайного элемента по вертикали

	int countEnemy = 5;//количество камней

	while (countEnemy > 0) {
		randomElementX = 1 + rand() % (width - 1);//псевдослучайное значение по УxФ от 1 до
												  //ширина карты-1. ќграничение введено чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (height - 1);//по УyФ

		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's';  //то ставим туда камень.
			countEnemy--;
		}
	}
}
