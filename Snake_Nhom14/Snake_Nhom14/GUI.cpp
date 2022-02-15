#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <mmsystem.h>
#include "GUI.h"
#include "Gameplay.h"
#include "Graphic.h"
#include "Sound.h"

bool playingGame = true;
bool howtoplay = false;
bool highscore = false;
bool exitGame = false;
bool exitStartMenu = false;
bool optionMenu = false;

POINT cursor = { 59, 19 };
using namespace std;

void DisplaySNAKE()
{
	DrawRectangle(9, 1, 1, 1, 15);
	DrawPixel(13, 1, 15);
	DrawRectangle(14, 1, 1, 7, 15);
	DrawRectangle(16, 1, 3, 2, 15);
	DrawRectangle(20, 1, 1, 7, 15);
	DrawRectangle(21, 1, 1, 2, 15);
	DrawRectangle(22, 1, 1, 1, 15);
	DrawRectangle(24, 1, 1, 1, 15);
	DrawRectangle(25, 1, 1, 2, 15);
	DrawRectangle(26, 1, 1, 7, 15);
	DrawRectangle(28, 1, 3, 1, 15);
	DrawRectangle(32, 1, 1, 7, 15);
	DrawRectangle(10, 2, 3, 2, 15);
	DrawRectangle(10, 2, 3, 2, 15);
	DrawPixel(23, 2, 15);
	DrawRectangle(28, 2, 2, 1, 15);
	DrawRectangle(31, 2, 1, 5, 15);
	DrawRectangle(10, 2, 3, 2, 15);
	DrawRectangle(34, 2, 4, 2, 15);
	DrawRectangle(13, 3, 1, 2, 15);
	DrawRectangle(17, 3, 2, 1, 15);
	DrawRectangle(22, 3, 3, 2, 15);
	DrawPixel(28, 3, 15);
	DrawRectangle(30, 3, 1, 3, 15);
	DrawRectangle(9, 4, 1, 2, 15);
	DrawRectangle(16, 4, 1, 4, 15);
	DrawPixel(18, 4, 15);
	DrawPixel(29, 4, 15);
	DrawRectangle(10, 5, 3, 2, 15);
	DrawRectangle(17, 5, 1, 3, 15);
	DrawRectangle(28, 5, 1, 3, 15);
	DrawRectangle(34, 5, 4, 2, 15);
	DrawRectangle(10, 6, 1, 1, 15);
	DrawRectangle(18, 6, 1, 2, 15);
	DrawRectangle(22, 6, 3, 2, 15);
	DrawRectangle(22, 6, 3, 2, 15);
	DrawRectangle(29, 6, 1, 2, 15);
	DrawPixel(9, 7, 15);
	DrawPixel(13, 7, 15);
	DrawPixel(30, 7, 15);
}
void DisplayGAME()
{
	DrawPixel(12, 9, 15);
	DrawPixel(16, 9, 15);
	DrawRectangle(17, 9, 1, 7, 15);
	DrawRectangle(17, 9, 1, 7, 15);
	DrawRectangle(18, 9, 1, 2, 15);
	DrawPixel(19, 9, 15);
	DrawPixel(21, 9, 15);
	DrawRectangle(22, 9, 1, 2, 15);
	DrawRectangle(23, 9, 1, 7, 15);
	DrawRectangle(25, 9, 3, 1, 15);
	DrawRectangle(29, 9, 1, 7, 15);
	DrawRectangle(13, 10, 2, 5, 15);
	DrawRectangle(15, 10, 1, 2, 15);
	DrawRectangle(15, 10, 1, 2, 15);
	DrawPixel(20, 10, 15);
	DrawPixel(26, 10, 15);
	DrawRectangle(31, 10, 4, 2, 15);
	DrawPixel(16, 11, 15);
	DrawRectangle(19, 11, 3, 2, 15);
	DrawRectangle(25, 11, 1, 5, 15);
	DrawRectangle(27, 11, 1, 5, 15);
	DrawRectangle(26, 12, 1, 4, 15);
	DrawRectangle(15, 13, 1, 2, 15);
	DrawRectangle(31, 13, 4, 2, 15);
	DrawRectangle(19, 14, 3, 2, 15);
	DrawPixel(12, 15, 15);
	DrawPixel(16, 15, 15);
}
void DisplaySNAKEIMG()
{
	DrawRectangle(26, 16, 1, 2, 2);
	DrawRectangle(22, 18, 6, 1, 3);
	DrawRectangle(21, 19, 8, 1, 3);
	DrawRectangle(20, 20, 10, 1, 3);
	DrawRectangle(19, 21, 12, 1, 3);
	DrawRectangle(18, 22, 6, 1, 3);
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
	DrawRectangle(15, 35, 14, 1, 3);
	DrawRectangle(16, 36, 12, 1, 3);
	DrawRectangle(17, 37, 10, 1, 3);
	DrawRectangle(18, 38, 8, 1, 3);
	DrawRectangle(25, 19, 2, 2, 15);
	DrawRectangle(26, 20, 1, 1, 0);
	DrawRectangle(15, 34, 5, 1, 12);
	DrawRectangle(16, 33, 3, 1, 12);
	DrawRectangle(17, 32, 1, 1, 12);
	DrawPixel(31, 22, 4);
	// DrawRectangle(32, 23, 2, 1, 4);
	DrawPixel(32, 23, 4);
	DrawRectangle(34, 25, 2, 2, 4);
}
void MenuBG()
{
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 6);
	DrawRectangle(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, 2);
	DrawRectangle(45, 1, 1, SCREEN_HEIGHT - 2, 15);
	DrawRectangle(9, 1, 29, 7, 12);
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
	GoToXYPixel(62, 19);
	SetColor(2, 11);
	cout << " START";
	GoToXYPixel(61, 20);
	cout << "HOW TO PLAY";
	GoToXYPixel(61, 21);
	cout << " HIGHSCORE";
	GoToXYPixel(62, 22);
	cout << "OPTION";
	GoToXYPixel(62, 23);
	cout << " EXIT";
	GoToXYPixel(61, 24);
	cout << "-----.------";
	SetColor(2, 15);
	GoToXYPixel(61, 25);
	cout << "WASD: Move" << endl;
	GoToXYPixel(61, 26);
	cout << "Enter: Select" << endl;
	GoToXYPixel(61, 27);
	cout << "Esc: Exit" << endl;
}

