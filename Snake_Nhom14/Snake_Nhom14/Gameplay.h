#pragma once
#include <Windows.h>

static POINT snake[100];
static int snakeSize = 0;
static POINT food;

bool IsValid(int x, int y);
void GenerateFood();
void TestFoodSpawn();

