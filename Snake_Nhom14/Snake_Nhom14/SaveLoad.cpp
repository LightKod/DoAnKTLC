#include "SaveLoad.h"
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

void DisplayScore()
{
	for (int i = 0; i < 10; i++)
	{
		printf("%s + %d\n", playerDatas[i].name, playerDatas[i].score);
	}
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
	DisplayScore();
}