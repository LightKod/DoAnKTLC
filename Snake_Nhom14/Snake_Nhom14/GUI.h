#include <Windows.h>

static bool playingGame = true;
static bool howtoplay = true;
static bool highscore = true;
static bool exitGame = false;
static bool optionMenu = false;
static bool exitStartMenu = false;
static POINT cursor = { 0, 0 };

void OptionMenu();
void GUI();
void GameplayUI();
void ClearScreen();
void StartMenu();
void DisplayInstructions();
