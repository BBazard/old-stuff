#ifndef FILE_CONSTANTS
#define FILE_CONSTANTS

#define WINDOW_LENGHT 500
#define WINDOW_HEIGHT 500

#define BORDER_UP 50
#define BORDER_DOWN 50
#define BORDER_LEFT 150
#define BORDER_RIGHT 150

#define FIELD_LENGHT 10
#define FIELD_HEIGHT 20
#define TAB_LENGHT 4
#define TAB_HEIGHT 4

#define BLOCK_LENGHT 20
#define BLOCK_HEIGHT 20
#define NBR_PIECES 7

#define SPEED_INITIAL 100
#define SPEED_STEP 5

#include <SDL_ttf.h>


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
    unsigned int elapsed;
    unsigned int lastTime;
    unsigned int speed;
    int frame;

} Time;

typedef struct
{
    char tab[TAB_LENGHT][TAB_HEIGHT];
    char form, color;
    char nextform, nextcolor;
    int X, Y;
    char blocked;

} Piece;

typedef struct
{
    SDL_Surface* text;
    TTF_Font *police;
    SDL_Color colorPolice;

} TTF;


    enum {EMPTY,    RED,    GREEN,  BROWN,  PURPLE,     YELLOW,     BLUE,   WHITE,  POINT,  ERROR};
    enum {          I,        O,      T,      L,      J,          S,          Z};
    enum {UP, DOWN, LEFT, RIGHT};


#endif

