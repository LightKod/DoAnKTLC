#include "Gameplay.h"
#include "Graphic.h"
#include "GUI.h"
#include "Sound.h"
#include "SaveLoad.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <fstream>

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
	} while (!IsValid(x, y));
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
				Generate2Food();
		}
		DrawPixel(two_food_pos[0], 10, 7, 'X');
		DrawPixel(two_food_pos[1], 10, 7, 'X');

		Sleep(1000 / 60);
		DrawPixel(food_pos, DEFAULT_BACKGROUND_COLOR);
	}
}

void ResetData()
{
	snakeSize = 2;
	snake_pos[0] = { 3, 2 };
	snake_pos[1] = { 2, 2 };
	snake_text[0] = snake_default_text[0];
	snake_text[1] = snake_default_text[1];
	current_last_text = 1;
	snake_dir = Direction::RIGHT;
	snake_state = State::ALIVE;
	snake_speed = 5;
	strcpy_s(name, "");
	food_state = 1;
	score = 0;
	game_time = 0;
	t1 = time(0);
	wall_size = 0;
	gate_state = 0;
	level = 1;
	process = 2;
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
	float bigfood_timer = 0;
	int h = 0, min = 0, sec = 0;
	ResetData();
	WaitPlayGame();
	GameplayUI();
	DisplayHighScoreInGame(46, 18, 0);
	GenerateWallNew();
	GenerateFood();
	DrawPixel(food_pos, food_color, 15, food_text);
	ProcessBar();
	DrawPixels(wall_pos, wall_size, wall_color);
	while (1)
	{

		DrawPixels(snake_pos, snakeSize, snake_color, 15, snake_text);
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
				if (bigfood_state == 1)
				{
					bigfood_timer += 0.01;
					if (bigfood_timer >= bigfood_lifeTime)
					{
						bigfood_state = 0;
						bigfood_timer = 0;
						GenerateBigFood();
					}
				}
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
					if (playerDatas[i].score < score || (playerDatas[i].score == score && playerDatas[i].time >= game_time))
					{
						saveName = true;
						break;
					}
				}
			}

			if (saveName)
			{
				PlayerData playerData;
				do
				{
					GoToXYPixel(46, 8);
					SetColor(0, 15);
					cout << "Enter name: ";
					ShowCursor(true);
					cin.getline(playerData.name, 4);
					rewind(stdin);
				} while (strlen(playerData.name) == 0);

				saveName = false;
				playerData.score = score;
				playerData.time = game_time;
				Save(playerData);
				ShowCursor(false);
			}
			GoToXYPixel(46, 8);
			SetColor(0, 15);
			cout << "Press any key to restart";
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
						bigfood_timer = 0;
						timer = 1;
						WaitPlayGame();
						GameplayUI();
						// DrawBorder(45, 17, 15, 15, 15, 0);
						DisplayHighScoreInGame(46, 18, 0);
						SpawnFood();
						break;
					}
				}
				Sleep(100);
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
			t1 = time(0);
			GameplayUI();
			DrawPixels(wall_pos, wall_size, wall_color);
			if (MiniGame3_state == 0)
			{
				DrawPixel(food_pos, food_color, 15, food_text);
			}
			else
				for (int i = 0; i < 2; i++)
				{
					DrawPixel(two_food_pos[i], food_color, 15, food_text);
				}
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
		if (sfx)
		{
			PlayDieSound();
		}
	}
}

