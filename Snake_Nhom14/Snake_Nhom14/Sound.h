#include <Windows.h>
#include <mmsystem.h>

static bool music_toggle = true;
static bool sfx_toggle = true;

void OpenSound();
void CloseSound();
void OpenMusic();
void PlayMusic();
void PauseMusic();
void StopMusic();
void CloseMusic();
void OpenKey();
void PlayKey();
void StopKey();
void CloseKey();
void OpenEatSound();
void PlayEatSound();
void CloseEatSound();