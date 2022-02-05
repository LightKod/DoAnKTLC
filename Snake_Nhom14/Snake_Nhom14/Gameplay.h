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
static int snake_color;
static int snakeSize;
static POINT food_pos;
static int food_color = 12;
static Direction snake_dir;
static State snake_state;
static float snake_speed;
static int score;

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
bool IsHitTheWall();
bool IsHitYourself();
void ProcessDead();
void Eat(POINT last_pos);