void Eat()
{
	if (snake_pos[0].x == food_pos.x && snake_pos[0].y == food_pos.y && food_state == 1)
	{
		if (sfx)
		{
			PlayEatSound();
		}
		score += level * 10;
		snakeSize++;
		process++;
		ProcessBar();
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
		if (snakeSize % 9 == 0)
		{
			gate_state = 1;
			food_state = 0;
			GenerateGate();
		}
		else
		{
			SpawnFood();
		}
		if (rand() % 100 <= bigfood_ratio && bigfood_state == 0)
			// if (snakeSize % 9 == 4)
		{
			bigfood_state = 1;
			GenerateBigFood();
		}
	}
	if (snake_pos[0].x == gate_pos.x && snake_pos[0].y == gate_pos.y && gate_state == 1)
	{
		ToTheNextLevel();
	}
	if (bigfood_state == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (snake_pos[0].x == bigfood_pos[i].x && snake_pos[0].y == bigfood_pos[i].y)
			{
				if (sfx)
				{
					PlayEatSound();
				}
				score += level * 30;
				bigfood_state = 0;
				GenerateBigFood();
				break;
			}
		}
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
	//(level - 1) % 7 + 1
	switch ((level - 1) % 7 + 1) // Do not change this line
	// 6: how many levels
	// 1 level -> 1
	// 2 levels -> 2
	// x levels -> x
	{
	case 1: 
		DrawLevel1();
		break;
	case 2:
		DrawLevel2();
		break;
	case 3:
		DrawLevel3();
		break;
	case 4:
		DrawLevel4();
		break;
	case 5:
		DrawLevel5();
		break;
	case 6:
		DrawLevel6();
		break;
	case 7:
		DrawLevel7();
		break;
	}
}
void SetGateCollider() // Do not change this function
{
	switch (gate_dir)
	{
	case 0:
		gate_colliders[0] = { gate_pos.x - 1, gate_pos.y };
		gate_colliders[1] = { gate_pos.x + 1, gate_pos.y };
		gate_colliders[2] = { gate_pos.x - 1, gate_pos.y + 1 };
		gate_colliders[3] = { gate_pos.x, gate_pos.y + 1 };
		gate_colliders[4] = { gate_pos.x + 1, gate_pos.y + 1 };
		break;

	case 1:
		gate_colliders[0] = { gate_pos.x - 1, gate_pos.y - 1 };
		gate_colliders[1] = { gate_pos.x, gate_pos.y - 1 };
		gate_colliders[2] = { gate_pos.x + 1, gate_pos.y - 1 };
		gate_colliders[3] = { gate_pos.x - 1, gate_pos.y };
		gate_colliders[4] = { gate_pos.x + 1, gate_pos.y };
		break;

	case 2:
		gate_colliders[0] = { gate_pos.x, gate_pos.y - 1 };
		gate_colliders[1] = { gate_pos.x + 1, gate_pos.y - 1 };
		gate_colliders[2] = { gate_pos.x + 1, gate_pos.y };
		gate_colliders[3] = { gate_pos.x, gate_pos.y + 1 };
		gate_colliders[4] = { gate_pos.x + 1, gate_pos.y + 1 };
		break;

	case 3:
		gate_colliders[0] = { gate_pos.x - 1, gate_pos.y - 1 };
		gate_colliders[1] = { gate_pos.x, gate_pos.y - 1 };
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

void GenerateGate() // Do not change this function
{
	int x, y;
	do
	{
		x = rand() % (game_field_width - 12) + game_field_pos.x + 4;
		y = rand() % (game_field_height - 12) + game_field_pos.y + 4;
	} while (!IsValid(x, y) || !IsValid(x+1,y) || !IsValid(x+1, y+1) || !IsValid(x+1,y-1) || !IsValid(x, y-1) || !IsValid(x,y+1) || !IsValid(x-1, y-1) || !IsValid(x-1,y+1) !IsValid(x-1,y));
	gate_pos = { x, y };
	gate_dir = rand() % 4;
	SetGateCollider();
}

void ToTheNextLevel()
{
	GameplayUI();
	snake_pos[0] = { 3, 2 };
	snake_pos[1] = { 2, 2 };
	snake_dir = Direction::RIGHT;
	for (int i = 2; i < snakeSize; i++) {
		snake_pos[i] = {-1,-1};
	}
	bigfood_state = 0;
	gate_state = 0;
	level += 1;
	process = 0;
	/*for (int i = 0; i < level; i++)
	{
		GenerateWall();
	}*/
	food_state = 1;
	GenerateWallNew();
	DrawPixels(wall_pos, wall_size, wall_color);
	SpawnFood();
}	 

void ProcessBar()
{
	DrawBorder(45, 12, 29, 4, 15, 0);
	DrawBorder(75, 12, 4, 4, 15, 0);
	for (int i = 0; i < process; i++)
	{
		DrawRectangle(46 + i * 3, 13, 3, 2, 11);
	}
	if (process == 9)
	{
		DrawRectangle(76, 13, 2, 2, 11);
	}
}

void ToggleSfx()
{
	if (sfx)
	{
		sfx = false;
	}
	else
	{
		sfx = true;
	}
}

void GenerateBigFood()
{
	if (bigfood_state == 1)
	{
		int a, b;
		do
		{
			a = rand() % (game_field_width - 3) + game_field_pos.x + 1;
			b = rand() % (game_field_height - 3) + game_field_pos.y + 1;
			bigfood_pos[0] = { a, b };
			bigfood_pos[1] = { a + 1, b };
			bigfood_pos[2] = { a, b + 1 };
			bigfood_pos[3] = { a + 1, b + 1 };
			bigfood_lifeTime = (abs(bigfood_pos[0].x - snake_pos[0].x) + abs(bigfood_pos[0].y - snake_pos[0].y) + bigfood_lifetimeDelay) * 0.2f;

		} while (!IsValid(a, b) || !IsValid(a + 1, b) ||  !IsValid(a, b + 1) || !IsValid(a + 1, b + 1));
		DrawPixels(bigfood_pos, 4, bigfood_color);
	}
	else
	{
		DrawPixels(bigfood_pos, 4, game_field_color);
	}
}

void RunMiniGame1() // Maze
{
	WaitPlayGame();
	float timer = 1;
	MiniGame1ResetData();
	GameplayUI();
	GenerateMaze();
	snake_dir = Direction::STOP;
	DrawPixels(wall_pos, wall_size, 15);
	while (1)
	{

		DrawPixels(snake_pos, snakeSize, snake_color, 15, snake_text);
		GoToXYPixel(46, 2);
		SetColor(0, 15);
		cout << "Score: " << score << " ";

		if (snake_state != State::DEAD)
		{
			GameInput();
			if (snake_dir != Direction::STOP)
			{

				timer += 0.01;
				startTimer = 0;

				if (timer >= 1 / snake_speed)
				{
					timer = 0;
					ProcessDead();
					Move();
					MiniGame1Eat();
				}
			}
			else
			{
				timer = 1;
				startTimer -= 0.01;
				if (startTimer <= 0)
				{
					snake_dir = Direction::RIGHT;
				}

			}
		}
		else
		{
			GoToXYPixel(46, 8);
			SetColor(0, 15);
			cout << "Press any key to restart";
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
						// ResetData();
						MiniGame1ResetData();
						timer = 1;
						WaitPlayGame();
						GameplayUI();
						GenerateMaze();
						// SpawnFood();
						break;
					}
				}
				Sleep(100);
			}
		}
		Sleep(100);
	}
}
void GenerateMaze()
{
	// https://www.dcode.fr/maze-generator width 14 || height 21
	char mazePath[17] = "mazes\\maze_";
	char ran = rand() % 10 + 48;
	char ending[6] = "_.txt";
	ending[0] = ran;
	strcat_s(mazePath, ending);
	fstream file;
	file.open(mazePath);
	char maze[game_field_width][game_field_height];
	for (int i = 0; i < game_field_width; i++)
	{
		file >> maze[i];
		// cout << (maze[i]) <<endl;
	}
	wall_size = 0;
	for (int x = 0; x < game_field_width; x++)
	{
		for (int y = 0; y < game_field_width; y++)
		{
			if (maze[x][y] == 'X')
			{
				wall_pos[wall_size] = { x + 1, y + 1 };
				wall_size++;
			}
		}
	}
	DrawPixels(wall_pos, wall_size, 15);
	food_pos = { 42, 42 };
	DrawPixel(food_pos, food_color);
}

