#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

void OpenMusic()
{
	mciSendString(TEXT("open \"music.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
}

void PlayMusic()
{
	mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
}

void PauseMusic()
{
	mciSendString(TEXT("pause mp3"), NULL, 0, NULL);
}

void CloseMusic()
{
	mciSendString(TEXT("close mp3"), NULL, 0, NULL);
}