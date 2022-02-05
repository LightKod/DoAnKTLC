#include "Gameplay.h"
#include "Graphic.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

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
		// x = rand() % (SCREEN_WIDTH - 1) + 1;
		// y = rand() % (SCREEN_HEIGHT - 1) + 1;
		x = rand() % (43 - 2) + 2;
		y = rand() % (43 - 2) + 2;
	} while (!IsValid(x, y));
	food_pos.x = x;
	food_pos.y = y;
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
		DrawPixel(food_pos, 10, 7, 'X');
		Sleep(1000 / 60);
		DrawPixel(food_pos, DEFAULT_BACKGROUND_COLOR);
	}
}

void ResetData()
{
	snakeSize = 2;
	snake_pos[0] = {2, 2};
	snake_pos[1] = {2, 2};
	snake_color = 3;
	snake_dir = Direction::STOP;
	snake_state = State::ALIVE;
	snake_speed = 10;
	score = 0;
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
	DrawBorder(1, 1, 43, 43, 15, 0);
	GenerateFood();
	DrawPixel(food_pos, food_color);
	while (1)
	{
		DrawPixels(snake_pos, snakeSize, snake_color);
		POINT last_pos = snake_pos[snakeSize - 1];
		GameInput();
		if (snake_dir != Direction::STOP && snake_state != State::DEAD)
		{
			timer += 1 / (float)60;
			if (timer >= 1 / snake_speed)
			{
				timer = 0;
				DrawPixel(last_pos, DEFAULT_BACKGROUND_COLOR);
				Move();
				ProcessDead();
				Eat(last_pos);
			}
		}
		else
		{
			timer = 1;
		}
		if (snake_state == State::DEAD)
		{
			GoToXYPixel(20, 20);
			cout << "DEAD";
			GoToXYPixel(20, 21);
			cout << "Press any key to restart";
			if (_kbhit)
			{
				if (_getch())
				{
					ResetData();
					DrawBorder(1, 1, 43, 43, 15, 0);
					GenerateFood();
					DrawPixel(food_pos, food_color);
				}
			}
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

bool IsHitTheWall()
{
	switch (snake_dir)
	{
	case Direction::UP:
		if (snake_pos[0].y == 1)
		{
			return true;
		}
		break;

	case Direction::DOWN:
		if (snake_pos[0].y == 43)
		{
			return true;
		}
		break;
	case Direction::LEFT:
		if (snake_pos[0].x == 1)
		{
			return true;
		}
		break;
	case Direction::RIGHT:
		if (snake_pos[0].x == 43)
		{
			return true;
		}
		break;
	}
	return false;
}

bool IsHitYourself()
{
	for (int i = 1; i < snakeSize; i++)
	{
		if (snake_pos[0].x == snake_pos[i].x && snake_pos[0].y == snake_pos[i].y)
		{
			return true;
		}
	}
	return false;
}

void ProcessDead()
{
	if (IsHitTheWall() || IsHitYourself())
	{
		snake_state = State::DEAD;
		snake_dir = Direction::STOP;
	}
}

void Eat(POINT last_pos)
{
	if (snake_pos[0].x == food_pos.x && snake_pos[0].y == food_pos.y)
	{
		snakeSize++;
		snake_pos[snakeSize - 1] = last_pos;
		DrawPixel(food_pos, DEFAULT_BACKGROUND_COLOR);
		GenerateFood();
		DrawPixel(food_pos, food_color);
	}
}