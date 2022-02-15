#include "SaveLoad.h"
#include "Graphic.h"
using namespace std;
#include <iostream>
#include <fstream>

void Save(PlayerData newData)
{
	fstream file;
	file.open(savePath);
	if (dataSize < 10) {
		dataSize++;
	}
	for (int i = 0; i < dataSize; i++)
	{
		if (playerDatas[i].score <= newData.score)
		{
			// day xuong
			for (int k = i; k < dataSize - 1; k++)
			{
				playerDatas[i + 1] = playerDatas[i];
			}
			playerDatas[i] = newData;
			break;
		}
	}
	file << dataSize << endl;
	for (int i = 0; i < dataSize; i++)
	{
		file << playerDatas[i].name << " " << playerDatas[i].score << endl;
	}
}

void Load()
{
	fstream file;
	file.open(savePath);
	file >> dataSize;
	for (int i = 0; i < 10; i++)
	{
		file >> playerDatas[i].name;
		file >> playerDatas[i].score;
	}
}

void DisplayScore(int x, int y)
{
	//HiScoreText
	DrawRectangle(x, y, 1, 3,15);
	DrawRectangle(x, y+1, 3, 1,15);
	DrawRectangle(x+2, y, 1, 3,15);
	//DrawRectangle(x+4, y, 1, 1,7);
	DrawRectangle(x+4, y+1, 1, 2,15);
	for (int i = 0; i < dataSize; i++)
	{
		GoToXYPixel(x, y + i+4);
		printf("%s ----- %d", playerDatas[i].name, playerDatas[i].score);
	}

	DrawBorder(x-2, y-1, 10, 15, 15);
}

void TestSaveLoad()
{
	PlayerData p1;
	strcpy_s(p1.name, "AAA");
	p1.score = 10;
	Save(p1);
	PlayerData p2;
	strcpy_s(p2.name, "BBB");
	p2.score = 100;
	Save(p2);
	//DisplayScore();
}