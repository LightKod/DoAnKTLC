#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <mmsystem.h>
#include "GUI.h"
#include "Gameplay.h"
#include "Graphic.h"

using namespace std;

void OptionMenu()
{

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
	playingGame = false;
}

void DisplayInstructions()
{
	ClearScreen();

	printf("\n\n");

	printf("\n\n\n");

	printf("\t\t      How to play \n");
	printf("\t\t      =========== \n\n\n");
	printf("\t     The objective of the game is to eat\n");
	printf("\t     as many food items as possible and avoid hitting the walls.\n");
	printf("\t     Each food items gives you points according to level\n");
	printf("\t     and you have to get more points - before the game ends. \n");
	printf("\n\n\n");
}
void GUI()
{
	while (!exitGame)
	{

		DrawRectangle(0, 0, 90, 70, 0);
		StartMenu();
		while (1)
		{
			DrawPixel(cursor.x, cursor.y, 15);
			if (_kbhit())
			{
				int temp = _getch();
				DrawPixel(cursor.x, cursor.y, 0);
				DrawRectangle(0, 3, 3, 0, 0);
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
