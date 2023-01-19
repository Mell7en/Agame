#include "Move.h"
Move::Move(Texture& image) {
	for (int i = 0; i < 9; i++)
	{
		sprite[i].setTexture(image);
		field[i] = false;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sprite[i * 3 + j].setPosition(200 * j, 200 * i);
		}
	}
};

void Move::update(int& upt)
{
	for (int i = 0; i < 9; i++)
	{
		sprite[i].setTextureRect(IntRect(200 * (upt - 1), 0, 200, 200));
	}
}