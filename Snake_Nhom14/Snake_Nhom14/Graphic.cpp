#include <Windows.h>
#include <iostream>
#include "Graphic.h"

using namespace std;

void ShowCursor(bool cursor_visibility)
{
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 10;
    cursor_info.bVisible = cursor_visibility;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void DisableSelection()
{
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ~ENABLE_QUICK_EDIT_MODE);
}

void FixWindowSize()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableControlButton(bool close, bool min, bool max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void SetUp()
{
    system("MODE 160, 45");
    ShowCursor(0);
    DisableSelection();
    SetConsoleTitle(TEXT("Snake project"));
    SetConsoleOutputCP(65001);
    FixWindowSize();
    DisableControlButton(0, 0, 1);
}

void GoToXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GoToXYPixel(int x, int y)
{
    GoToXY(x * PIXEL_WIDTH, y * PIXEL_HEIGHT);
}

void SetColor(int bg_color, int text_color)
{
    int color_mode = bg_color * 16 + text_color;
    /*
    0 = black
    1 = blue
    2 = green
    3 = aqua
    4 = red
    5 = purple
    6 = yellow
    7 = white
    8 = gray
    9 = light blue
    10 = light green
    11 = light aqua
    12 = light red
    13 = light purple
    14 = light yellow
    15 = bright white
    */
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_mode);
}