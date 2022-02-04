#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <mmsystem.h>
#include "GUI.h"
#include "Gameplay.h"
#include "Graphic.h"
bool playingGame = true;
bool howtoplay = true;
bool score = true;
bool exitGame = false;
bool exitStartMenu = false;

POINT cursor = { 0, 0 };
void Option()
{

	if (playingGame);
	else if (howtoplay)
	{
		printf("\t\t      How to play \n");
		printf("\t\t      =========== \n\n\n");
		printf("\t     The objective of the game is to eat\n");
		printf("\t as many food items as possible and     \n");
		printf("\t avoid hitting the walls.               \n");
		printf("\t     Each food items gives you 10 points\n");
		printf("\t and you have 3 lives - 3 chances to get\n");
		printf("\t more points - before the game ends.    \n");
	}
	else if (score);
	else if (exitGame)
		return;

}
void GUI()
{
	using namespace std;
	SetUp();
	SetConsoleOutputCP(65001);
	srand(time(NULL));


	while (!exitGame)
	{

		DrawRectangle(0, 0, 50, 30, 0);
		GoToXYPixel(2, 0);
		SetColor(0, 4);
		cout << "START";
		SetColor(0, 7);
		GoToXYPixel(2, 1);
		SetColor(0, 1);
		cout << "How to play";
		SetColor(0, 7);
		GoToXYPixel(2, 2);
		SetColor(0, 1);
		cout << "Score";
		SetColor(0, 7);
		GoToXYPixel(2, 3);
		SetColor(0, 1);
		cout << "Exit";
		SetColor(0, 7);
		GoToXYPixel(0, 4);
		cout << "WASD: move" << endl
			<< "Enter: select" << endl
			<< "Esc: exit" << endl;

		while (1)
		{
			DrawPixel(cursor.x, cursor.y, 0);
			if (_kbhit())
			{
				int temp = _getch();
				DrawRectangle(0, 3, 3, 0, 0);
				GoToXYPixel(0, 3);
				if (temp == 27)
				{
					playingGame = false;
					howtoplay = false;
					score = false;
					exitGame = true;
					break;
				}
				else if (temp == 13)
				{
					exitGame = false;
					if (cursor.y == 0)
					{
						playingGame = true;
						howtoplay = false;
						score = false;
						exitGame = false;
					}
					else if(cursor.y==1)
					{
						playingGame = false;
						howtoplay = true;
						score = false;
						exitGame = false;
					}
					else if (cursor.y == 2)
					{
						playingGame = false;
						howtoplay = false;
						score = true;
						exitGame = false;
					}
					else if (cursor.y == 3)
					{
						playingGame = false;
						howtoplay = false;
						score = false;
						exitGame = true;
					}
					break;
				}
				if (toupper(temp) == 'S' && cursor.y == 0)
						{
							cursor.y++;
						}
				else if (toupper(temp) == 'W' && cursor.y == 1)
				{
					cursor.y--;
				}
			}
			Option();
			DrawPixel(cursor.x, cursor.y, 15);
			Sleep(100);
		}
	}
}
