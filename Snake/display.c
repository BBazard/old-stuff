#include <time.h>
#include <SDL.h>

#include "main.h"


void DisplayWall(SDL_Surface *screen, Wall *wall)
{
    int i = 0;
    SDL_Rect dst, src;

    src.x = BLOCK_LENGHT*WALL;
    src.y = 0;
    src.h = BLOCK_HEIGHT;
    src.w = BLOCK_LENGHT;

    for(i = 0 ; i < NBR_WALL ; i++)
    {

        dst.x = wall->posX[i] * BLOCK_LENGHT + BORDER_LEFT;
        dst.y = wall->posY[i] * BLOCK_HEIGHT + BORDER_UP;

                SDL_BlitSurface(wall->tileset, &src, screen, &dst);
    }
}

void DisplayTails(SDL_Surface *screen, Snake *snake)
{
    int i = 0;
    SDL_Rect dst, src;

    src.x = BLOCK_LENGHT*BODY;
    src.y = 0;
    src.h = BLOCK_HEIGHT;
    src.w = BLOCK_LENGHT;

    for(i = TAILS_MAX-1 ; i != 0 ; i--)
    {
        if(snake->tails > i)
        {
            dst.x = snake->lastX[i] * BLOCK_LENGHT + BORDER_LEFT;
            dst.y = snake->lastY[i] * BLOCK_HEIGHT + BORDER_UP;

                snake->lastX[i] = snake->lastX[i-1];
                snake->lastY[i] = snake->lastY[i-1];

            SDL_BlitSurface(snake->tileset, &src, screen, &dst);
        }
    }

    if(snake->tails > 0)
    {
        dst.x = snake->lastX[0] * BLOCK_LENGHT + BORDER_LEFT;
        dst.y = snake->lastY[0] * BLOCK_HEIGHT + BORDER_UP;

            snake->lastX[0] = snake->posX;
            snake->lastY[0] = snake->posY;

        SDL_BlitSurface(snake->tileset, &src, screen, &dst);
    }
}

void DiplayHeadSnake(Snake *snake, SDL_Surface *screen)
{
    SDL_Rect dst, src;

    src.x = BLOCK_LENGHT*snake->lastAction;
    src.y = 0;
    src.h = BLOCK_HEIGHT;
    src.w = BLOCK_LENGHT;

    dst.x = snake->posX * BLOCK_LENGHT + BORDER_LEFT;
    dst.y = snake->posY * BLOCK_HEIGHT + BORDER_UP;

        SDL_BlitSurface(snake->tileset, &src, screen, &dst);
}

void DisplayApple(SDL_Surface *screen, Apple *apple, Snake *snake, Wall *wall)
{
    int i = 0;
    int retry = 0;
    SDL_Rect dst, src;

        if (apple->eaten == 0)
        {
            do {
                retry = 0;

                apple->posX = rand()%FIELD_LENGHT;
                apple->posY = rand()%FIELD_HEIGHT;

                for(i = 0 ; i < TAILS_MAX ; i ++)
                {
                    if(apple->posX == snake->lastX[i] && apple->posY == snake->lastY[i])
                        retry = 1;
                }

                for(i = 0 ; i < NBR_WALL ; i ++)
                {
                    if(apple->posX == wall->posX[i] && apple->posY == wall->posY[i])
                        retry = 1;
                }

            } while((snake->posX == apple->posX && snake->posY == apple->posY) || retry);

            apple->eaten = 1;
        }

    src.x = BLOCK_LENGHT*APPLE;
    src.y = 0;
    src.h = BLOCK_HEIGHT;
    src.w = BLOCK_LENGHT;

    dst.x = apple->posX * BLOCK_LENGHT + BORDER_LEFT;
    dst.y = apple->posY * BLOCK_HEIGHT + BORDER_UP;

        SDL_BlitSurface(apple->tileset, &src, screen, &dst);
}


