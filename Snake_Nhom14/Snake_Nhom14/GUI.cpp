#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <mmsystem.h>
#include "GUI.h"
#include "Gameplay.h"
#include "Graphic.h"
bool playingGame = true;
bool howtoplay = false;
bool highscore = false;
bool exitGame = false;
bool exitStartMenu = false;

POINT cursor = { 59, 19 };
using namespace std;

void DisplaySNAKE()
{
	DrawPixel(10, 1, 15);
	DrawRectangle(13, 1, 2, 1, 15);
	DrawRectangle(16, 1, 2, 2, 15);
	DrawRectangle(19, 1, 4, 2, 15);
	DrawRectangle(24, 1, 4, 2, 15);
	DrawRectangle(29, 1, 2, 1, 15);
	DrawRectangle(32, 1, 1, 7, 15);
	DrawRectangle(11, 2, 2, 2, 15);
	DrawRectangle(14, 2, 1,6, 15);
	DrawRectangle(23, 2, 1, 2, 15);
	DrawRectangle(29, 2, 1, 2, 15);
	DrawRectangle(31, 2, 1, 5, 15);
	DrawRectangle(34, 2, 3, 2, 15);
	DrawRectangle(13, 3, 1, 2, 15);
	DrawRectangle(17, 3, 1, 2, 15);
	DrawRectangle(19, 3, 3, 2, 15);
	DrawRectangle(25, 3, 3, 2, 15);
	DrawRectangle(30, 3, 1, 3, 15);
	DrawRectangle(10, 4, 1, 2, 15);
	DrawRectangle(16, 4, 1, 4, 15);
	DrawRectangle(11, 5, 2, 2, 15);
	DrawRectangle(19, 5, 2, 2, 15);
	DrawRectangle(22, 5, 3, 3, 15);
	DrawRectangle(26, 5, 2, 2, 15);
	DrawRectangle(29, 5, 1, 3, 15);
	DrawRectangle(34, 5, 3, 2, 15);
	DrawRectangle(17, 6, 1, 2, 15);
	DrawRectangle(21, 6, 1, 2, 15);
	DrawRectangle(25, 6, 1, 2, 15);
	DrawPixel(10, 7, 15);
	DrawPixel(13, 7, 15);
	DrawPixel(19, 7, 15);
	DrawPixel(27, 7, 15);
	DrawPixel(30, 7, 15);
}
void DisplayGAME()
{
	DrawPixel(12, 9, 15);
	DrawPixel(15, 9, 15);
	DrawRectangle(16, 9, 3, 4, 15);
	DrawRectangle(19, 9, 1, 2, 15);
	DrawRectangle(21, 9, 4, 2, 15);
	DrawRectangle(26, 9, 3, 1, 15);
	DrawRectangle(30, 9, 1, 7, 15);
	DrawRectangle(13, 10, 2, 2, 15);
	DrawRectangle(20, 10, 1, 2, 15);
	DrawRectangle(27, 10, 1, 2, 15);
	DrawRectangle(32, 10, 3, 2, 15);
	DrawPixel(15, 11, 15);
	DrawRectangle(22, 11, 3, 2, 15);
	DrawRectangle(26, 11, 1, 5, 15);
	DrawRectangle(28, 11, 1, 5, 15);
	DrawRectangle(13, 12, 1, 3, 15);
	DrawRectangle(14, 13, 1, 2, 15);
	DrawRectangle(26, 13, 1, 5, 15);
	DrawRectangle(16, 13, 2, 2, 15);
	DrawRectangle(19, 13, 3, 3, 15);
	DrawRectangle(23, 13, 2, 2, 15);
	DrawRectangle(27, 13, 1, 3, 15);
	DrawRectangle(32, 13, 3, 2, 15);
	DrawRectangle(18, 14, 1, 2, 15);
	DrawRectangle(22, 14, 1, 2, 15);
	DrawRectangle(12, 15, 1, 1, 15);
	DrawRectangle(15, 15, 2, 1, 15);
	DrawRectangle(24, 15, 1, 1, 15);
}
void DisplaySNAKEIMG()
{
	DrawRectangle(26, 16, 1, 2, 2);
	DrawRectangle(22, 18, 6, 1, 3);
	DrawRectangle(21, 19, 8, 1, 3);
	DrawRectangle(20, 20, 10, 1, 3);
	DrawRectangle(19, 21, 12, 1, 3);
	DrawRectangle(18, 22,5, 1, 3);
	DrawRectangle(17, 23, 6, 3, 3);
	DrawRectangle(18, 26, 6, 1, 3);
	DrawRectangle(19, 27, 6, 1, 3);
	DrawRectangle(20, 28, 6, 1, 3);
	DrawRectangle(21, 29, 6, 1, 3);
	DrawRectangle(22, 30, 6, 1, 3);
	DrawRectangle(23, 31, 6, 1, 3);
	DrawRectangle(24, 32, 6, 1, 3);
	DrawRectangle(25, 33, 5, 1, 3);
	DrawRectangle(24, 34, 6, 1, 3);
	DrawRectangle(16, 35, 13, 1, 3);
	DrawRectangle(17, 36, 11, 1, 3);
	DrawRectangle(18, 37, 9, 1, 3);
	DrawRectangle(25, 19, 2, 2, 15);
	DrawRectangle(26, 20, 1, 1, 0);
	DrawRectangle(16, 30, 3, 5, 14);
	DrawPixel(31, 22, 4);
	DrawRectangle(32, 23, 2, 1, 4);
	DrawPixel(32, 24, 4);
}
void MenuBG()
{
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 6);
	DrawRectangle(1, 1, SCREEN_WIDTH-2, SCREEN_HEIGHT-2, 2);
	DrawRectangle(45, 1, 1, SCREEN_HEIGHT - 2, 15);
	DrawRectangle(10, 1, 27,7, 12);
	DrawRectangle(12, 9, 23, 7, 12);
	DisplaySNAKE();
	DisplayGAME();
	DisplaySNAKEIMG();
}
void ClearScreen()
{
	system("cls");
}
void StartMenu()
{
	GoToXYPixel(2, 0);
	SetColor(0, 4);
	cout << "START";
	GoToXYPixel(2, 1);
	SetColor(0, 1);
	cout << "HOW TO PLAY";
	GoToXYPixel(2, 2);
	SetColor(0, 1);
	cout << "HIGHSCORE";
	GoToXYPixel(2, 3);
	SetColor(0, 1);
	cout << "EXIT";
	SetColor(0, 7);
	GoToXYPixel(0, 4);
	cout << "WASD: move" << endl
		<< "Enter: select" << endl
		<< "Esc: exit" << endl;
}