void PlayingGame()
{
	RunGamePlay();
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
	while (!exitGame)
	{
		cursor = { 59, 19 };
		MenuBG();
		StartMenu();
		while (1)
		{
			DrawPixel(cursor.x, cursor.y, 15);
			if (_kbhit())
			{
				int temp = _getch();
				DrawPixel(cursor.x, cursor.y, 2);
				GoToXYPixel(0, 3);
				if (sfx_toggle)
					PlayKey();
				if (temp == 27)
				{
					playingGame = false;
					exitGame = true;
					break;
				}
				else if (temp == 13)
				{
					exitGame = false;
					if (cursor.y == 19)
					{
						playingGame = true;
						howtoplay = false;
						highscore = false;
						optionMenu = false;
						exitGame = false;
					}
					else if (cursor.y == 20)
					{
						playingGame = false;
						howtoplay = true;
						highscore = false;
						optionMenu = false;
						exitGame = false;
					}
					else if (cursor.y == 21)
					{
						playingGame = false;
						howtoplay = false;
						highscore = true;
						optionMenu = false;
						exitGame = false;
					}
					else if (cursor.y == 22)
					{
						playingGame = false;
						howtoplay = false;
						highscore = false;
						optionMenu = true;
						exitGame = false;
					}
					else if (cursor.y == 23)
					{
						playingGame = false;
						howtoplay = false;
						highscore = false;
						optionMenu = false;
						exitGame = true;
					}
					break;
				}
				else if (toupper(temp) == 'S' && cursor.y < 23)
				{
					cursor.y++;
				}
				else if (toupper(temp) == 'W' && cursor.y > 19)
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
		else if (optionMenu)
		{
			OptionMenu();
		}
		else if (exitGame)
			return;
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

void OptionMenu()
{
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 6);
	DrawRectangle(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, 2);
	cursor = { 27, 12 };
	while (1)
	{
		DrawPixel(cursor, 15);
		SetColor(2, 15);
		GoToXYPixel(29, 12);
		cout << "Music: ";
		if (music_toggle)
		{
			cout << "enable ";
		}
		else
		{
			cout << "disable";
		}
		GoToXYPixel(29, 13);
		cout << "SFX  : ";
		if (sfx_toggle)
		{
			cout << "enable ";
		}
		else
		{
			cout << "disable";
		}
		GoToXYPixel(29, 14);
		cout << "Exit";
		if (_kbhit())
		{
			if (sfx_toggle)
				PlayKey();
			int temp = _getch();
			if (temp == 27)
			{
				return;
			}
			else if (temp == 13)
			{
				if (cursor.y == 12)
				{
					if (music_toggle)
					{
						StopMusic();
						music_toggle = false;
					}
					else
					{
						PlayMusic();
						music_toggle = true;
					}
				}
				else if (cursor.y == 13)
				{
					sfx_toggle = (sfx_toggle ? false : true);
				}
				else if (cursor.y == 14)
				{
					return;
				}
			}
			else if (toupper(temp) == 'W' && cursor.y > 12)
			{
				DrawPixel(cursor, 2);
				cursor.y--;
			}
			else if (toupper(temp) == 'S' && cursor.y < 14)
			{
				DrawPixel(cursor, 2);
				cursor.y++;
			}
		}
		Sleep(100);
	}
}