#include "Entity.h"

Entity::Entity(Image &image, float X, float Y, int W, int H, std::string Name)
{
	x = X; y = Y; // оордината по€влени€ спрайта
	w = W; h = H;
	name = Name;
	moveTimer = 0;
	dx = 0; dy = 0;
	speed = 0;
	CurrentFrame = 0;
	fishFood = 1;
	life = true; //»нициализировали логическую переменную жизни, герой жив
	texture.loadFromImage(image); //«аносим наше изображение в текстуру
	sprite.setTexture(texture); //«аливаем спрайт текстурой
}

void Entity::switchImage(Image &image) 
{
	texture.loadFromImage(image); //«аносим наше изображение в текстуру
	sprite.setTexture(texture); //«аливаем спрайт текстурой
}