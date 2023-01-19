#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
class Move {
public:
	Sprite sprite[9];
	bool field[9];
	Move(Texture& image);
	void update(int& upt);
};
