#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

void OpenSound()
{
	OpenMusic();
	OpenKey();
	OpenEatSound();
}

void CloseSound()
{
	CloseMusic();
	CloseKey();
	CloseEatSound();
}

void OpenMusic()
{
	mciSendString(TEXT("open \"music.mp3\" type mpegvideo alias music"), NULL, 0, NULL);
}

void PlayMusic()
{
	mciSendString(TEXT("play music repeat"), NULL, 0, NULL);
}

void PauseMusic()
{
	mciSendString(TEXT("pause music"), NULL, 0, NULL);
}

void CloseMusic()
{
	mciSendString(TEXT("close music"), NULL, 0, NULL);
}

void OpenKey()
{
	mciSendString(TEXT("open \"key.mp3\" type mpegvideo alias key"), NULL, 0, NULL);
}

void PlayKey()
{
	mciSendString(TEXT("play key from 0"), NULL, 0, NULL);
}

void CloseKey()
{
	mciSendString(TEXT("close key"), NULL, 0, NULL);
}

void OpenEatSound()
{
	mciSendString(TEXT("open \"eat.mp3\" type mpegvideo alias eat"), NULL, 0, NULL);
}

void PlayEatSound()
{
	mciSendString(TEXT("play eat from 0"), NULL, 0, NULL);
}

void CloseEatSound()
{
	mciSendString(TEXT("close eat"), NULL, 0, NULL);
}
