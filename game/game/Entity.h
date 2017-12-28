#ifndef _Entity_H_
#define _Entity_H_
	//--Начало--//
		#include "gameMap.h"
		
		using namespace sf;

		class Entity
		{
		public:
			enum { left, right, up, down, stay } state; //Тип перечисления - состояние объекта
			float dx, dy, x, y, speed, moveTimer; //Добавили переменную таймер для будущих целей
			int w, h, fishFood; //Переменная "fishFood", хранящая жизни игрока
			bool life; //Переменная "life" жизнь, логическая
			Texture texture; //SFML текстура
			Sprite sprite; //SFML спрайт 
			float CurrentFrame; //Хранит текущий кадр
			
			int sizeW = 96;
			int sizeH = 96;
			
			std::string name; //Враги могут быть разные, врагов можно различать по именам. Каждому можно дать свое действие в update() в зависимости от имени
			
			Entity(Image &image, float X, float Y, int W, int H, std::string Name);
			
			void switchImage(Image &image);
			
			FloatRect getRect()
			{
				//Метод получения прямоугольника. Его коорд, размеры (шир,высот).
				FloatRect FR(x, y, w, h); //Переменная FR типа FloatRect
				return FR;
				//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
				//в нашей игре это координаты текущего расположения тайла на карте
				//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
				//эта ф-ция нужна для проверки пересечений 
			}
			
			virtual void update(GameMap &gameMap, float time) = 0;
		};
	//--Конец--//
#endif