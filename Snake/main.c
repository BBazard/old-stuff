#include <time.h>
#include <SDL.h>

#include "main.h"

int main ( int argc, char** argv )
{
    Input in;

    srand(time(NULL));

   Time time;
    time.elapsed = 0;
    time.lastTime = 0;
    time.speed = SPEED_INITIAL;
    time.over = 0;
    time.retry = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_LENGHT, WINDOW_HEIGHT, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
                                        SDL_WM_SetCaption("Snake", NULL);

    SDL_Surface *bg = SDL_LoadBMP("Sprites/bg.bmp");
        SDL_SetAlpha(bg, SDL_SRCALPHA, 128);

    SDL_Surface *tileset = SDL_LoadBMP("Sprites/SnakeTileSet.bmp");
    SDL_SetColorKey(tileset, SDL_SRCCOLORKEY, SDL_MapRGB(tileset->format, 0, 250, 250));

    SDL_Surface *gameOver = SDL_LoadBMP("Sprites/Game Over.bmp");
        SDL_SetAlpha(gameOver, SDL_SRCALPHA, 128);

    Snake snake;
        snake.tileset = tileset;
        snake.posX = 0, snake.posY = 0;
        snake.lastAction = BODY;
        snake.tails = 0;

    Apple apple;
        apple.tileset = tileset;
        apple.posX = BORDER_LEFT;
        apple.posY = BORDER_UP;
        apple.eaten = 0;

    Wall wall;
        wall.tileset = tileset;

        while(time.retry)
        {
            time.retry = 0;
            time.over = 0;
            snake.tails = 0;
            time.speed = SPEED_INITIAL;

            InitialiseTails(&snake);
            PutWall(&wall);

            memset(&in,0,sizeof(in));
            while(!in.key[SDLK_ESCAPE] && !in.quit && !time.over)
            {
                UpdateEvents(&in);

                ManageEvents(&in, &snake);

                    if(SpendTime(&time))
                    {
                            MoveSnake(&snake);
                           // MoveSnakeAuto(&snake, &wall, &apple);

                        SDL_BlitSurface(bg, 0, screen, NULL);

                            if (snake.posX == apple.posX && snake.posY == apple.posY)
                            {
                                apple.eaten = 0;
                                snake.tails++;

                                    if(time.speed > SPEED_STEP)
                                        time.speed -= SPEED_STEP;
                            }

                            if (BiteTails(&snake) || HitWall(&snake, &wall))
                                time.over = 1;

                        DisplayTails(screen, &snake);

                        DiplayHeadSnake(&snake, screen);

                        DisplayWall(screen, &wall);

                        DisplayApple(screen, &apple, &snake, &wall);

                        SDL_Flip(screen);
                    }
            }

            SDL_Rect dst;

            dst.x = (WINDOW_LENGHT - 200)/2;
            dst.y = (WINDOW_HEIGHT - 200)/2;

                    SDL_BlitSurface(gameOver, 0, screen, &dst);

                SDL_Flip(screen);

            while(!in.key[SDLK_ESCAPE] && !in.quit && !time.retry)
            {
                UpdateEvents(&in);

                if(in.key[SDLK_SPACE])
                {
                    time.retry = 1;
                    break;
                }
            }
            snake.lastAction = BODY;
            snake.posX = 0, snake.posY = 0;
        }

    SDL_FreeSurface(gameOver);
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(bg);
    SDL_Quit();

    return snake.tails;
}

void DirectionMoveAuto(Snake *snake, Wall *wall, Apple *apple, int DIRECTION)
{
    int OPPOSE = 0;

    if(DIRECTION == RIGHT)
        OPPOSE = LEFT;

    if(DIRECTION == LEFT)
        OPPOSE = RIGHT;

    if(DIRECTION == UP)
        OPPOSE = DOWN;

    if(DIRECTION == DOWN)
        OPPOSE = UP;

        MoveSnake(snake);

        if(snake->lastAction == OPPOSE || BiteTails(snake) || HitWall(snake, wall))
        {
            snake->lastAction = (rand()%4)+1;
            MoveSnake(snake);
        }

        else
        {
            snake->lastAction = DIRECTION;
            MoveSnake(snake);
        }
}

