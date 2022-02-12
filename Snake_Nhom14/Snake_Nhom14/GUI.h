#include <Windows.h>

static bool playingGame = true;
static bool howtoplay = false;
static bool highscore = false;
static bool exitGame = false;
static bool exitStartMenu = false;
static POINT cursor = { 59, 19 };

void DisplaySNAKE();
void DisplayGAME();
void DisplaySNAKEIMG();
void MenuBG();
void GUI();
void GameplayUI();
void ClearScreen();
void StartMenu();
void DisplayInstructions();
