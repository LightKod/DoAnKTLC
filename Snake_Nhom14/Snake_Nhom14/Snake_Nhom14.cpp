// Snake_Nhom14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include "Graphic.h"
#include "Gameplay.h"
#include "GUI.h"
#include "Sound.h"
#pragma comment(lib, "Winmm.lib")

using namespace std;

int main()
{
	SetUp();
	//  TestFoodSpawn();
	TestSnakeMove();
	GoToXYPixel(0, 0);
	cout << "Hello snake\n";
	system("pause");
}