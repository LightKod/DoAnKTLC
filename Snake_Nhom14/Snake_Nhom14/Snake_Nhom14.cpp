// Snake_Nhom14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Graphic.h"
#include "Gameplay.h"

using namespace std;

int main()
{
	SetUp();
	ResetData();
	//Press any key to change position
	TestFoodSpawn();
	cout << "Hello snake\n";
}