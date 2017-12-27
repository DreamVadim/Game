//#include "Map.h"
#include "Game.h"

Game::Game()
{

}

void Game::randomFoodGenerate(std::string TileMap[], int width, int height) {//�������� ���������� ���

	int randomElementX = 0;//��������� �� ������� ���������� �������� �� �����������
	int randomElementY = 0;//��������� �� ������� ���������� �������� �� ���������

	int countFood = 5;//���������� ���

	while (countFood > 0) {
		randomElementX = 1 + rand() % (width - 1);//��������������� �������� �� �x� �� 1 ��
												  //������ �����-1. ����������� ������� ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (height - 1);//�� �y�

		if (TileMap[randomElementY][randomElementX] == ' ') {//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 's';  //�� ������ ���� ������.
			countFood--;
		}
	}
}

void Game::randomEnemyGenerate(std::string TileMap[], int width, int height) {//�������� ���������� ������

	int randomElementX = 0;//��������� �� ������� ���������� �������� �� �����������
	int randomElementY = 0;//��������� �� ������� ���������� �������� �� ���������

	int countEnemy = 5;//���������� ������

	while (countEnemy > 0) {
		randomElementX = 1 + rand() % (width - 1);//��������������� �������� �� �x� �� 1 ��
												  //������ �����-1. ����������� ������� ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (height - 1);//�� �y�

		if (TileMap[randomElementY][randomElementX] == ' ') {//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 's';  //�� ������ ���� ������.
			countEnemy--;
		}
	}
}