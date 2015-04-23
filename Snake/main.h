#ifndef GUARD
#define GUARD

#define WINDOW_LENGHT 640
#define WINDOW_HEIGHT 480

#define BORDER_UP 40
#define BORDER_DOWN 60
#define BORDER_LEFT 180
#define BORDER_RIGHT 120

#define BLOCK_LENGHT 20
#define BLOCK_HEIGHT 20

#define FIELD_LENGHT ((WINDOW_LENGHT-(BORDER_LEFT+BORDER_RIGHT))/BLOCK_LENGHT)
#define FIELD_HEIGHT ((WINDOW_HEIGHT-(BORDER_UP+BORDER_DOWN))/BLOCK_HEIGHT)

#define TAILS_MAX 50
#define NBR_WALL 0
#define SPEED_INITIAL 100
#define SPEED_STEP 3
/*

MOVE : DIRECTIONAL ARROWS
RETRY : SPACE

*/
typedef struct
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[6];
	char quit;
} Input;

typedef struct
{
    SDL_Surface *tileset;
    unsigned char posX, posY;
    unsigned char lastX[TAILS_MAX], lastY[TAILS_MAX];
    unsigned char lastAction;
    unsigned char tails;
} Snake;

typedef struct
{
    SDL_Surface *tileset;
    unsigned char posX, posY;
    unsigned char eaten;
} Apple;

typedef struct
{
    SDL_Surface *tileset;
    unsigned char posX[NBR_WALL], posY[NBR_WALL];
} Wall;

typedef struct
{
    unsigned int elapsed;
    unsigned int lastTime;
    unsigned int speed;
    unsigned char over;
    unsigned char retry;
} Time;

// Initialise Functions

void InitialiseTails(Snake *snake);

void PutWall(Wall *wall);

// Time Functions

void UpdateEvents(Input* in);

void ManageEvents(Input *in, Snake *snake);

int SpendTime(Time *time);

void MoveSnake(Snake *snake);

// Collide Functions

int BiteTails(Snake *snake);

int HitWall(Snake *snake, Wall *wall);

// Display Functions

void DisplayWall(SDL_Surface *screen, Wall *wall);

void DisplayTails(SDL_Surface *screen, Snake *snake);

void DiplayHeadSnake(Snake *snake, SDL_Surface *screen);

void DisplayApple(SDL_Surface *screen, Apple *apple, Snake *snake, Wall *wall);

// IA FUNCTION

void DirectionMoveAuto(Snake *snake, Wall *wall, Apple *apple, int DIRECTION);
void MoveSnakeAuto(Snake *snake, Wall *wall, Apple *apple);


    enum{BODY, UP, DOWN, LEFT, RIGHT, APPLE, EMPTY, WALL};

#endif

