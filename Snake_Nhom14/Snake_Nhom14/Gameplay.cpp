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
	snakeSize = 2;
	snake_pos[0] = {1, 0};
	snake_pos[1] = {0, 0};
	snake_dir = Direction::STOP;
	snake_state = State::ALIVE;
	snake_speed = 10;
}

void MoveRight()
{
	for (int i = snakeSize - 1; i > 0; i--)
	{
		snake_pos[i] = snake_pos[i - 1];
	}
	snake_pos[0].x++;
}

void MoveLeft()
{
	for (int i = snakeSize - 1; i > 0; i--)
	{
		snake_pos[i] = snake_pos[i - 1];
	}
	snake_pos[0].x--;
}

void MoveUp()
{
	for (int i = snakeSize - 1; i > 0; i--)
	{
		snake_pos[i] = snake_pos[i - 1];
	}
	snake_pos[0].y--;
}
void MoveDown()
{
	for (int i = snakeSize - 1; i > 0; i--)
	{
		snake_pos[i] = snake_pos[i - 1];
	}
	snake_pos[0].y++;
}

void TestSnakeMove()
{
	float timer = 1;
	while (1)
	{
		DrawPixels(snake_pos, snakeSize, snake_color);
		POINT last_pos = snake_pos[snakeSize - 1];
		GameInput();
		if (snake_dir != Direction::STOP)
		{
			timer += 1 / (float)60;
			if (timer >= 1 / snake_speed)
			{
				timer = 0;
				Move();
				DrawPixel(last_pos, DEFAULT_BACKGROUND_COLOR);
			}
		}
		else
		{
			timer = 1;
		}
		Sleep(1000 / 60);
	}
}

void GameInput()
{
	if (_kbhit())
	{
		int temp = _getch();
		switch (toupper(temp))
		{
		case 'A':
			if (snake_dir != Direction::RIGHT)
				snake_dir = Direction::LEFT;
			break;

		case 'D':
			if (snake_dir != Direction::LEFT)
				snake_dir = Direction::RIGHT;
			break;

		case 'W':
			if (snake_dir != Direction::DOWN)
				snake_dir = Direction::UP;
			break;

		case 'S':
			if (snake_dir != Direction::UP)
				snake_dir = Direction::DOWN;
			break;

		default:
			break;
		}
	}
}

void Move()
{
	switch (snake_dir)
	{
	case Direction::LEFT:
		MoveLeft();
		break;

	case Direction::RIGHT:
		MoveRight();
		break;

	case Direction::UP:
		MoveUp();
		break;
	case Direction::DOWN:
		MoveDown();
		break;
	}
}