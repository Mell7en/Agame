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
	
	Texture crossCircle; //������
	Texture font; //���
	Texture lines; //�����
	 
	Event event;

	Sprite choice[2];//������ ��� ������ ������ ��� �����
	Sprite fontSprite;

public:
	int BotMove();
	Game();
	void run();
	void doing();
};

