#include "Gameplay.h"
#include "Graphic.h"
#include <iostream>


bool IsValid(int x, int y) {
	for (int i = 0; i < snakeSize; i++) {
		if (snake[i].x == x && snake[i].y == y) {
			return false;
		}
	}
	return true;
}
void GenerateFood() {
	int x, y;
	srand(time(NULL));
	do {
		x = rand() % (SCREEN_WIDTH - 1) + 1;
		y = rand() % (SCREEN_HEIGHT - 1) + 1;
	} while (!IsValid(x, y));
	food.x = x;
	food.y = y;
}

void TestFoodSpawn() {
	while (true) {
		GenerateFood();
		DrawPixel(food, 10, 7, 'X');
		Sleep(1000);
		DrawPixel(food, DEFAULT_BACKGROUND_COLOR);
	}
}
