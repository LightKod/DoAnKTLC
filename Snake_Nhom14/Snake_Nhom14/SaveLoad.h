#pragma once
#define savePath "hiscore.txt"
struct PlayerData {
	char name[4];
	unsigned long score;
};
static PlayerData playerDatas[10];
void Save(PlayerData newData);
void Load();
void DisplayScore();
void TestSaveLoad();

