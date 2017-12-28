#ifndef _Entity_H_
#define _Entity_H_
	//--������--//
		#include "gameMap.h"
		
		using namespace sf;

		class Entity
		{
		public:
			enum { left, right, up, down, stay } state; //��� ������������ - ��������� �������
			float dx, dy, x, y, speed, moveTimer; //�������� ���������� ������ ��� ������� �����
			int w, h, fishFood; //���������� "fishFood", �������� ����� ������
			bool life; //���������� "life" �����, ����������
			Texture texture; //SFML ��������
			Sprite sprite; //SFML ������ 
			float CurrentFrame; //������ ������� ����
			
			int sizeW = 96;
			int sizeH = 96;
			
			std::string name; //����� ����� ���� ������, ������ ����� ��������� �� ������. ������� ����� ���� ���� �������� � update() � ����������� �� �����
			
			Entity(Image &image, float X, float Y, int W, int H, std::string Name);
			
			void switchImage(Image &image);
			
			FloatRect getRect()
			{
				//����� ��������� ��������������. ��� �����, ������� (���,�����).
				FloatRect FR(x, y, w, h); //���������� FR ���� FloatRect
				return FR;
				//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
				//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
				//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
				//��� �-��� ����� ��� �������� ����������� 
			}
			
			virtual void update(GameMap &gameMap, float time) = 0;
		};
	//--�����--//
#endif