#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "constants.h"

void InitialisePiece(Piece* piece)
{
    FILE *file = NULL;

    file = fopen("Ressources/form.txt", "r");

        if(file != NULL)
        {
            int i = 0, j = 0;
            char carac = ' ';

            for(i = 0 ; i < (((TAB_LENGHT+1)*TAB_HEIGHT)+1)*piece->form ; i++)
                carac = fgetc(file);

                for(j = 0 ; j < TAB_HEIGHT ; j++)
                {
                    for(i = 0 ; i < TAB_LENGHT ; i++)
                    {
                        carac = fgetc(file);
                        piece->tab[i][j] = (carac-'0');
                    }

                    carac = fgetc(file);
                }

            fclose(file);
        }

        else
        {
            fprintf(stderr, "file form doesn't exist !\n");
        }
}

void NewPiece(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    if(piece->blocked)
    {
        int i, j;

        for(j = 0 ; j < TAB_HEIGHT ; j++)
        {
            for(i = 0 ; i < TAB_LENGHT ; i++)
            {
                if(field[piece->X+i][piece->Y+j] == EMPTY && piece->tab[i][j] != EMPTY)
                    field[piece->X+i][piece->Y+j] = piece->color;
            }
        }

        piece->form = piece->nextform;
        piece->color = piece->nextcolor;
        piece->nextform = rand()%(Z+1);
        piece->nextcolor = piece->nextform+1;
        piece->X = 5;
        piece->Y = 0;
        piece->blocked = 0;

        InitialisePiece(piece);
    }
}

