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

const char snake_default_text[] = "21127151 21127077 21127483 21127297 ";
const int textSize = 36;

static float fps = 100;

// snake's properties
static POINT snake_pos[2000];
static int snake_color[2000] = { 1, 9 };
static int snakeSize;
static Direction snake_dir;
static State snake_state;
static float snake_speed;
static char snake_text[2000];
static int current_last_text;

// food's properties
static POINT food_pos;
static int food_color = 4;
static char food_text;
static int food_state;
static POINT bigfood_pos[4];
static int bigfood_state;
static int bigfood_color = 4;
static int bigfood_ratio = 50;
static float bigfood_lifeTime = 5;
static float bigfood_lifetimeDelay = 5;

static int score;
static POINT last_pos;
static char name[4];

static int t1, t2, game_time;

const int game_field_width = 43;
const int game_field_height = 43;
const POINT game_field_pos = { 1, 1 };
const int game_field_color = 2;

// Wall
static POINT wall_pos[2000];
static int wall_size;
static int wall_color = 15;

static POINT gate_pos;
static int gate_color = 8;
static int gate_dir;
static POINT gate_colliders[6];
static int gate_state;

static int level;
static Direction previous_dir;
static int process = 2;
static bool sfx = true;

bool IsValid(int x, int y);
bool IsWallValid(int x, int y);
void GenerateFood();
void TestFoodSpawn();
void ResetData(); // Reset game data
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void RunGamePlay();
void GameInput();
void Move();
bool IsHitTheBorder();
bool IsHitYourself();
bool IsHitTheWall();
void ProcessDead();
void Eat();
void SpawnFood();
bool IsAlreadyHad();
void GenerateWall();
void GenerateWallNew();
void SetGateCollider();
bool IsHitTheGate();
void GenerateGate();
void ToTheNextLevel();
void ProcessBar();
void ToggleSfx();
void GenerateBigFood();
void RunMiniGame1();//Maze
void GenerateMaze();
void RunMiniGame2();//Revert
void MiniGame2ResetData();
void MiniGame2Eat();
