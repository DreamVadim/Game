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
	//Создаём окно с той же битовой глубиной пикселей, что и рабочий стол
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1700, 800, desktop.bitsPerPixel), "FishGame"); //Создаём объект окна, в скобках конструктор

	Font font; //Шрифт 
	font.loadFromFile("RobotoBold.ttf"); //Передаем нашему шрифту файл шрифта
	Text text("", font, 20); //Создаем объект текст
	text.setColor(Color::White); //Покрасили текст в белый

	Image map_image; //Объект изображения для карты
	map_image.loadFromFile("images/map_new.png"); //Загружаем файл для карты
	Texture map; //Текстура карты
	map.loadFromImage(map_image); //Заряжаем текстуру картинкой
	Sprite s_map; //Создаём спрайт для карты
	s_map.setTexture(map); //Заливаем текстуру спрайтом

	Clock clock;
	Clock gameTimeClock; //Переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0; //Объявили игровое время, инициализировали.

	Image heroImage;
	heroImage.loadFromFile("images/hero_new.png"); //Загружаем изображение игрока

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy_new.png"); //Загружаем изображение врага

	Image easyEnemyGreenImage;
	easyEnemyGreenImage.loadFromFile("images/enemy_new_green.png"); //Загружаем изображение врага


	Player player(heroImage, 100, 100, 96, 96, "Player1"); //Объект класса игрока
	Game game;
	GameMap gameMap;

	std::list<Entity*>  enemies; //Список врагов
	std::list<Entity*>::iterator it; //Итератор чтобы проходить по элементам списка

	const int ENEMY_COUNT = 7;	//Максимальное количество врагов в игре

	//Заполняем список объектами врагами
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		float xr = 150 + rand() % 1700; //случайная координата врага на поле игры по оси “x”
		float yr = 150 + rand() % 500;  //случайная координата врага на поле игры по оси “y”
										//создаем врагов и помещаем в список
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
	}

	int createObjectForMapTimer = 0; //Переменная под время для генерирования еды

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (player.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); //Игровое время в секундах идёт вперед, пока жив игрок. 

		//Перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time; //Наращиваем таймер
		if (createObjectForMapTimer > 11000) 
		{
			game.randomFoodGenerate(gameMap.TileMap, WIDTH_MAP, HEIGHT_MAP); //Генерация еды
			createObjectForMapTimer = 0; //Обнуляем таймер
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//--Оживляем героя--НАЧАЛО--//
			player.update(gameMap, time); //Оживляем объект "player" класса "Player"
		//--Оживляем героя--КОНЕЦ--//

		//--Оживляем врагов--НАЧАЛО--//
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				if ((*it)->fishFood < player.fishFood)
				{
					(*it)->switchImage(easyEnemyGreenImage);
				}
				(*it)->update(gameMap, time); //Запускаем метод update()
			}
		//--Оживляем врагов--КОНЕЦ--//

		//--Проверка пересечения рыб--НАЧАЛО--//
			if (player.life == true) //Если игрок жив
			{
				for (it = enemies.begin(); it != enemies.end(); it++) { //Бежим по списку врагов
					if ((player.getRect().intersects((*it)->getRect())))
					{
						if (player.fishFood < (*it)->fishFood) //Если у игрока меньше еды, чем у врага, то 
						{
							player.fishFood = 0; //У игрока забирают всю еду
							std::cout << "you are lose";
						}
						else
						{
							(*it)->fishFood = 0; //Забираем всю еду врага
						}

					}
				}
			}
		//--Проверка пересечения рыб--КОНЕЦ--//

		//--Рисуем карту--НАЧАЛО--//
			window.clear(); //Очищаем экран перед новой отрисовкой

			for (int i = 0; i < HEIGHT_MAP; i++)
			{
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (gameMap.TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //Свободное поле
					if (gameMap.TileMap[i][j] == 'f')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //Еда
					if ((gameMap.TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32)); //Граница

					s_map.setPosition(j * 32, i * 32);
					window.draw(s_map);
				}
			}
		//--Рисуем карту--КОНЕЦ--//

		//--Информационный блок (текст в левом верхнем углу)--НАЧАЛО--//
			std::ostringstream playerFoodString, gameTimeString; //Объявили переменную еды и времени

			playerFoodString << player.fishFood; gameTimeString << gameTime; //Формируем строку
			text.setString("My level: " + playerFoodString.str() + "\nTime: " + gameTimeString.str() + "\nRed fish level: 7"); //Задаем строку тексту
			text.setPosition(50, 50); //Задаем позицию текста
			window.draw(text); //Рисуем этот текст
		//--Информационный блок (текст в левом верхнем углу)--КОНЕЦ--//

		//--Рисуем героя--НАЧАЛО--//
			window.draw(player.sprite); //Рисуем спрайт объекта "p" класса "Player"
		//--Рисуем героя--КОНЕЦ--//

		//--Рисуем врагов--НАЧАЛО--//
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				if ((*it)->fishFood > 0) //Если у врага значение еды больше нуля, то мы его рисуем
				{
					window.draw((*it)->sprite); //Рисуем enemies объекты	
				}

			}
		//--Рисуем врагов--КОНЕЦ--//

		window.display();
	}
	return 0;
}