void MiniGame1ResetData()
{
	snakeSize = 2;
	snake_pos[0] = { 3, 2 };
	snake_pos[1] = { 2, 2 };
	snake_text[0] = snake_default_text[0];
	snake_text[1] = snake_default_text[1];
	current_last_text = 1;
	snake_dir = Direction::STOP;
	snake_state = State::ALIVE;
	snake_speed = 30;
	food_state = 1;
	score = 0;
	startTimer = 3;
}

void MiniGame1Eat() {
	if (food_state == 1 && food_pos.x == snake_pos[0].x && food_pos.y == snake_pos[0].y)
	{
		if (sfx)
		{
			PlayEatSound();
		}

		MiniGame1ResetData();
		score += 100;
		snake_dir = Direction::STOP;
		startTimer = 3;
		GameplayUI();
		GenerateMaze();
		//Reset lai map moi
	}
}

void RunMiniGame2() // Revert
{
	WaitPlayGame();
	float timer = 1;
	MiniGame2ResetData();
	GameplayUI();
	GenerateFood();
	wall_size = 0;
	DrawPixel(food_pos, food_color, 15, food_text);
	while (1)
	{

		DrawPixels(snake_pos, snakeSize, snake_color, 15, snake_text);
		GoToXYPixel(46, 2);
		SetColor(0, 15);
		cout << "SCORE: " << score;

		if (snake_state != State::DEAD)
		{
			GameInput();
			if (snake_dir != Direction::STOP)
			{

				timer += 0.01;

				if (timer >= 1 / snake_speed)
				{
					timer = 0;
					ProcessDead();
					Move();
					MiniGame2Eat();
				}
			}
			else
			{
				timer = 1;
			}
		}
		else
		{
			GoToXYPixel(46, 8);
			SetColor(0, 15);
			cout << "Press any key to restart";
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
						timer = 1;
						WaitPlayGame();
						GameplayUI();
						SpawnFood();
						break;
					}
				}
				Sleep(100);
			}
		}
		Sleep(1000 / fps);
	}
}

