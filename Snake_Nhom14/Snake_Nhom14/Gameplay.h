#pragma once
#include <Windows.h>
#include "Graphic.h"

static struct POINT
{
	int x;
	int y;
};
POINT snake[100], food[4];
static int SIZE_SNAKE = 0; 
int CHAR_LOCK; //used to determine the direction my snake cannot move
int MOVING; //used to determine the direction my snake moves
static int SPEED; //snake's speed
int HEIGH_CONSOLE, WIDTH_CONSOLE; //height and width of console-screen
int FOOD_INDEX; //current food-index
int STATE; //State of snake: dead or alive

bool IsValid(int x, int y);
void GenerateFood();
void TestFoodSpawn();
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void ThreadFunc();
void ProcessDead();
void Eat();
