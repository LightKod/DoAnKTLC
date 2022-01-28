#include <Windows.h>

#define PIXEL_WIDTH 2
#define PIXEL_HEIGHT 1
#define SCREEN_WIDTH 160
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
void SetColor(int bg_color, int text_color);