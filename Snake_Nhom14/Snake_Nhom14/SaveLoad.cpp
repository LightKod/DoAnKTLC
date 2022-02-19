#include "SaveLoad.h"
#include "Graphic.h"
using namespace std;
#include <iostream>
#include <fstream>

void Save(PlayerData newData)
{
	fstream file;
	file.open(savePath);

	for (int i = 0; i < dataSize; i++)
	{
		if (playerDatas[i].score < newData.score || (playerDatas[i].time > newData.time && playerDatas[i].score == newData.score))
		{
			for (int j = i; j < dataSize - 1; j++)
			{
				playerDatas[j + 1] = playerDatas[j];
			}
			playerDatas[i] = newData;
			if (dataSize < 10)
			{
				dataSize++;
			}
			break;
		}
		else if (i == dataSize - 1 && dataSize < 10)
		{
			dataSize++;
			playerDatas[dataSize - 1] = newData;
			break;
		}
	}
	if (dataSize == 0)
	{
		playerDatas[0] = newData;
		dataSize++;
	}

	file << dataSize << endl;
	for (int i = 0; i < dataSize; i++)
	{
		file << playerDatas[i].name << " " << playerDatas[i].score << " " << playerDatas[i].time << endl;
	}
	file.close();
}

void SavePlayer(char name[], int score, int time)
{
	fstream file;
	file.open(savePath);

	for (int i = 0; i < dataSize; i++)
	{
		if (playerDatas[i].score < score || (playerDatas[i].time > time && playerDatas[i].score == score))
		{
			for (int j = i; j < dataSize - 1; j++)
			{
				playerDatas[j + 1] = playerDatas[j];
			}
			strcpy_s(playerDatas[i].name, name);
			playerDatas[i].score = score;
			playerDatas[i].time = time;
			if (dataSize < 10)
			{
				dataSize++;
			}
			break;
		}
		else if (i == dataSize - 1 && dataSize < 10)
		{
			dataSize++;
			strcpy_s(playerDatas[dataSize - 1].name, name);
			playerDatas[dataSize - 1].score = score;
			playerDatas[dataSize - 1].time = time;
			break;
		}
	}
	if (dataSize == 0)
	{
		dataSize++;
		strcpy_s(playerDatas[dataSize - 1].name, name);
		playerDatas[dataSize - 1].score = score;
		playerDatas[dataSize - 1].time = time;
	}

	file << dataSize << endl;
	for (int i = 0; i < dataSize; i++)
	{
		file << playerDatas[i].name << " " << playerDatas[i].score << " " << playerDatas[i].time << endl;
	}
	file.close();
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
		file >> playerDatas[i].time;
	}
	file.close();
}

void DisplayScore(int x, int y)
{
	// HiScoreText
	DrawRectangle(x, y, 1, 3, 15);
	DrawRectangle(x, y + 1, 3, 1, 15);
	DrawRectangle(x + 2, y, 1, 3, 15);
	// DrawRectangle(x+4, y, 1, 1,7);
	DrawRectangle(x + 4, y + 1, 1, 2, 15);
	for (int i = 0; i < dataSize; i++)
	{
		GoToXYPixel(x, y + i + 4);
		printf("%s ----- %d --- %d", playerDatas[i].name, playerDatas[i].score, playerDatas[i].time);
	}

	DrawBorder(x - 2, y - 1, 10, 15, 15);
}

void DisplayHighScoreInGame()
{
	GoToXYPixel(46, 18);
	SetColor(0, 15);
	printf("                            HIGHSCORE");
	GoToXYPixel(46, 19);
	printf("   | name |  score | time");
	for (int i = 0; i < dataSize; i++)
	{
		GoToXYPixel(46, 20 + i);
		printf("%2d | %4s | %6d | %d", i + 1, playerDatas[i].name, playerDatas[i].score, playerDatas[i].time);
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
	// DisplayScore();
}