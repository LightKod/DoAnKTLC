#include <Windows.h>

enum class Direction // direction of snake
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class State // state of snake
{
	DEAD,
	ALIVE
};

const char snake_default_text[] = "21127151 21127077 21127483 21127297";
const int textSize = 35;

static float fps = 60;

// snake's properties
static POINT snake_pos[100];
static int snake_color;
static int snakeSize;
static Direction snake_dir;
static State snake_state;
static float snake_speed;
static char snake_text[100];
static int current_last_text;

// food's properties
static POINT food_pos;
static int food_color = 4;
static char food_text;

static int score;
static POINT last_pos;

static int t1, t2, game_time;

bool IsValid(int x, int y);
void GenerateFood();
void TestFoodSpawn();
void ResetData(); // Reset game data
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void TestSnakeMove();
void GameInput();
void Move();
bool IsHitTheWall();
bool IsHitYourself();
void ProcessDead();
void Eat();