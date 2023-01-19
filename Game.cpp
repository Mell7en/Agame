#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Move.h"
#include <time.h>


using namespace sf;

int Game::BotMove()
{
	bool trust = false;
	while (!trust)
	{
		result = rand() % 9;

		if (!lib[result])
		{
			trust = true;
		}

		else
		{
			trust = false;
		}
	}
	return result;
}

Game::Game() :window(VideoMode(600, 600), "Agasi's Project")
{
	font.loadFromFile("D:\\C++\\Project2\\Paint\\fon.png");
	crossCircle.loadFromFile("D:\\C++\\Project2\\Paint\\cross.psd");
}

void Game::doing()
{
	Sprite fontSprite(font);
	for (int i = 0; i < 2; i++) 
	{
		choice[i].setTexture(crossCircle); //закгрузка текстуры
		choice[i].setPosition(50 + 300 * i, 180); //какой именно кусок картинкихочу вставить
	}


		Move player(crossCircle);
		Move bot(crossCircle);

		lines.loadFromFile("D:\\C++\\Project2\\Paint\\line.png");
		Sprite lineSprite(lines);


		while (window.isOpen())
		{
			Vector2i pos = Mouse::getPosition(window); //координаты курсора
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}

				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						if (ch == 0)
						{
							for (int i = 0; i < 2; i++)
							{
								if (choice[i].getGlobalBounds().contains(pos.x, pos.y))
								{
									ch = i + 1;
								}
							}
						}

						else
						{
							for (int i = 0; i < 9; i++)
							{
								if (player.sprite[i].getGlobalBounds().contains(pos.x, pos.y) && !lib[i])
								{
									player.field[i] = true;
									lib[i] = true;
									ch++;
									hotBot = true;
								}
							}
						}
					}
				}
			}



			for (int i = 0; i < 2; i++)
			{
				if (choice[i].getGlobalBounds().contains(pos.x, pos.y)) //если навел на крестик
				{
					choice[i].setTextureRect(IntRect(200 * i, 200, 200, 200)); //вывод 2 варианта фотки
				}

				else
				{
					choice[i].setTextureRect(IntRect(200 * i, 0, 200, 200)); //вывод 1 варианта фотки
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if (i < 3)
				{
					winplay[i][0] = player.field[3 * i] && player.field[1 + 3 * i] && player.field[2 + 3 * i];
					winplay[i][1] = bot.field[3 * i] && bot.field[1 + 3 * i] && bot.field[2 + 3 * i];
				}

				else if (i >= 3 && i < 6)
				{
					winplay[i][0] = player.field[i - 3] && player.field[i] && player.field[i + 3];
					winplay[i][1] = bot.field[i - 3] && bot.field[i] && bot.field[i + 3];
				}

				else if (i >= 6)
				{
					winplay[i][0] = player.field[2 * (i - 6)] && player.field[4] && player.field[8 - 2 * (i - 6)];
					winplay[i][1] = bot.field[2 * (i - 6)] && bot.field[4] && bot.field[8 - 2 * (i - 6)];
				}

				for (int j = 0; j < 2; j++)
					if (winplay[i][j])
					{
						win = true;
						if (i < 3)
						{
							lineSprite.setTextureRect(IntRect(0, 0, 600, 10));
							int ly = 95 + 200 * i;
							lineSprite.setPosition(0, ly);
						}

						else if (i < 6)
						{
							lineSprite.setTextureRect(IntRect(0, 0, 600, 10));
							lineSprite.setRotation(90);
							int lx = 105 + 200 * (i - 3);
							lineSprite.setPosition(lx, 0);
						}

						else if (i == 6)
						{
							lineSprite.setTextureRect(IntRect(0, 10, 600, 600));
						}

						else if (i == 7)
						{
							lineSprite.setTextureRect(IntRect(600, 10, -600, 600));
						}
					}
			}

			if (hotBot && !win && num < 9)
			{
				num++;

				if (!dumBot) {
					botMove = BotMove();
					dumBot = true;
				}
				else {
					bool cdat = true;

					for (int i = 0; i < 3; i++) {
						if (player.field[i] && player.field[3 + i] && !lib[6 + i])
						{
							botMove = 6 + i;
							cdat = false;
						}

						if (player.field[6 + i] && player.field[3 + i] && !lib[i])
						{
							botMove = i;
							cdat = false;
						}

						if (player.field[3 * i] && player.field[1 + 3 * i] && !lib[2 + 3 * i])
						{
							botMove = 2 + 3 * i;
							cdat = false;
						}

						if (player.field[2 + 3 * i] && player.field[1 + 3 * i] && !lib[3 * i])
						{
							botMove = 3 * i;
							cdat = false;
						}
					}

					if (player.field[0] && player.field[4] && !lib[8])
					{
						botMove = 8;
						cdat = false;
					}

					if (player.field[8] && player.field[4] && !lib[0])
					{
						botMove = 0;
						cdat = false;
					}

					if (player.field[2] && player.field[4] && !lib[6])
					{
						botMove = 6;
						cdat = false;
					}

					if (player.field[6] && player.field[4] && !lib[2])
					{
						botMove = 2;
						cdat = false;
					}

					if (player.field[2] && player.field[6] && !lib[4])
					{
						botMove = 4;
						cdat = false;
					}

					if (cdat)
					{
						botMove = BotMove();
					}

				}

				bot.field[botMove] = true;
				lib[botMove] = true;
				hotBot = false;
			}

			player.update(ch);

			int biv = ch + 1;
			if (biv == 3)
			{
				biv = 1;
			}

			bot.update(biv);

			window.clear(Color::White);
			if (ch == 0)
			{
				for (int i = 0; i < 2; i++)
					window.draw(choice[i]);
			}

			else
			{
				window.draw(fontSprite);
				for (int i = 0; i < 9; i++)
				{
					if (player.field[i])
					{
						window.draw(player.sprite[i]);
					}

					if (bot.field[i])
					{
						window.draw(bot.sprite[i]);
					}
				}
			}

			if (win)
			{
				window.draw(lineSprite);
			}
			window.display();
		}
}

void Game::run() {

}