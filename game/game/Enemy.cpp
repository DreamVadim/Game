#include "Enemy.h" 

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	fishFood = 7;
	if (name == "EasyEnemy")
	{
		//������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� �����
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (3); //����������� �������� ����� ����� ��������� ������� ����� ��������� ��������� �����
		speed = 0.05; //���� ��������. ���� ������ ������ ���������
		dx = speed;
	}
};

void Enemy::checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy) //�-��� �������� ������������ � ������
{
	for (int i = y / 32; i < (y + h) / 32; i++) //���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (j < 0) j == 0;
			else if (j > WIDTH_MAP - 1) j = WIDTH_MAP - 1;
			if (i < 0) i == 0;
			else if (i > HEIGHT_MAP - 1) i = HEIGHT_MAP - 1;

			if (gameMap.TileMap[i][j] == '0') //���� ������� - ������ �����
			{
				if (Dy > 0)
				{
					y = i * 32 - h;  dy = -0.1;
					direction = rand() % (3); //����������� �������� �����
				} //�� Y 

				if (Dy < 0)
				{
					y = i * 32 + 32; dy = 0.1;
					direction = rand() % (3); //����������� �������� ����� 
				} //������������ � �������� ������ 

				if (Dx > 0)
				{
					x = j * 32 - w; dx = -0.1;
					direction = rand() % (3); //����������� �������� ����� 
				} //� ������ ����� �����

				if (Dx < 0)
				{
					x = j * 32 + 32; dx = 0.1;
					direction = rand() % (3); //����������� �������� �����
				} //� ����� ����� �����
			}
		}
};

void Enemy::update(GameMap &gameMap, float time)
{
	if (name == "EasyEnemy") //��� ��������� � ����� ������ ������ ����� �����
	{
		if (life) { //���������, ��� �� �����
			switch (direction) //�������� ��������� �������� � ����������� �� ���������
			{
			case 0: { //��������� ���� ������
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
				break;
			}
			case 1: { //��������� ���� �����
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
				break;
			}
			case 2: { //���� �����
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
				break;
			}
			case 3: { //���� ����
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
				break;
			}
			}

			x += dx*time; //�������� �� "X"
			checkCollisionWithMap(gameMap, dx, 0); //������������ ������������ �� �

			y += dy*time; //�������� �� "Y"
			checkCollisionWithMap(gameMap, 0, dy); //������������ ������������ �� Y

			sprite.setPosition(x, y); //������ � ������� (x, y).

			if (fishFood <= 0) { life = false; } //���� ������ ������ 0, ���� ����� 0, �� �������
		}
	}
};