void MiniGame2ResetData()
{
	snakeSize = 2;
	snake_pos[0] = { 3, 2 };
	snake_pos[1] = { 2, 2 };
	snake_text[0] = snake_default_text[0];
	snake_text[1] = snake_default_text[1];
	current_last_text = 1;
	snake_dir = Direction::RIGHT;
	snake_state = State::ALIVE;
	snake_speed = 5;
	food_state = 1;
	score = 0;
}

void MiniGame2Eat()
{
	if (food_state == 1 && food_pos.x == snake_pos[0].x && food_pos.y == snake_pos[0].y)
	{
		if (sfx)
		{
			PlayEatSound();
		}
		score += 10;
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
		for (int i = 0; i < snakeSize / 2; i++)
		{
			POINT temp = snake_pos[i];
			snake_pos[i] = snake_pos[snakeSize - 1 - i];
			snake_pos[snakeSize - 1 - i] = temp;
		}
		if (snake_pos[0].x == snake_pos[1].x + 1)
		{
			snake_dir = Direction::RIGHT;
		}
		else if (snake_pos[0].x == snake_pos[1].x - 1)
		{
			snake_dir = Direction::LEFT;
		}
		else if (snake_pos[0].y == snake_pos[1].y + 1)
		{
			snake_dir = Direction::DOWN;
		}
		else
		{
			snake_dir = Direction::UP;
		}
		SpawnFood();
	}
}
void RunMiniGame3() // Teleport
{
	// WaitPlayGame();
	float timer = 1;
	MiniGame2ResetData();
	GameplayUI();
	Generate2Food();
	wall_size = 0;
	DrawPixel(two_food_pos[0], food_color, 15, food_text);
	DrawPixel(two_food_pos[1], food_color, 15, food_text);
	snake_dir = Direction::STOP;
	while (1)
	{
		DrawPixels(snake_pos, snakeSize, snake_color, 15, snake_text);
		GoToXYPixel(46, 2);
		SetColor(0, 15);
		cout << "SCORE: " << score;

		if (snake_state != State::DEAD)
		{
			MiniGame3_state = 1;
			GameInput();
			if (snake_dir != Direction::STOP)
			{
				timer += 0.01;
				if (timer >= 1 / snake_speed)
				{
					timer = 0;
					ProcessDead();
					Move();
					MiniGame3Eat();
				}
			}
			else
			{
				timer = 1;
			}
		}
		else
		{
			GoToXYPixel(46, 8);
			SetColor(0, 15);
			cout << "Press any key to restart";
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
						timer = 1;
						WaitPlayGame();
						GameplayUI();
						SpawnTwoFood();
						break;
					}
				}
				Sleep(100);
			}
		}
		Sleep(1000 / fps);
	}
}
void Generate2Food()
{
	int x1, x0, y0, y1;
	do
	{
		do
		{
			x0 = rand() % (game_field_width - 2) + game_field_pos.x + 1;
			y0 = rand() % (game_field_height - 2) + game_field_pos.y + 1;
			x1 = rand() % (game_field_width - 2) + game_field_pos.x + 1;
			y1 = rand() % (game_field_height - 2) + game_field_pos.y + 1;
		} while (!IsValid(x0, y0) || !IsValid(x1, y1));
	} while (x0 == x1 && y0 == y1);
	two_food_pos[0].x = x0;
	two_food_pos[1].x = x1;
	two_food_pos[0].y = y0;
	two_food_pos[1].y = y1;
	if (current_last_text >= textSize - 1)
	{
		food_text = snake_default_text[0];
	}
	else
	{
		food_text = snake_default_text[current_last_text + 1];
	}
}
void MiniGame3Eat()
{
	if (food_state == 1)
	{
		if ((snake_pos[0].x == two_food_pos[0].x && snake_pos[0].y == two_food_pos[0].y) || (snake_pos[0].x == two_food_pos[1].x && snake_pos[0].y == two_food_pos[1].y))
		{
			if (sfx)
			{
				PlayEatSound();
			}
			score += 10;
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
			if (snake_pos[0].x == two_food_pos[0].x && snake_pos[0].y == two_food_pos[0].y)
			{
				snake_pos[0] = two_food_pos[1];
			}
			else if (snake_pos[0].x == two_food_pos[1].x && snake_pos[0].y == two_food_pos[1].y)
			{
				snake_pos[0] = two_food_pos[0];
			}
			SpawnTwoFood();
		}
	}
}
void SpawnTwoFood()
{
	DrawPixel(two_food_pos[0], game_field_color);
	DrawPixel(two_food_pos[1], game_field_color);
	Generate2Food();
	DrawPixel(two_food_pos[0], food_color, 15, food_text);
	DrawPixel(two_food_pos[1], food_color, 15, food_text);
}


