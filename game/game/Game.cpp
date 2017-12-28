#include "Game.h"

Game::Game()
{
	//Пустой конструктор
}

void Game::randomFoodGenerate(std::string TileMap[], int width, int height) { //Рандомно расставляем еду
	int randomElementX = 0; //Переменная для хранения случайного элемента по горизонтали
	int randomElementY = 0; //Переменная для хранения случайного элемента по вертикали

	int countFood = 2; //Количество еды

	while (countFood > 0) {
		randomElementX = 1 + rand() % (width - 1); //Псевдослучайное значение по "x" от 1 до *ширина карты-1*. Ограничение введено чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (height - 1); //По "y"
		if (TileMap[randomElementY][randomElementX] == ' ') //Если встретили символ пробел
		{
			TileMap[randomElementY][randomElementX] = 'f';  //То ставим туда корм
			countFood--;
		}
	}
}