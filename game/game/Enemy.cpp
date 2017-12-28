#include "Enemy.h" 

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	fishFood = 7;
	if (name == "EasyEnemy")
	{
		//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (3); //Направление движения врага задаём случайным образом через генератор случайных чисел
		speed = 0.05; //Даем скорость. Этот объект всегда двигается
		dx = speed;
	}
};

void Enemy::checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy) //Ф-ция проверки столкновений с картой
{
	for (int i = y / 32; i < (y + h) / 32; i++) //Проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (j < 0) j == 0;
			else if (j > WIDTH_MAP - 1) j = WIDTH_MAP - 1;
			if (i < 0) i == 0;
			else if (i > HEIGHT_MAP - 1) i = HEIGHT_MAP - 1;

			if (gameMap.TileMap[i][j] == '0') //Если элемент - тайлик земли
			{
				if (Dy > 0)
				{
					y = i * 32 - h;  dy = -0.1;
					direction = rand() % (3); //Направление движения врага
				} //По Y 

				if (Dy < 0)
				{
					y = i * 32 + 32; dy = 0.1;
					direction = rand() % (3); //Направление движения врага 
				} //Столкновение с верхними краями 

				if (Dx > 0)
				{
					x = j * 32 - w; dx = -0.1;
					direction = rand() % (3); //Направление движения врага 
				} //С правым краем карты

				if (Dx < 0)
				{
					x = j * 32 + 32; dx = 0.1;
					direction = rand() % (3); //Направление движения врага
				} //С левым краем карты
			}
		}
};

void Enemy::update(GameMap &gameMap, float time)
{
	if (name == "EasyEnemy") //Для персонажа с таким именем логика будет такой
	{
		if (life) { //Проверяем, жив ли герой
			switch (direction) //Делаются различные действия в зависимости от состояния
			{
			case 0: { //Состояние идти вправо
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
				break;
			}
			case 1: { //Состояние идти влево
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
				break;
			}
			case 2: { //Идти вверх
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
				break;
			}
			case 3: { //Идти вниз
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
				break;
			}
			}

			x += dx*time; //Движение по "X"
			checkCollisionWithMap(gameMap, dx, 0); //Обрабатываем столкновение по Х

			y += dy*time; //Движение по "Y"
			checkCollisionWithMap(gameMap, 0, dy); //Обрабатываем столкновение по Y

			sprite.setPosition(x, y); //Спрайт в позиции (x, y).

			if (fishFood <= 0) { life = false; } //Если жизней меньше 0, либо равно 0, то умираем
		}
	}
};