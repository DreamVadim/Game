#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
//#include "map.h" //подключили код с картой
#include "Player.h"
#include "Entity.h"
#include <list>

using namespace sf;

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
	//playerScore = 0;
	state = stay;
	if (name == "Player1") {
		//«адаем спрайту один пр€моугольник дл€
		//вывода одного игрока. IntRect Ц дл€ приведени€ типов
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

void Player::control() {
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

//ћетод проверки столкновений с элементами карты
void Player::checkCollisionWithMap(std::string TileMap[], float Dx, float Dy) {
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимс€ по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент тайлик земли
			{
				if (Dy > 0) { y = i * 32 - h;  dy = 0; }//по Y 
				if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними кра€ми 
				if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты
				if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты
			}
			if (TileMap[i][j] == 's') {
				fishFood += 1;  //ЅерЄм корм
				TileMap[i][j] = ' '; //«амен€ корма на пробел
			}
		}
}


void Player::update(std::string TileMap[], float time) //метод "оживлени€/обновлени€" объекта класса.
{
	if (life) {//провер€ем, жив ли герой
		control();//функци€ управлени€ персонажем
		switch (state)//делаютс€ различные действи€ в зависимости от состо€ни€
		{
		case right: {//состо€ние идти вправо
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			break;
		}
		case left: {//состо€ние идти влево
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
			break;
		}
		case up: {//идти вверх
			dy = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
			break;
		}
		case down: {//идти вниз
			dy = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			break;
		}
		case stay: {//стоим
			dy = speed;
			dx = speed;
			break;
		}
		}

		x += dx*time; //движение по УXФ
		checkCollisionWithMap(TileMap, dx, 0);//обрабатываем столкновение по ’
		y += dy*time; //движение по УYФ
		checkCollisionWithMap(TileMap, 0, dy);//обрабатываем столкновение по Y

		speed = 0;    //обнул€ем скорость, чтобы персонаж остановилс€.

		sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (fishFood <= 0) { life = false; }//если корма меньше 0, либо равно 0, то умираем 
	}
};