void PlayingGame()
{
	TestSnakeMove();
}

void DisplayInstructions()
{
	ClearScreen();
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 6);
	DrawRectangle(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, 2);
	SetColor(2, 15);
	GoToXYPixel(29, 12);
	printf("\t\t      How to play \n");
	GoToXYPixel(29, 13);
	printf("\t\t      =========== \n\n\n");
	GoToXYPixel(29, 14);
	printf("\t   The objective of the game is to eat\n");
	GoToXYPixel(29, 15);
	printf("\t   as many food items as possible and     \n");
	GoToXYPixel(29, 16);
	printf("\t        avoid hitting the walls.               \n");
	GoToXYPixel(29, 17);
	printf("\t   Each food items gives you 10 points\n");
	GoToXYPixel(29, 18);
	printf("\t      and you have 3 lives to get\n");
	GoToXYPixel(29, 19);
	printf("\t    more points - before the game ends.    \n");
	GoToXYPixel(29, 22);
}
void GUI()
{
	MenuBG();
	while (!exitGame)
	{
		StartMenu();
		while (1)
		{
			DrawPixel(cursor.x, cursor.y, 15);
			if (_kbhit())
			{
				int temp = _getch();
				DrawPixel(cursor.x, cursor.y, 2);
				GoToXYPixel(0, 3);
				if (temp == 27)
				{
					playingGame = false;
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
						highscore = false;
						exitGame = false;
					}
					else if (cursor.y == 1)
					{
						playingGame = false;
						howtoplay = true;
						highscore = false;
						exitGame = false;
					}
					else if (cursor.y == 2)
					{
						playingGame = false;
						howtoplay = false;
						highscore = true;
						exitGame = false;
					}
					else if (cursor.y == 3)
					{
						playingGame = false;
						howtoplay = false;
						highscore = false;
						exitGame = true;
					}
					break;
				}
				else if (toupper(temp) == 'S' && cursor.y != 3)
				{
					cursor.y++;
				}
				else if (toupper(temp) == 'W' && cursor.y != 0)
				{
					cursor.y--;
				}
			}
		}
		if (playingGame)
		{
			PlayingGame();
		}
		else if (howtoplay)
		{
			DisplayInstructions();
			printf("\t Press any key to return to the main menu...");
			while (true)
				if (_kbhit())
					break;
			_getch();
		}
		else if (highscore)
			;
		else if (exitGame)
			return;
		else if (optionMenu) {
			OptionMenu();
		}
		Sleep(100);
	}
}

void GameplayUI()
{
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 6);
	DrawBorder(game_field_pos, game_field_width, game_field_height, 15, game_field_color);
	DrawBorder(45, 1, 34, 10, 15, 0);
	DrawBorder(45, 12, 34, 32, 15, 0);
}
