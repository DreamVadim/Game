//branch develop
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <list>

using namespace sf;

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1700, 800, desktop.bitsPerPixel), "Easy Fish");

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст
	text.setColor(Color::Red);//покрасили текст в красный	text.setStyle(Text::Bold);//жирный текст.

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map_new.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	Image heroImage;
	//heroImage.loadFromFile("images/hero.png"); // загружаем изображение игрока
	heroImage.loadFromFile("images/hero_new.png"); // загружаем изображение игрока

	Image easyEnemyImage;
	//easyEnemyImage.loadFromFile("images/enemy.png"); // загружаем изображение врага
	easyEnemyImage.loadFromFile("images/enemy_new.png"); // загружаем изображение врага

	Player player(heroImage, 100, 100, 96, 96, "Player1");//объект класса игрока
	Game game;

	std::list<Entity*>  enemies; //список врагов
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка

	const int ENEMY_COUNT = 7;	//максимальное количество врагов в игре
	int enemiesCount = 0;      //текущее количество врагов в игре

							   //Заполняем список объектами врагами
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		float xr = 150 + rand() % 1700; //случайная координата врага на поле игры по оси “x”
		float yr = 150 + rand() % 500; //случайная координата врага на поле игры по оси “y”
									   //создаем врагов и помещаем в список
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
		enemiesCount += 1; //увеличили счётчик врагов
	}

	int createObjectForMapTimer = 0;//Переменная под время для генерирования еды

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (player.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в секундах идёт вперед, пока жив игрок. 
																			   //Перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer > 3000) {
			game.randomFoodGenerate(TileMap, WIDTH_MAP, HEIGHT_MAP);//генерация еды
			createObjectForMapTimer = 0;//обнуляем таймер
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.update(TileMap, time); //оживляем объект “p” класса “Player” 

									  //оживляем врагов
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(TileMap, time); //запускаем метод update()
		}

		//Проверка пересечения игрока с врагами
		//Если пересечение произошло, то "fishFood = 0", игрок обездвижевается и 
		//выводится сообщение "you are lose"
		if (player.life == true) {//если игрок жив
			for (it = enemies.begin(); it != enemies.end(); it++) {//бежим по списку врагов
				if ((player.getRect().intersects((*it)->getRect())))
				{
					if (player.fishFood < (*it)->fishFood)
					{
						player.fishFood = 0;
						std::cout << "you are lose";
					}
					else
					{
						(*it)->fishFood = 0;
					}

				}
			}
		}

		window.clear();

		////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //свободное поле
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //враг
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32)); //граница

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}

		//объявили переменную здоровья и времени
		std::ostringstream playerHealthString, gameTimeString;

		playerHealthString << player.fishFood; gameTimeString << gameTime;//формируем строку
		text.setString("Наш уровень: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str() + "\nУровень рыб: 5");//задаем строку тексту
		text.setPosition(50, 50);//задаем позицию текста
		window.draw(text);//рисуем этот текст

		window.draw(player.sprite); //рисуем спрайт объекта “p” класса “Player”

									//рисуем врагов
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->fishFood > 0) //Если у врага нету еды (умер), то он не рисуется
			{
				window.draw((*it)->sprite); //рисуем enemies объекты
			}

		}

		window.display();
	}
	return 0;
}