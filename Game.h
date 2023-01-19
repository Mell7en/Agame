#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Game
{

	RenderWindow window;
	int ch = 0;
	int num = 0;
	int result = 0;
	int botMove = 0;
	bool lib[9] = { false };


	bool win = false;
	bool hotBot = false;
	bool dumBot = false;
	bool winplay[8][2];
	
	Texture crossCircle; //кресты
	Texture font; //фон
	Texture lines; //линии
	 
	Event event;

	Sprite choice[2];//массив для выбора кретик или нолик
	Sprite fontSprite;

public:
	int BotMove();
	Game();
	void run();
	void doing();
};

