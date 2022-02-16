#pragma once
#define savePath "hiscore.txt"
struct PlayerData
{
	char name[4];
	int score;
	int time;
};
static int dataSize;
static PlayerData playerDatas[11];
void Save(PlayerData newData);
void SavePlayer(char name[], int score, int time);
void Load();
void DisplayScore(int x, int y);
void DisplayHighScoreInGame();
void TestSaveLoad();
