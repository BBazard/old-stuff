#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include <SDL_ttf.h>

#include "constants.h"
#include "functions.h"

/**
    TODO :  gérer le texte
            gérer le son
            mettre une icone
**/

int main ( int argc, char** argv )
{
    srand(time(NULL));

    Input in;
    memset(&in,0,sizeof(in));
    Time time;
        time.elapsed = 0;
        time.lastTime = 0;
        time.speed = SPEED_INITIAL;
        time.frame = 0;

    SDL_Init(SDL_INIT_VIDEO);
        if(TTF_Init() == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }

    TTF_Font *police = NULL;
    SDL_Color colorPolice = {0, 0, 0};

    police = TTF_OpenFont("angelina.ttf", 65);
    SDL_Surface* text = NULL;
    text = TTF_RenderText_Blended(police, "Salut les Zér0s !", colorPolice);


    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_LENGHT, WINDOW_HEIGHT, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
                                            SDL_WM_SetCaption("Tetris", NULL);

    SDL_Surface *color = SDL_LoadBMP("Ressources/TileSetColor.bmp");
        SDL_SetColorKey(color, SDL_SRCCOLORKEY, SDL_MapRGB(color->format, 0, 250, 250));
    SDL_Surface *background = SDL_LoadBMP("Ressources/background.bmp");

    SDL_Surface *gameOver = SDL_LoadBMP("Ressources/Game Over.bmp");
        SDL_SetAlpha(gameOver, SDL_SRCALPHA, 128);

    Piece current;
        current.form = rand()%(Z+1);
        current.color = current.form+1;
        current.nextform = rand()%(Z+1);
        current.nextcolor = current.nextform+1;
        current.X = 1;
        current.Y = 0;
        current.blocked = 0;

    int field[FIELD_LENGHT][FIELD_HEIGHT];
        InitialiseField(field);
        InitialisePiece(&current);

    SDL_BlitSurface(background, 0, screen, NULL);

    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
        UpdateEvents(&in);

        ManageEvent(&in, field, &current, &time);

        if(SpendTime(&time))
        {
            if(activeFrame(&time, 10))
            {
                (!CollideDown(field, &current) && !current.blocked) ?
                (current.Y += 1) : (current.blocked = 1);
            }

                BlitAll(background, &current, field, color, screen);

                DeleteLign(field);
                SDL_Flip(screen);
        }

        NewPiece(field, &current);
            GameOver(&in, field, &current, gameOver, background, screen);
    }

    SDL_FreeSurface(text);
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(color);
    SDL_FreeSurface(background);
    SDL_FreeSurface(gameOver);
    SDL_Quit();

    return EXIT_SUCCESS;
}

int activeFrame(Time* time, int frameMax)
{
    if(time->frame == 0)
    {
        time->frame = 1;

        return 1;
    }

    else
    {
        time->frame++;

        if(time->frame == frameMax)
            time->frame = 0;

        return 0;
    }
}

int RemoveLign(int field[FIELD_LENGHT][FIELD_HEIGHT])
{
    int i = 0, j;
    char fullLign = 1;
    int lignFull = -1;

    for(j = 0 ; j < FIELD_HEIGHT; j++)
    {
        fullLign = 1;

        for(i = 0 ; i < FIELD_LENGHT; i++)
        {
            if(field[i][j] == EMPTY)
                fullLign = 0;
        }
        if(fullLign == 1)
            return lignFull = j;
    }

   return lignFull;
}

void DeleteLign(int field[FIELD_LENGHT][FIELD_HEIGHT])
{
    int i, j;
    int ligneToDelete = RemoveLign(field);
    int copie[FIELD_LENGHT][FIELD_HEIGHT];

        if(ligneToDelete != -1)
        {
            for(j = 0 ; j < FIELD_HEIGHT ; j++)
            {
                for(i = 0 ; i < FIELD_LENGHT ; i++)
                {
                    copie[i][j] = field[i][j];
                }
            }

            for(j = 1 ; j < FIELD_HEIGHT ; j++)
            {
                for(i = 0 ; i < FIELD_LENGHT ; i++)
                {
                    if(j <= ligneToDelete)
                    field[i][j] = copie[i][j-1];

                    else
                    field[i][j] = copie[i][j];
                }
            }

            for(i = 0 ; i < FIELD_LENGHT ; i++)
                field[i][0] = EMPTY;
        }
}

void InitialiseField(int field[FIELD_LENGHT][FIELD_HEIGHT])
{
    int i, j;
    for(j = 0 ; j < FIELD_HEIGHT ; j++)
    {
        for(i = 0 ; i < FIELD_LENGHT ; i++)
        {
           field[i][j] = EMPTY;
        }
    }
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