void MoveSnakeAuto(Snake *snake, Wall *wall, Apple *apple)
{
    if (apple->posX > snake->posX)
    {
        DirectionMoveAuto(snake, wall, apple, RIGHT);
    }

    else if (apple->posX < snake->posX)
    {
        DirectionMoveAuto(snake, wall, apple, LEFT);
    }

    else if (apple->posY > snake->posY)
    {
        DirectionMoveAuto(snake, wall, apple, DOWN);
    }

    else if (apple->posY < snake->posY)
    {
        DirectionMoveAuto(snake, wall, apple, UP);
    }
}

void MoveSnake(Snake *snake)
{
    if(snake->lastAction == UP)
    {
        if(snake->posY <= 0)
            snake->posY = FIELD_HEIGHT-1;

        else
            snake->posY--;
    }

    else if(snake->lastAction == DOWN)
    {
        if(snake->posY >= FIELD_HEIGHT-1)
            snake->posY = 0;

        else
            snake->posY++;
    }

    else if(snake->lastAction == LEFT)
    {
        if(snake->posX <= 0)
            snake->posX = FIELD_LENGHT-1;

        else
            snake->posX--;
    }

    else if(snake->lastAction == RIGHT)
    {
        if(snake->posX >= FIELD_LENGHT-1)
            snake->posX = 0;

        else
            snake->posX++;
    }
}

int HitWall(Snake *snake, Wall *wall)
{
    int i = 0;

        for(i = 0 ; i < NBR_WALL ; i++)
        {
            if (snake->posX == wall->posX[i] && snake->posY == wall->posY[i])
                return 1;
        }

    return 0;
}

int BiteTails(Snake *snake)
{
    int i = 0;

        for(i = 0 ; i < snake->tails ; i++)
        {
            if (snake->posX == snake->lastX[i] && snake->posY == snake->lastY[i])
                return 1;
        }

    return 0;
}

void PutWall(Wall *wall)
{
    int i = 0, j = 0;

        for(i = 0 ; i < NBR_WALL ; i++)
        {
            wall->posX[i] = rand()%FIELD_LENGHT;
            wall->posY[i] = rand()%FIELD_HEIGHT;
        }

        for(j = 0 ; j < NBR_WALL ; j++)
        {
            for(i = 0 ; i < NBR_WALL ; i++)
            {
                if(wall->posX[j] == wall->posX[i] && wall->posY[j]== wall->posY[i])
                {
                    wall->posX[j] = rand()%FIELD_LENGHT;
                    wall->posY[j] = rand()%FIELD_HEIGHT;
                }

                if(wall->posX[j] == 0 && wall->posY[j]== 0)
                {
                    wall->posX[j] = rand()%FIELD_LENGHT;
                    wall->posY[j] = rand()%FIELD_HEIGHT;
                }
            }
        }
}

void InitialiseTails(Snake *snake)
{
    int i = 0;

        for(i = 0 ; i < TAILS_MAX ; i++)
        {
            snake->lastX[i] = 200;
            snake->lastY[i] = 200;
        }
}

void ManageEvents(Input *in, Snake *snake)
{
    if(in->key[SDLK_UP] && snake->lastAction != DOWN)
    {
        snake->lastAction = UP;
        in->key[SDLK_UP] = 0;
    }

    if(in->key[SDLK_DOWN] && snake->lastAction != UP)
    {
        snake->lastAction = DOWN;
        in->key[SDLK_DOWN] = 0;
    }

    if(in->key[SDLK_LEFT] && snake->lastAction != RIGHT)
    {
        snake->lastAction = LEFT;
        in->key[SDLK_LEFT] = 0;
    }

    if(in->key[SDLK_RIGHT] && snake->lastAction != LEFT)
    {
        snake->lastAction = RIGHT;
        in->key[SDLK_RIGHT] = 0;
    }
}

int SpendTime(Time *time)
{
    time->elapsed = SDL_GetTicks();
        if (time->elapsed - time->lastTime > time->speed)
        {
            time->lastTime = time->elapsed;
            return 1;
        }

    SDL_Delay(time->speed - (time->elapsed - time->lastTime));
        return 0;
}

void UpdateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
			in->mousebuttons[event.button.button-1]=1;
			break;
		case SDL_MOUSEBUTTONUP:
			in->mousebuttons[event.button.button-1]=0;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}

