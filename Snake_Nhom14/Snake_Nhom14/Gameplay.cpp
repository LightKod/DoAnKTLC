#include "Gameplay.h"
#include "Graphic.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

bool IsValid(int x, int y)
{
	for (int i = 0; i < snakeSize; i++)
	{
		if (snake_pos[i].x == x && snake_pos[i].y == y)
		{
			return false;
		}
	}
	return true;
}
void GenerateFood()
{
	int x, y;
	do
	{
		x = rand() % (SCREEN_WIDTH - 1) + 1;
		y = rand() % (SCREEN_HEIGHT - 1) + 1;
	} while (!IsValid(x, y));
	food.x = x;
	food.y = y;
}

void TestFoodSpawn()
{
	while (true)
	{
		if (_kbhit())
		{
			int temp = _getch();
			if (temp)
				GenerateFood();
		}
		DrawPixel(food, 10, 7, 'X');
		Sleep(1000 / 60);
		DrawPixel(food, DEFAULT_BACKGROUND_COLOR);
	}
}

void ResetData()
{
	snakeSize = 1;
	snake_pos[0] = {0, 0};
	snake_dir = Direction::STOP;
	snake_state = State::ALIVE;
}