void DrawLevel1() {
	wall_size = 0;
}
void DrawLevel2() {
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
}
void DrawLevel3() {
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
}
void DrawLevel4() {
	wall_size = 90;

	// Outside
	int i = 0;
	for (int temp1 = 8, temp2 = 8; i < (wall_size - 30) / 4; i++)
	{
		wall_pos[i] = { temp1, temp2 };
		wall_pos[90 - i - 1] = { 44 - temp1, 44 - temp2 };
		i++;
		wall_pos[i] = { 44 - temp1, temp2 };
		wall_pos[wall_size - i - 1] = { temp1, 44 - temp2 };
		if (i < 7)
			temp1++;
		else
		{
			temp1 = 8;
			temp2++;
		}
	}

	// Inside
	for (int temp1 = 13, temp2 = 16; i < (wall_size / 2); i++)
	{
		wall_pos[i] = { temp1, temp2 };
		wall_pos[90 - i - 1] = { 44 - temp1, 44 - temp2 };
		i++;
		wall_pos[i] = { 44 - temp1, temp2 };
		wall_pos[wall_size - i - 1] = { temp1, 44 - temp2 };
		if (i < (wall_size / 2) - 5)
			temp1++;
		else
		{
			temp1 = 13;
			temp2++;
		}
	}

}
void DrawLevel5() {
	wall_size = 71;
	for (int i = 0; i < 35; i++)
	{
		wall_pos[i] = { 5 + i,5 + i };
	}
	for (int i = 0; i < 35; i++)
	{
		wall_pos[35 + i] = { 40 - i,5 + i };
	}
}
void DrawLevel6() {
	//wall_size = 861;
	//int Mark = 11;
	//int f = 0;
	//for (int g = 12; g <= 32; g++)
	//{
	//	for (int i = 2; i <= 42; i++)
	//	{
	//		if ((i != Mark) && (i != Mark + 1))
	//		{
	//			wall_pos[f] = { g,i };
	//			f++;
	//		}
	//	}
	//	Mark++;
	//}

	wall_size = 1;
	int size = 0;
	int temp = 1;
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 18 - temp*2; k++)
		{
			wall_pos[size++] = { 13 + k + temp,6 + i };
		}
		temp++;
	}
	temp = 1;
	for (int i = 8; i >= 0; i--)
	{
		for (int k = 0; k < 18 - temp * 2; k++)
		{
			wall_pos[size++] = { 13 + k + temp, 36-6 + i };
		}
		temp++;
	}

	temp = 1;
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 18 - temp * 2; k++)
		{
			wall_pos[size++] = {6 + i ,13 + k + temp };
		}
		temp++;
	}
	temp = 1;
	for (int i = 8; i >= 0; i--)
	{
		for (int k = 0; k < 18 - temp * 2; k++)
		{
			wall_pos[size++] = {36 - 6 + i, 13 + k + temp};
		}
		temp++;
	}

	for (int i = 0; i < 10; i++)
	{
		wall_pos[size++] = {6+i, 10+i };
	}
	for (int i = 0; i < 10; i++)
	{
		wall_pos[size++] = { 10 + i, 6 + i };
	}
	for (int i = 0; i < 10; i++)
	{
		wall_pos[size++] = {42-7- 6 + i,42 - 7 - 11 + i };
	}
	for (int i = 0; i < 10; i++)
	{
		wall_pos[size++] = { 42-7- 11 + i,42 - 7 - 6 + i };
	}
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			wall_pos[size++] = { 12+i, 2+k};
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			wall_pos[size++] = { 12 + 18 + i, 2 + k };
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			wall_pos[size++] = { 13 + i, 41 + k };
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			wall_pos[size++] = { 13+ 18 + i, 41 + k };
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			wall_pos[size++] = { 40 + i, 2 + k };
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			wall_pos[size++] = { 2 + i, 40 + k };
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			wall_pos[size++] = { 13 + i, 25 + k };
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			wall_pos[size++] = { 29 + i, 17 + k };
		}
	}

	wall_pos[size++] = { 4,3 };
	wall_pos[size++] = { 3,4 };
	wall_pos[size++] = { 41,40 };
	wall_pos[size++] = { 40,41 };
	wall_size = size;
}
void DrawLevel7() {
	int size = 0;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			wall_pos[size++] = { 2 + x, 2 + y };
		}
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			wall_pos[size++] = { 2 + x, 15 + y };
		}
	}
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			wall_pos[size++] = { 2 + x, 25 + y };
		}
	}
	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 17; y++)
		{
			wall_pos[size++] = { 2 + x, 26 + y };
		}
	}

	for (int x = 0; x < 42; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			wall_pos[size++] = { 2 + x, 42 + y };
		}
	}
	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			wall_pos[size++] = { 2 + x, 41 + y };
		}
	}
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			wall_pos[size++] = { 32 + x, 40 + y };
		}
	}
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			wall_pos[size++] = { 35 + x, 33 + y };
		}
	}
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			wall_pos[size++] = { 13 + x, 2 + y };
		}
	}
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			wall_pos[size++] = { 16 + x, 4 + y };
		}
	}
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			wall_pos[size++] = { 31 + x, 5 + y };
		}
	}
	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 19; y++)
		{
			wall_pos[size++] = { 42 + x, 2 + y };
		}
	}
	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 14; y++)
		{
			wall_pos[size++] = { 41 + x, 7 + y };
		}
	}
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			wall_pos[size++] = { 7 + x, 15 + y };
		}
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			wall_pos[size++] = { 7 + x, 19 + y };
		}
	}
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			wall_pos[size++] = { 9 + x, 21 + y };
		}
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			wall_pos[size++] = { 17 + x, 13 + y };
		}
	}
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			wall_pos[size++] = { 23 + x, 11 + y };
		}
	}
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			wall_pos[size++] = { 27 + x, 12 + y };
		}
	}
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y <11; y++)
		{
			wall_pos[size++] = { 24 + x, 15 + y };
		}
	}
	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			wall_pos[size++] = { 21 + x, 15 + y };
		}
	}
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			wall_pos[size++] = { 22 + x, 18 + y };
		}
	}

	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			wall_pos[size++] = { 15 + x, 32 + y };
		}
	}
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			wall_pos[size++] = { 11 + x, 25 + y };
		}
	}
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			wall_pos[size++] = { 11 + x, 25 + y };
		}
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			wall_pos[size++] = { 14 + x, 21 + y };
		}
	}
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			wall_pos[size++] = { 27 + x, 23 + y };
		}
	}
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			wall_pos[size++] = { 32 + x, 25 + y };
		}
	}
	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			wall_pos[size++] = { 37 + x, 25 + y };
		}
	}
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			wall_pos[size++] = { 40 + x, 25 + y };
		}
	}
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			wall_pos[size++] = { 38 + x, 27 + y };
		}
	}
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			wall_pos[size++] = { 15 + x, 30 + y };
		}
	}
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			wall_pos[size++] = { 10 + x, 6 + y };
		}
	}
	wall_pos[size++] = { 3, 40 };
	wall_pos[size++] = { 3, 30 };
	wall_pos[size++] = { 4, 30 };
	wall_pos[size++] = { 17, 14 };

	wall_size = size;
}