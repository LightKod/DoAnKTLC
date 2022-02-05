#pragma once
#include <Windows.h>

enum class Direction // direction of snake
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class State // state of snake
{
	DEAD,
	ALIVE
};

static POINT snake_pos[100];
static int snake_color = 15;
static int snakeSize;
static POINT food;
static Direction snake_dir;
static State snake_state;
static float snake_speed;

bool IsValid(int x, int y);
void GenerateFood();
void TestFoodSpawn();
void ResetData(); // Reset game data
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void TestSnakeMove();
void GameInput();
void Move();