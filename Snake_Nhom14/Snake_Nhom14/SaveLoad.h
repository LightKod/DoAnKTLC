#pragma once
#define savePath "hiscore.txt"
struct PlayerData {
	char name[4];
	unsigned long score;
};
static int dataSize;
static PlayerData playerDatas[11];
void Save(PlayerData newData);
void Load();
void DisplayScore();
void TestSaveLoad();

