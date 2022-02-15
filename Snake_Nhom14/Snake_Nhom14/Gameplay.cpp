#include "Gameplay.h"
#include "Graphic.h"
#include "GUI.h"
#include "Sound.h"
#include "SaveLoad.h"
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

bool IsWallValid(int x, int y)
{
	for (int i = 0; i < wall_size; i++)
	{
		if (wall_pos[i].x == x && wall_pos[i].y == y)
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
		x = rand() % (game_field_width - 2) + game_field_pos.x + 1;
		y = rand() % (game_field_height - 2) + game_field_pos.y + 1;
	} while (!IsValid(x, y) || !IsWallValid(x, y));
	food_pos.x = x;
	food_pos.y = y;
	if (current_last_text >= textSize - 1)
	{
		food_text = snake_default_text[0];
	}
	else
	{
		food_text = snake_default_text[current_last_text + 1];
	}
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
	snake_dir = Direction::RIGHT;
	snake_state = State::ALIVE;
	snake_speed = 5;
	score = 0;
	game_time = 0;
	t1 = time(0);
	wall_size = 0;
	gate_state = 0;
	level = 1;
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

void RunGamePlay()
{
	float timer = 1;
	int h = 0, min = 0, sec = 0;
	ResetData();
	GameplayUI();
	GenerateWallNew();
	GenerateFood();
	DrawPixel(food_pos, food_color, 15, food_text);
	while (1)
	{

		DrawPixels(snake_pos, snakeSize, snake_color, 15, snake_text);
		DrawPixels(wall_pos, wall_size, wall_color);
		if (gate_state == 1)
		{
			DrawGate(gate_pos, gate_color, gate_dir);
		}
		GoToXYPixel(46, 2);
		SetColor(0, 15);
		cout << "SCORE: " << score;
		GoToXYPixel(46, 4);
		SetColor(0, 15);
		cout << "TIME: " << game_time << " => " << h << ":" << min << ":" << sec << " ";
		GoToXYPixel(46, 6);
		SetColor(0, 15);
		cout << "LEVEL: " << level << " ";

		if (snake_state != State::DEAD)
		{
			GameInput();
			if (snake_dir != Direction::STOP)
			{
				t2 = time(0);
				game_time += t2 - t1;
				h = game_time / 3600;
				min = game_time / 60 - 60 * h;
				sec = game_time - h * 3600 - min * 60;
				t1 = time(0);
				timer += 0.01;
				if (timer >= 1 / snake_speed)
				{
					timer = 0;
					ProcessDead();
					Move();
					Eat();
				}
			}
			else
			{
				timer = 1;
				t1 = time(0);
			}
		}
		else
		{
			bool saveName = false;
			if (dataSize < 10)
			{
				saveName = true;
			}
			else
			{
				for (int i = 0; i < dataSize; i++)
				{
					if (playerDatas[i].score <= score)
					{
						saveName = true;
						break;
					}
				}
			}
			GoToXYPixel(46, 8);
			SetColor(0, 15);
			if (saveName)
			{

				cout << "Enter name: ";
				ShowCursor(true);
				cin.getline(name, 4);
				PlayerData playerData;
				strcpy_s(playerData.name, name);
				playerData.score = score;
				Save(playerData);
				ShowCursor(false);
				GoToXYPixel(46, 9);
				SetColor(0, 15);
				cout << "Press esc to exit game              ";
				while (1)
				{
					if (_kbhit())
					{
						int temp = _getch();
						if (temp == 27)
						{
							return;
						}
						else
						{
							ResetData();
							h = 0;
							min = 0;
							sec = 0;
							GameplayUI();
							SpawnFood();
						}
					}
				}
			}
			else
			{
				cout << "Press any key to restart";
				GoToXYPixel(46, 9);
				SetColor(0, 15);
				cout << "Press esc to exit game              ";
				if (_kbhit())
				{
					int temp = _getch();
					if (temp == 27)
					{
						return;
					}
					else
					{
						ResetData();
						h = 0;
						min = 0;
						sec = 0;
						GameplayUI();
						SpawnFood();
					}
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
		if (temp == 27)
		{
			OptionMenu();
			GameplayUI();
			DrawPixel(food_pos, food_color, 15, food_text);
		}
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
	DrawPixel(last_pos, game_field_color);
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

bool IsHitTheBorder()
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

bool IsHitTheWall()
{
	for (int i = 0; i < wall_size; i++)
	{
		switch (snake_dir)
		{
		case Direction::UP:
			if (snake_pos[0].y == wall_pos[i].y + 1 && snake_pos[0].x == wall_pos[i].x)
			{
				return true;
			}
			break;
		case Direction::DOWN:
			if (snake_pos[0].y == wall_pos[i].y - 1 && snake_pos[0].x == wall_pos[i].x)
			{
				return true;
			}
			break;
		case Direction::LEFT:
			if (snake_pos[0].x == wall_pos[i].x + 1 && snake_pos[0].y == wall_pos[i].y)
			{
				return true;
			}
			break;
		case Direction::RIGHT:
			if (snake_pos[0].x == wall_pos[i].x - 1 && snake_pos[0].y == wall_pos[i].y)
			{
				return true;
			}
			break;
		}
	}
	return false;
}

void ProcessDead()
{
	if (IsHitTheBorder() || IsHitYourself() || IsHitTheWall() || IsHitTheGate())
	{
		snake_state = State::DEAD;
		snake_dir = Direction::STOP;
	}
}

void Eat()
{
	if (snake_pos[0].x == food_pos.x && snake_pos[0].y == food_pos.y)
	{
		if (sfx_toggle)
			PlayEatSound();
		score += level * 10;
		snakeSize++;
		if (snakeSize % 4 == 0)
		{
			snake_speed += 1;
		}
		snake_pos[snakeSize - 1] = last_pos;
		snake_color[snakeSize - 1] = 9;
		current_last_text++;
		if (current_last_text >= textSize)
		{
			current_last_text = 0;
		}
		snake_text[snakeSize - 1] = snake_default_text[current_last_text];
		if (snakeSize != (9 * level))
		{
			SpawnFood();
		}
		if (snakeSize == (9 * level))
		{
			gate_state = 1;
			GenerateGate();
		}
	}

	if (snake_pos[0].x == gate_pos.x && snake_pos[0].y == gate_pos.y && gate_state == 1)
	{
		ToTheNextLevel();
	}
}

void SpawnFood()
{
	DrawPixel(food_pos, game_field_color);
	GenerateFood();
	DrawPixel(food_pos, food_color, 15, food_text);
}

bool IsAlreadyHad(int x, int y)
{
	for (int i = 0; i < wall_size; i++)
	{
		if (wall_pos[i].x == x && wall_pos[i].y == y)
		{
			return true;
		}
	}
	return false;
}

void GenerateWall()
{
	if (wall_size >= 1600)
	{
		return;
	}
	int x, y;
	do
	{
	x = rand() % (game_field_width - 2) + game_field_pos.x + 1;
	y = rand() % (game_field_height - 2) + game_field_pos.y + 1;
	} while (!IsValid(x, y) || IsAlreadyHad(x, y));
	wall_size++;
	wall_pos[wall_size - 1] = { x, y };
}

void GenerateWallNew()
{
	switch ((level))
	{
	case 1: // Level 1: 0 wall
		wall_size = 0;
		break;
	case 2: // Level 2: 4 cuc vuong o 4 goc
		wall_size = 16;
		// Top Right
		wall_pos[0] = { 5, 5 };
		wall_pos[1] = { 6, 5 };
		wall_pos[2] = { 6, 6 };
		wall_pos[3] = { 5, 6 };

		// Top Left
		wall_pos[4] = { 42 - 5, 5 };
		wall_pos[5] = { 42 - 6, 5 };
		wall_pos[6] = { 42 - 6, 6 };
		wall_pos[7] = { 42 - 5, 6 };

		// Bottom Left
		wall_pos[8] = { 42 - 5, 42 - 5 };
		wall_pos[9] = { 42 - 6, 42 - 5 };
		wall_pos[10] = { 42 - 6, 42 - 6 };
		wall_pos[11] = { 42 - 5, 42 - 6 };

		// Bottom Right
		wall_pos[12] = { 5, 42 - 5 };
		wall_pos[13] = { 6, 42 - 5 };
		wall_pos[14] = { 6, 42 - 6 };
		wall_pos[15] = { 5, 42 - 6 };
		break;

	case 3:
		wall_size = 28;

		// Top left
		wall_pos[0] = { 6, 3 };
		wall_pos[1] = { 6, 4 };
		wall_pos[2] = { 6, 5 };
		wall_pos[3] = { 6, 6 };
		wall_pos[4] = { 5, 6 };
		wall_pos[5] = { 4, 6 };
		wall_pos[6] = { 3, 6 };

		// Top right
		wall_pos[7] = { 38, 3 };
		wall_pos[8] = { 38, 4 };
		wall_pos[9] = { 38, 5 };
		wall_pos[10] = { 38, 6 };
		wall_pos[11] = { 39, 6 };
		wall_pos[12] = { 40, 6 };
		wall_pos[13] = { 41, 6 };

		// Bottom right
		wall_pos[14] = { 38, 41 };
		wall_pos[15] = { 38, 40 };
		wall_pos[16] = { 38, 39 };
		wall_pos[17] = { 38, 38 };
		wall_pos[18] = { 39, 38 };
		wall_pos[19] = { 40, 38 };
		wall_pos[20] = { 41, 38 };

		// Bottom left
		wall_pos[21] = { 6, 41 };
		wall_pos[22] = { 6, 40 };
		wall_pos[23] = { 6, 39 };
		wall_pos[24] = { 6, 38 };
		wall_pos[25] = { 5, 38 };
		wall_pos[26] = { 4, 38 };
		wall_pos[27] = { 3, 38 };
		break;

	case 4: {
		wall_size = 90;

		// Outside
		int i = 0;
		for (int temp1 = 8, temp2 = 8; i < (wall_size - 30) / 4; i++)
		{
			wall_pos[i] = { temp1, temp2 };
			wall_pos[90 - i - 1] = { 44 - temp1,44 - temp2 };
			i++;
			wall_pos[i] = { 44 - temp1, temp2 };
			wall_pos[wall_size - i - 1] = { temp1, 44 - temp2 };
			if (i < 7) temp1++;
			else {
				temp1 = 8; temp2++;
			}
		}

		//Inside
		for (int temp1 = 13, temp2 = 16; i < (wall_size / 2); i++)
		{
			wall_pos[i] = { temp1, temp2 };
			wall_pos[90 - i - 1] = { 44 - temp1,44 - temp2 };
			i++;
			wall_pos[i] = { 44 - temp1, temp2 };
			wall_pos[wall_size - i - 1] = { temp1, 44 - temp2 };
			if (i < (wall_size / 2) - 5) temp1++;
			else {
				temp1 = 13; temp2++;
			}
		}

		break;
	}
	}
}

void SetGateCollider()
{
	switch (gate_dir)
	{
	case 0:
		gate_colliders[0] = {gate_pos.x - 1, gate_pos.y};
		gate_colliders[1] = {gate_pos.x + 1, gate_pos.y};
		gate_colliders[2] = {gate_pos.x - 1, gate_pos.y + 1};
		gate_colliders[3] = {gate_pos.x, gate_pos.y + 1};
		gate_colliders[4] = {gate_pos.x + 1, gate_pos.y + 1};
		break;

	case 1:
		gate_colliders[0] = {gate_pos.x - 1, gate_pos.y - 1};
		gate_colliders[1] = {gate_pos.x, gate_pos.y - 1};
		gate_colliders[2] = {gate_pos.x + 1, gate_pos.y - 1};
		gate_colliders[3] = {gate_pos.x - 1, gate_pos.y};
		gate_colliders[4] = {gate_pos.x + 1, gate_pos.y};
		break;

	case 2:
		gate_colliders[0] = {gate_pos.x, gate_pos.y - 1};
		gate_colliders[1] = {gate_pos.x + 1, gate_pos.y - 1};
		gate_colliders[2] = {gate_pos.x + 1, gate_pos.y};
		gate_colliders[3] = {gate_pos.x, gate_pos.y + 1};
		gate_colliders[4] = {gate_pos.x + 1, gate_pos.y + 1};
		break;

	case 3:
		gate_colliders[0] = {gate_pos.x - 1, gate_pos.y - 1};
		gate_colliders[1] = {gate_pos.x, gate_pos.y - 1};
		gate_colliders[2] = {gate_pos.x - 1, gate_pos.y};
		gate_colliders[3] = {gate_pos.x - 1, gate_pos.y + 1};
		gate_colliders[4] = {gate_pos.x, gate_pos.y + 1};
		break;

	case 4:
		gate_colliders[0] = { gate_pos.x - 1, gate_pos.y - 1 };
		gate_colliders[1] = { gate_pos.x - 1, gate_pos.y - 1 };
		gate_colliders[2] = { gate_pos.x - 1, gate_pos.y };
		gate_colliders[3] = { gate_pos.x - 1, gate_pos.y + 1 };
		gate_colliders[4] = { gate_pos.x, gate_pos.y + 1 };
		break;
	}
}

bool IsHitTheGate()
{
	if (gate_state == 0)
	{
		return false;
	}
	for (int i = 0; i < 5; i++)
	{
		switch (snake_dir)
		{
		case Direction::UP:
			if (snake_pos[0].y == gate_colliders[i].y + 1 && snake_pos[0].x == gate_colliders[i].x)
			{
				return true;
			}
			break;
		case Direction::DOWN:
			if (snake_pos[0].y == gate_colliders[i].y - 1 && snake_pos[0].x == gate_colliders[i].x)
			{
				return true;
			}
			break;
		case Direction::LEFT:
			if (snake_pos[0].x == gate_colliders[i].x + 1 && snake_pos[0].y == gate_colliders[i].y)
			{
				return true;
			}
			break;
		case Direction::RIGHT:
			if (snake_pos[0].x == gate_colliders[i].x - 1 && snake_pos[0].y == gate_colliders[i].y)
			{
				return true;
			}
			break;
		}
	}
	return false;
}

void GenerateGate()
{
	int x, y;
	do
	{
		x = rand() % (game_field_width - 8) + game_field_pos.x + 1;
		y = rand() % (game_field_height - 8) + game_field_pos.y + 1;
	} while (!IsValid(x, y) || !IsWallValid(x, y));
	gate_pos = {x, y};
	gate_dir = rand() % 4;
	SetGateCollider();
}

void ToTheNextLevel()
{
	GameplayUI();
	gate_state = 0;
	level += 1;
	/*for (int i = 0; i < level; i++)
	{
		GenerateWall();
	}*/
	GenerateWallNew();
	SpawnFood();
}