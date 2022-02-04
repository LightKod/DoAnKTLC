#include "Gameplay.h"
#include "Graphic.h"
#include <iostream>

bool IsValid(int x, int y) {
    for (int i = 0; i < SIZE_SNAKE; i++) {
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
        DrawPixel(food, 0, 7, 'X');
        Sleep(1000);
        DrawPixel(food, 0, 0, 'Y');

    }
}
void Eat() {}

// Snake's movement
void MoveRight() {
    if (snake[SIZE_SNAKE - 1].x - 1 == WIDTH_CONSOLE)
    {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x++;
    }
}
void MoveLeft() {
    if (snake[SIZE_SNAKE - 1].x - 1 == WIDTH_CONSOLE)
    {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x++;
    }
}
void MoveUp() {
    if (snake[SIZE_SNAKE - 1].y - 1 == 0)
    {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y--;
    }
}
void MoveDown() {
    if (snake[SIZE_SNAKE - 1].y - 1 == HEIGH_CONSOLE)
    {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y--;
    }
}
void ThreadFunc()
{
    while (1) {
        if (STATE == 1) // 1: Snake is alive
        {
            DrawSnakeAndFood("");
            switch (MOVING) {
            case 'A': {
                MoveLeft();
                break;
            }
            case 'D': {
                MoveRight();
                break;
            }
            case 'S': {
                MoveDown();
                break;
            }
            case 'W': {
                MoveUp();
                break;
            }
            }
            DrawSnakeAndFood("0");
            Sleep(1000 / SPEED); //Sleep functions
        }
    }
}
void ProcessDead()
{
    STATE = 0;
    GoToXY(0, HEIGH_CONSOLE + 2);
    printf("Dead, type y to continue");
}
