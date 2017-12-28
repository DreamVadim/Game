//branch release_v2.0
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "GameMap.h"
#include <list>

using namespace sf;

int main()
{
	//������ ���� � ��� �� ������� �������� ��������, ��� � ������� ����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1700, 800, desktop.bitsPerPixel), "FishGame"); //������ ������ ����, � ������� �����������

	Font font; //����� 
	font.loadFromFile("RobotoBold.ttf"); //�������� ������ ������ ���� ������
	Text text("", font, 20); //������� ������ �����
	text.setColor(Color::White); //��������� ����� � �����

	Image map_image; //������ ����������� ��� �����
	map_image.loadFromFile("images/map_new.png"); //��������� ���� ��� �����
	Texture map; //�������� �����
	map.loadFromImage(map_image); //�������� �������� ���������
	Sprite s_map; //������ ������ ��� �����
	s_map.setTexture(map); //�������� �������� ��������

	Clock clock;
	Clock gameTimeClock; //���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0; //�������� ������� �����, ����������������.

	Image heroImage;
	heroImage.loadFromFile("images/hero_new.png"); //��������� ����������� ������

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy_new.png"); //��������� ����������� �����

	Image easyEnemyGreenImage;
	easyEnemyGreenImage.loadFromFile("images/enemy_new_green.png"); //��������� ����������� �����


	Player player(heroImage, 100, 100, 96, 96, "Player1"); //������ ������ ������
	Game game;
	GameMap gameMap;

	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������

	const int ENEMY_COUNT = 7;	//������������ ���������� ������ � ����

	//��������� ������ ��������� �������
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		float xr = 150 + rand() % 1700; //��������� ���������� ����� �� ���� ���� �� ��� �x�
		float yr = 150 + rand() % 500;  //��������� ���������� ����� �� ���� ���� �� ��� �y�
										//������� ������ � �������� � ������
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
	}

	int createObjectForMapTimer = 0; //���������� ��� ����� ��� ������������� ���

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (player.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); //������� ����� � �������� ��� ������, ���� ��� �����. 

		//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time; //���������� ������
		if (createObjectForMapTimer > 11000) 
		{
			game.randomFoodGenerate(gameMap.TileMap, WIDTH_MAP, HEIGHT_MAP); //��������� ���
			createObjectForMapTimer = 0; //�������� ������
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//--�������� �����--������--//
			player.update(gameMap, time); //�������� ������ "player" ������ "Player"
		//--�������� �����--�����--//

		//--�������� ������--������--//
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				if ((*it)->fishFood < player.fishFood)
				{
					(*it)->switchImage(easyEnemyGreenImage);
				}
				(*it)->update(gameMap, time); //��������� ����� update()
			}
		//--�������� ������--�����--//

		//--�������� ����������� ���--������--//
			if (player.life == true) //���� ����� ���
			{
				for (it = enemies.begin(); it != enemies.end(); it++) { //����� �� ������ ������
					if ((player.getRect().intersects((*it)->getRect())))
					{
						if (player.fishFood < (*it)->fishFood) //���� � ������ ������ ���, ��� � �����, �� 
						{
							player.fishFood = 0; //� ������ �������� ��� ���
							std::cout << "you are lose";
						}
						else
						{
							(*it)->fishFood = 0; //�������� ��� ��� �����
						}

					}
				}
			}
		//--�������� ����������� ���--�����--//

		//--������ �����--������--//
			window.clear(); //������� ����� ����� ����� ����������

			for (int i = 0; i < HEIGHT_MAP; i++)
			{
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (gameMap.TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //��������� ����
					if (gameMap.TileMap[i][j] == 'f')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //���
					if ((gameMap.TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32)); //�������

					s_map.setPosition(j * 32, i * 32);
					window.draw(s_map);
				}
			}
		//--������ �����--�����--//

		//--�������������� ���� (����� � ����� ������� ����)--������--//
			std::ostringstream playerFoodString, gameTimeString; //�������� ���������� ��� � �������

			playerFoodString << player.fishFood; gameTimeString << gameTime; //��������� ������
			text.setString("My level: " + playerFoodString.str() + "\nTime: " + gameTimeString.str() + "\nRed fish level: 7"); //������ ������ ������
			text.setPosition(50, 50); //������ ������� ������
			window.draw(text); //������ ���� �����
		//--�������������� ���� (����� � ����� ������� ����)--�����--//

		//--������ �����--������--//
			window.draw(player.sprite); //������ ������ ������� "p" ������ "Player"
		//--������ �����--�����--//

		//--������ ������--������--//
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				if ((*it)->fishFood > 0) //���� � ����� �������� ��� ������ ����, �� �� ��� ������
				{
					window.draw((*it)->sprite); //������ enemies �������	
				}

			}
		//--������ ������--�����--//

		window.display();
	}
	return 0;
}