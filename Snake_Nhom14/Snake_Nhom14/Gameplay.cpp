#include "Gameplay.h"
#include "Graphic.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

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
	food_text = snake_default_text[current_last_text + 1];
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
	snake_pos[0] = {3, 2};
	snake_pos[1] = {2, 2};
	snake_text[0] = snake_default_text[0];
	snake_text[1] = snake_default_text[1];
	current_last_text = 1;
	snake_color = 2;
	snake_dir = Direction::RIGHT;
	snake_state = State::ALIVE;
	snake_speed = 10;
	score = 0;
	t1 = time(0);
	game_time = 0;
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
	DrawPixel(food_pos, food_color, 15, food_text);
	while (1)
	{
		DrawPixels(snake_pos, snakeSize, snake_color, 15, snake_text);
		DrawRectangle(45, 2, 10, 1, 0);
		GoToXYPixel(45, 2);
		SetColor(0, 15);
		cout << "Score: " << score;
		DrawRectangle(45, 4, 10, 1, 0);
		GoToXYPixel(45, 4);
		SetColor(0, 15);
		t2 = time(0);
		game_time += t2 - t1;
		t1 = time(0);
		cout << "Time: " << game_time;
		if (snake_state != State::DEAD)
		{
			GameInput();
			if (snake_dir != Direction::STOP)
			{
				timer += 1 / fps;
				if (timer >= 1 / snake_speed)
				{
					timer = 0;
					ProcessDead();
					Move();
					DrawPixel(last_pos, DEFAULT_BACKGROUND_COLOR);
					Eat();
				}
			}
			else
			{
				timer = 1;
			}
		}
		else
		{
			GoToXYPixel(20, 20);
			cout << "DEAD";
			GoToXYPixel(20, 21);
			cout << "Press any key to restart";
			if (_kbhit())
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
		Sleep(1000 / fps);
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
	last_pos = snake_pos[snakeSize - 1];
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
		if (snake_pos[0].y == 2)
		{
			return true;
		}
		break;

	case Direction::DOWN:
		if (snake_pos[0].y == 42)
		{
			return true;
		}
		break;
	case Direction::LEFT:
		if (snake_pos[0].x == 2)
		{
			return true;
		}
		break;
	case Direction::RIGHT:
		if (snake_pos[0].x == 42)
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

void Eat()
{
	if (snake_pos[0].x == food_pos.x && snake_pos[0].y == food_pos.y)
	{
		score += 10;
		snakeSize++;
		if (snakeSize % 8 == 0)
		{
			snake_speed += 5;
		}
		snake_pos[snakeSize - 1] = last_pos;
		current_last_text++;
		if (current_last_text >= textSize)
		{
			current_last_text = 0;
		}
		snake_text[snakeSize - 1] = snake_default_text[current_last_text];
		DrawPixel(food_pos, DEFAULT_BACKGROUND_COLOR);
		GenerateFood();
		DrawPixel(food_pos, food_color, 15, food_text);
	}
}