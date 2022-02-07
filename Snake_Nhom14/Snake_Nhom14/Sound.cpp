#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

void PlayMusic() {
	mciSendString(TEXT("open \"audio.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
}