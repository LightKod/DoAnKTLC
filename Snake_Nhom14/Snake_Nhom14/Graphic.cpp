#include <Windows.h>
#include <iostream>
#include <time.h>
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
	SetConsoleTitle(TEXT("Snake project"));
	SetConsoleOutputCP(65001);
	FixWindowSize();
	DisableControlButton(0, 0, 1);
	DisableSelection();
	ShowCursor(false);
	srand(time(NULL));
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

void GoToXYPixel(POINT pos)
{
	GoToXY(pos.x * PIXEL_WIDTH, pos.y * PIXEL_HEIGHT);
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

void DrawPixel(int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < PIXEL_HEIGHT; j++)
		{
			GoToXY(x * PIXEL_WIDTH + i, y * PIXEL_HEIGHT + j);
			SetColor(color, DEFAULT_TEXT_COLOR);
			cout << " ";
			SetColor(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
		}
	}
}

void DrawPixel(POINT pos, int color)
{
	if (pos.x < 0 || pos.x >= SCREEN_WIDTH || pos.y < 0 || pos.y >= SCREEN_HEIGHT)
	{
		return;
	}
	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < PIXEL_HEIGHT; j++)
		{
			GoToXY(pos.x * PIXEL_WIDTH + i, pos.y * PIXEL_HEIGHT + j);
			SetColor(color, DEFAULT_TEXT_COLOR);
			cout << " ";
			SetColor(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
		}
	}
}

void DrawPixel(int x, int y, int bg_color, int text_color, char text)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < PIXEL_HEIGHT; j++)
		{
			GoToXY(x * PIXEL_WIDTH + i, y * PIXEL_HEIGHT + j);
			SetColor(bg_color, text_color);
			if (i == 0 && j == 0)
			{
				cout << text;
			}
			else
			{
				cout << " ";
			}
			SetColor(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
		}
	}
}

void DrawPixel(POINT pos, int bg_color, int text_color, char text)
{
	if (pos.x < 0 || pos.x >= SCREEN_WIDTH || pos.y < 0 || pos.y >= SCREEN_HEIGHT)
	{
		return;
	}
	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < PIXEL_HEIGHT; j++)
		{
			GoToXY(pos.x * PIXEL_WIDTH + i, pos.y * PIXEL_HEIGHT + j);
			SetColor(bg_color, text_color);
			if (i == 0 && j == 0)
			{
				cout << text;
			}
			else
			{
				cout << " ";
			}
			SetColor(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
		}
	}
}

void DrawPixel(int x, int y, int bg_color, int text_color, char text[], int size)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	int t = 0;
	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < PIXEL_HEIGHT; j++)
		{
			GoToXY(x * PIXEL_WIDTH + i, y * PIXEL_HEIGHT + j);
			SetColor(bg_color, text_color);
			cout << text[t];
			SetColor(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
			t++;
			if (t >= size)
			{
				t = 0;
			}
		}
	}
}

void DrawPixel(int x, int y, int bg_color, int text_color, const char text[], int size)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	int t = 0;
	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		for (int j = 0; j < PIXEL_HEIGHT; j++)
		{
			GoToXY(x * PIXEL_WIDTH + i, y * PIXEL_HEIGHT + j);
			SetColor(bg_color, text_color);
			cout << text[t];
			SetColor(DEFAULT_BACKGROUND_COLOR, DEFAULT_TEXT_COLOR);
			t++;
			if (t >= size)
			{
				t = 0;
			}
		}
	}
}

void DrawRectangle(int x, int y, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			DrawPixel(x + i, y + j, color);
		}
	}
}

void DrawRectangle(POINT pos, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			DrawPixel(pos.x + i, pos.y + j, color);
		}
	}
}

void DrawBorder(int x, int y, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				DrawPixel(x + i, y + j, color);
			}
		}
	}
}

void DrawBorder(POINT pos, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				DrawPixel(pos.x + i, pos.y + j, color);
			}
		}
	}
}

void DrawBorder(int x, int y, int width, int height, int border_color, int inner_color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				DrawPixel(x + i, y + j, border_color);
			}
			else
			{
				DrawPixel(x + i, y + j, inner_color);
			}
		}
	}
}

void DrawBorder(POINT pos, int width, int height, int border_color, int inner_color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				DrawPixel(pos.x + i, pos.y + j, border_color);
			}
			else
			{
				DrawPixel(pos.x + i, pos.y + j, inner_color);
			}
		}
	}
}

void DrawBorderWithThickness(int x, int y, int width, int height, int thickness, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((i >= 0 && i < thickness) || (i <= width - 1 && i > width - 1 - thickness) || (j >= 0 && j < thickness) || (j <= height - 1 && j > height - 1 - thickness))
			{
				DrawPixel(x + i, y + j, color);
			}
		}
	}
}

void DrawBorderWithThickness(POINT pos, int width, int height, int thickness, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((i >= 0 && i < thickness) || (i <= width - 1 && i > width - 1 - thickness) || (j >= 0 && j < thickness) || (j <= height - 1 && j > height - 1 - thickness))
			{
				DrawPixel(pos.x + i, pos.y + j, color);
			}
		}
	}
}

