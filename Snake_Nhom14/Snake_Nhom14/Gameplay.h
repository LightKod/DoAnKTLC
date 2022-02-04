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
static int snakeSize;
static POINT food;
static Direction snake_dir;
static State snake_state;

bool IsValid(int x, int y);
void GenerateFood();
void TestFoodSpawn();
void ResetData(); // Reset game data