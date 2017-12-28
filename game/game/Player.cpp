#include "Player.h"

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	state = stay;
	if (name == "Player1") 
	{
		//Создаем спрайту один прямоугольник для
		//Вывода одного игрока. IntRect для приведения типов
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

void Player::control()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		state = left;
		speed = 0.1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		state = right;
		speed = 0.1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		state = up;
		speed = 0.1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		state = down;
		speed = 0.1;
	}
}

void Player::checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy) //Метод проверки столкновений с элементами карты
{
	for (int i = y / 32; i < (y + h) / 32; i++) //Проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (gameMap.TileMap[i][j] == '0') //Если элемент тайлик земли
			{
				if (Dy > 0) { y = i * 32 - h;  dy = 0; } //По Y 
				if (Dy < 0) { y = i * 32 + 32; dy = 0; } //Столкновение с верхними краями 
				if (Dx > 0) { x = j * 32 - w; dx = 0; } //С правым краем карты
				if (Dx < 0) { x = j * 32 + 32; dx = 0; } //С левым краем карты
			}
			if (gameMap.TileMap[i][j] == 'f') {
				fishFood += 1;  //Берём еду
				gameMap.TileMap[i][j] = ' '; //Замена еды на пробел
			}
		}
}


void Player::update(GameMap &gameMap, float time) //Метод "оживления/обновления" объекта класса.
{
	if (life) { //Проверяем, жив ли герой
		control(); //Функция управления персонажем
		switch (state) //Делаются различные действия в зависимости от состояния
		{
			case right: { //Состояние идти вправо
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
				break;
			}
			case left: { //Состояние идти влево
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
				break;
			}
			case up: { //Идти вверх
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
				break;
			}
			case down: { //Идти вниз
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
				break;
			}
			case stay: { //Стоим
				dy = speed;
				dx = speed;
				break;
			}
		}

		x += dx*time; //Движение по "X"
		checkCollisionWithMap(gameMap, dx, 0); //Обрабатываем столкновение по X
		y += dy*time; //Движение по "Y"
		checkCollisionWithMap(gameMap, 0, dy); //Обрабатываем столкновение по Y

		speed = 0; //ОбнулЯем скорость, чтобы персонаж остановился

		sprite.setPosition(x, y); //Спрайт в позиции (x, y).

		if (fishFood <= 0) { life = false; } //Если еды меньше 0, либо равно 0, то умираем 
	}
};