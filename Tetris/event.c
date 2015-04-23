#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "constants.h"
#include "functions.h"

void ManageEvent(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece, Time* time)
{
    SaveMap(in, field, piece);
    LoadMap(in, field, piece);

        if(time->frame != 0)
        {
            Move(in, field, piece);
            TurnPiece(in, field, piece);
        }

    Drop(in, field, piece);
}

void GameOver(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece, SDL_Surface *gameOver, SDL_Surface *background, SDL_Surface *screen)
{
    if(CollideLeft(field, piece) && CollideRight(field, piece) && CollideDown(field, piece) && piece->Y <= 0)
    {
        int compteur = 1;
        while(!in->key[SDLK_ESCAPE] && !in->quit)
        {
            UpdateEvents(in);

            if(LoadMap(in, field, piece))
            {
                SDL_BlitSurface(background, 0, screen, NULL);
                break;
            }

                if(compteur == 1)
                {
                    compteur = 2;
                    SDL_BlitSurface(gameOver, 0, screen, NULL);
                    SDL_Flip(screen);
                }
        }
    }
}

void Drop(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    if(in->key[SDLK_SPACE])
    {
        while(!CollideDown(field, piece) && !piece->blocked)
                piece->Y += 1;

        in->key[SDLK_SPACE] = 0;
    }
}

int SaveMap(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    int SAVE_SUCCESS = 0;

        if(in->key[SDLK_s])
        {
            FILE *file = NULL;

            file = fopen("Ressources/save1.txt", "w");

                if(file != NULL)
                {
                    int i = 0, j = 0;

                        for(j = 0 ; j < FIELD_HEIGHT ; j++)
                        {
                            for(i = 0 ; i < FIELD_LENGHT ; i++)
                            {
                                fprintf(file, "%d\t", field[i][j]);
                            }

                            fprintf(file, "\n");
                        }

                    fclose(file);
                    SAVE_SUCCESS = 1;
                }

                else
                {
                    fprintf(stderr, "Save Failure !\n");
                }

            in->key[SDLK_s] = 0;
        }

    return SAVE_SUCCESS;
}

int LoadMap(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    int LOAD_SUCCESS = 0;

        if(in->key[SDLK_l])
        {
            FILE *file = NULL;

            char name[27] = "Ressources/Saves/Save .txt";
            int i = 0;
            int load = 0;

                for(i = 0 ; i <= 10 ; i++)
                {
                    if(in->key[SDLK_0+i])
                    {
                        name[27-6] = '0'+i;
                        load = 1;
                    }
                    in->key[SDLK_0+i] = 0;
                }

            if(load != 1)
                file = fopen("Ressources/New Game.txt", "r");

            else
                file = fopen(name, "r");

                if(file != NULL)
                {
                    int i = 0, j = 0;
                    char carac = ' ';

                        for(j = 0 ; j < FIELD_HEIGHT ; j++)
                        {
                            for(i = 0 ; i < FIELD_LENGHT ; i++)
                            {
                                carac = fgetc(file);
                                field[i][j] = (carac-'0');
                                carac = fgetc(file);
                            }

                            carac = fgetc(file);
                        }

                    fclose(file);

                    LOAD_SUCCESS = 1;
                }

                else
                {
                    fprintf(stderr, "file \"%s\" doesn't exist !\n", name);
                }

            in->key[SDLK_l] = 0;
        }

    return LOAD_SUCCESS;
}

void Move(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    if(in->key[SDLK_LEFT])
    {
        if(!CollideLeft(field, piece))
            piece->X--;
    }

    else if(in->key[SDLK_RIGHT])
    {
        if(!CollideRight(field, piece))
            piece->X++;
    }

    else if(in->key[SDLK_DOWN])
    {
        if(!CollideDown(field, piece))
            piece->Y++;
    }

    SDL_Delay(SPEED_INITIAL);

    /*in->key[SDLK_LEFT] = 0;
    in->key[SDLK_RIGHT] = 0;*/
}

void TurnPiece(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    int i, j;
    Piece copie;

    if(in->key[SDLK_UP] && piece->form != O)
    {
        for(j = 0 ; j < TAB_HEIGHT ; j++)
        {
            for(i = 0 ; i < TAB_LENGHT ; i++)
            {
                copie.tab[i][j] = piece->tab[i][j];
            }
        }
            if(piece->form == I)
            {
                for(j = 0 ; j < TAB_HEIGHT ; j++)
                {
                    for(i = 0 ; i < TAB_LENGHT ; i++)
                    {
                        piece->tab[i][j] = copie.tab[TAB_HEIGHT-j-1][i];
                    }
                }
            }

            else
            {
                for(j = 0 ; j < TAB_HEIGHT-1 ; j++)
                {
                    for(i = 0 ; i < TAB_LENGHT-1 ; i++)
                    {
                        piece->tab[i][j] = copie.tab[TAB_HEIGHT-j-2][i];
                    }
                }
            }


             if(CollideLeftOrRightNoForecast(field, piece))
             {
                for(j = 0 ; j < TAB_HEIGHT ; j++)
                {
                    for(i = 0 ; i < TAB_LENGHT ; i++)
                    {
                        piece->tab[i][j] = copie.tab[i][j];
                    }
                }
            }

        in->key[SDLK_UP] = 0;
    }
}
