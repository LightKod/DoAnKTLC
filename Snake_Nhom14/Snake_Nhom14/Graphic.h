#include <Windows.h>

#define PIXEL_WIDTH 2
#define PIXEL_HEIGHT 1
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 45
#define DEFAULT_BACKGROUND_COLOR 0
#define DEFAULT_TEXT_COLOR 7

void ShowCursor(bool cursor_visibility);
void DisableSelection();
void SetUp();
void FixWindowSize();
void DisableControlButton(bool close, bool min, bool max);
void GoToXY(int x, int y);
void GoToXYPixel(int x, int y);
void GoToXYPixel(POINT pos);
void SetColor(int bg_color, int text_color);
void DrawPixel(int x, int y, int color);
void DrawPixel(POINT pos, int color);
void DrawPixel(int x, int y, int bg_color, int text_color, char text);
void DrawPixel(POINT pos, int bg_color, int text_color, char text);
void DrawPixel(int x, int y, int bg_color, int text_color, char text[], int size);
void DrawPixel(int x, int y, int bg_color, int text_color, const char text[], int size);
void DrawRectangle(int x, int y, int width, int height, int color);
void DrawRectangle(POINT pos, int width, int height, int color);
void DrawBorder(int x, int y, int width, int height, int color);
void DrawBorder(POINT pos, int width, int height, int color);
void DrawBorder(int x, int y, int width, int height, int border_color, int inner_color);
void DrawBorder(POINT pos, int width, int height, int border_color, int inner_color);
void DrawBorderWithThickness(int x, int y, int width, int height, int thickness, int color);
void DrawBorderWithThickness(POINT pos, int width, int height, int thickness, int color);
void DrawBorderWithThickness(int x, int y, int width, int height, int thickness, int border_color, int inner_color);
void DrawBorderWithThickness(POINT pos, int width, int height, int thickness, int border_color, int inner_color);
void DrawPixels(POINT pos[], int size, int color);
void DrawPixels(POINT pos[], int size, int color[]);
void DrawPixels(POINT pos[], int size, int bg_color, int text_color, char text);
void DrawPixels(POINT pos[], int size, int bg_color, int text_color, char text[]);
void DrawPixels(POINT pos[], int size, int bg_color[], int text_color[], char text);
void DrawPixels(POINT pos[], int size, int bg_color[], int text_color, char text[]);
void DrawGate(int x, int y, int color, int direction);
void DrawGate(POINT pos, int color, int direction);