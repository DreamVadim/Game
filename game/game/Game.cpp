//#include "Map.h"
#include "Game.h"

Game::Game()
{

}

void Game::randomFoodGenerate(std::string TileMap[], int width, int height) {//рандомно расставляем еду

	int randomElementX = 0;//переменная для хранения случайного элемента по горизонтали
	int randomElementY = 0;//переменная для хранения случайного элемента по вертикали

	int countFood = 2;//количество еды

	while (countFood > 0) {
		randomElementX = 1 + rand() % (width - 1);//псевдослучайное значение по "x" от 1 до
												  //ширина карты-1. Ограничение введено чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (height - 1);//по "y"

		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's';  //то ставим туда корм.
			countFood--;
		}
	}
}