void DrawBorderWithThickness(int x, int y, int width, int height, int thickness, int border_color, int inner_color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((i >= 0 && i < thickness) || (i <= width - 1 && i > width - 1 - thickness) || (j >= 0 && j < thickness) || (j <= height - 1 && j > height - 1 - thickness))
			{
				DrawPixel(x + i, y + j, border_color);
			}
			else
			{
				DrawPixel(x + i, y + j, inner_color);
			}
		}
	}
}

void DrawBorderWithThickness(POINT pos, int width, int height, int thickness, int border_color, int inner_color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((i >= 0 && i < thickness) || (i <= width - 1 && i > width - 1 - thickness) || (j >= 0 && j < thickness) || (j <= height - 1 && j > height - 1 - thickness))
			{
				DrawPixel(pos.x + i, pos.y + j, border_color);
			}
			else
			{
				DrawPixel(pos.x + i, pos.y + j, inner_color);
			}
		}
	}
}

void DrawPixels(POINT pos[], int size, int color)
{
	for (int i = 0; i < size; i++)
	{
		DrawPixel(pos[i], color);
	}
}

void DrawPixels(POINT pos[], int size, int color[])
{
	for (int i = 0; i < size; i++)
	{
		DrawPixel(pos[i], color[i]);
	}
}

void DrawPixels(POINT pos[], int size, int bg_color, int text_color, char text)
{
	for (int i = 0; i < size; i++)
	{
		DrawPixel(pos[i], bg_color, text_color, text);
	}
}

void DrawPixels(POINT pos[], int size, int bg_color, int text_color, char text[])
{
	for (int i = 0; i < size; i++)
	{
		DrawPixel(pos[i], bg_color, text_color, text[i]);
	}
}

void DrawPixels(POINT pos[], int size, int bg_color[], int text_color[], char text)
{
	for (int i = 0; i < size; i++)
	{
		DrawPixel(pos[i], bg_color[i], text_color[i], text);
	}
}

void DrawPixels(POINT pos[], int size, int bg_color[], int text_color[], char text[])
{
	for (int i = 0; i < size; i++)
	{
		DrawPixel(pos[i], bg_color[i], text_color[i], text[i]);
	}
}

void DrawGate(int x, int y, int color, int direction)
{
	// 0: up
	// 1: down
	// 2: left
	// 3: right
	switch (direction)
	{
	case 0:
		DrawPixel(x - 1, y, color);
		DrawPixel(x + 1, y, color);
		DrawPixel(x - 1, y + 1, color);
		DrawPixel(x, y + 1, color);
		DrawPixel(x + 1, y + 1, color);
		break;

	case 1:
		DrawPixel(x, y - 1, color);
		DrawPixel(x - 1, y - 1, color);
		DrawPixel(x + 1, y - 1, color);
		DrawPixel(x + 1, y, color);
		DrawPixel(x - 1, y, color);
		break;

	case 2:
		DrawPixel(x + 1, y, color);
		DrawPixel(x + 1, y - 1, color);
		DrawPixel(x + 1, y + 1, color);
		DrawPixel(x, y - 1, color);
		DrawPixel(x, y + 1, color);
		break;

	case 3:
		DrawPixel(x - 1, y, color);
		DrawPixel(x - 1, y - 1, color);
		DrawPixel(x - 1, y + 1, color);
		DrawPixel(x, y - 1, color);
		DrawPixel(x, y + 1, color);
		break;

	default:
		break;
	}
}

void DrawGate(POINT pos, int color, int direction)
{
	// 0: up
	// 1: down
	// 2: left
	// 3: right
	switch (direction)
	{
	case 0:
		DrawPixel(pos.x - 1, pos.y, color);
		DrawPixel(pos.x + 1, pos.y, color);
		DrawPixel(pos.x - 1, pos.y + 1, color);
		DrawPixel(pos.x, pos.y + 1, color);
		DrawPixel(pos.x + 1, pos.y + 1, color);
		break;

	case 1:
		DrawPixel(pos.x, pos.y - 1, color);
		DrawPixel(pos.x - 1, pos.y - 1, color);
		DrawPixel(pos.x + 1, pos.y - 1, color);
		DrawPixel(pos.x + 1, pos.y, color);
		DrawPixel(pos.x - 1, pos.y, color);
		break;

	case 2:
		DrawPixel(pos.x + 1, pos.y, color);
		DrawPixel(pos.x + 1, pos.y - 1, color);
		DrawPixel(pos.x + 1, pos.y + 1, color);
		DrawPixel(pos.x, pos.y - 1, color);
		DrawPixel(pos.x, pos.y + 1, color);
		break;

	case 3:
		DrawPixel(pos.x - 1, pos.y, color);
		DrawPixel(pos.x - 1, pos.y - 1, color);
		DrawPixel(pos.x - 1, pos.y + 1, color);
		DrawPixel(pos.x, pos.y - 1, color);
		DrawPixel(pos.x, pos.y + 1, color);
		break;

	default:
		break;
	}
}