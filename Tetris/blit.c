#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include <SDL_ttf.h>

#include "constants.h"
#include "functions.h"

void BlitAll(SDL_Surface *background, Piece *piece, int field[FIELD_LENGHT][FIELD_HEIGHT], SDL_Surface *color, SDL_Surface *screen)
{
    BlitBackground(background, screen);

    BlitField(field, color, screen);
    BlitPiece(piece, color, screen);

    BlitNextPiece(piece, color, screen);
}

void BlitText(SDL_Surface* text, TTF_Font *police, SDL_Color colorPolice, SDL_Surface *screen)
{
    SDL_Rect dst;

        dst.x = 0;
        dst.y = 0;

    text = TTF_RenderText_Blended(police, "Salut les Zér0s !", colorPolice);

    SDL_BlitSurface(text, NULL, screen, &dst);
}

void BlitBackground(SDL_Surface *background, SDL_Surface *screen)
{
    SDL_Rect src, dst;
    src.x = BORDER_LEFT;
    src.y = BORDER_UP;
    src.w = FIELD_LENGHT*BLOCK_LENGHT;
    src.h = FIELD_HEIGHT*BLOCK_HEIGHT;

    dst.x = BORDER_LEFT;
    dst.y = BORDER_UP;

            SDL_BlitSurface(background, &src, screen, &dst);
}

void BlitPiece(Piece *piece, SDL_Surface *color, SDL_Surface *screen)
{
    int i = 0, j = 0;

    SDL_Rect src, dst;
    src.x = BLOCK_LENGHT*piece->color;
    src.y = 0;
    src.w = BLOCK_LENGHT;
    src.h = BLOCK_HEIGHT;

    for(j = 0 ; j < TAB_HEIGHT ; j++)
    {
        for(i = 0 ; i < TAB_LENGHT ; i++)
        {
            dst.x = (piece->X*BLOCK_LENGHT) + (i*BLOCK_LENGHT) + BORDER_RIGHT;
            dst.y = (piece->Y*BLOCK_HEIGHT) + (j*BLOCK_HEIGHT) + BORDER_UP;

                if(piece->tab[i][j] != EMPTY)
                    SDL_BlitSurface(color, &src, screen, &dst);
        }
    }
}

void BlitNextPiece(Piece *piece, SDL_Surface *color, SDL_Surface *screen)
{
    int i = 0, j = 0;
    int tabTmp[TAB_LENGHT][TAB_HEIGHT];

    FILE *file = NULL;

    file = fopen("Ressources/form.txt", "r");

        if(file != NULL)
        {
            int i = 0, j = 0;
            char carac = ' ';

            for(i = 0 ; i < (((TAB_LENGHT+1)*TAB_HEIGHT)+1)*piece->nextform ; i++)
                carac = fgetc(file);

                for(j = 0 ; j < TAB_HEIGHT ; j++)
                {
                    for(i = 0 ; i < TAB_LENGHT ; i++)
                    {
                        carac = fgetc(file);
                        tabTmp[i][j] = (carac-'0');
                    }

                    carac = fgetc(file);
                }

            fclose(file);
        }

        else
        {
            fprintf(stderr, "file form doesn't exist !\n");
        }

    SDL_Rect src, dst;
    src.x = BLOCK_LENGHT*piece->nextcolor;
    src.y = 0;
    src.w = BLOCK_LENGHT;
    src.h = BLOCK_HEIGHT;

    for(j = 0 ; j < TAB_HEIGHT ; j++)
    {
        for(i = 0 ; i < TAB_LENGHT ; i++)
        {
            dst.x = (i*BLOCK_LENGHT) + BORDER_RIGHT+235;
            dst.y = (j*BLOCK_HEIGHT) + BORDER_UP+20;

                if(tabTmp[i][j] != EMPTY)
                    src.x = BLOCK_LENGHT*piece->nextcolor;

                else
                    src.x = BLOCK_LENGHT*POINT;

            SDL_BlitSurface(color, &src, screen, &dst);
        }
    }
}

void BlitField(int field[FIELD_LENGHT][FIELD_HEIGHT], SDL_Surface *color, SDL_Surface *screen)
{
    int i = 0, j = 0;

    SDL_Rect src, dst;
    src.x = BLOCK_LENGHT;
    src.y = 0;
    src.w = BLOCK_LENGHT;
    src.h = BLOCK_HEIGHT;

    for(j = 0 ; j < FIELD_HEIGHT ; j++)
    {
        for(i = 0 ; i < FIELD_LENGHT ; i++)
        {
            dst.x = i*BLOCK_LENGHT + BORDER_RIGHT;
            dst.y = j*BLOCK_HEIGHT + BORDER_UP;

                if(field[i][j] != EMPTY)
                {
                    src.x = BLOCK_LENGHT*field[i][j];
                    SDL_BlitSurface(color, &src, screen, &dst);
                }
        }
    }
}

