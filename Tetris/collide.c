#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "constants.h"

int CollideDown(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    int i, j;
    int X, Y;
    int collide = 0;

        for(j = 0 ; j < TAB_HEIGHT ; j++)
        {
            for(i = 0 ; i < TAB_LENGHT ; i++)
            {
                X = piece->X+i;
                Y = piece->Y+j;

                    if(piece->tab[i][j] != EMPTY && field[X][Y+1] != EMPTY)
                        collide = 1;
            }
        }

    for(i = 0 ; i < TAB_HEIGHT ; i++)
    {
        for(j = 0 ; j < TAB_LENGHT ; j++)
        {
            if(piece->Y == FIELD_HEIGHT-i-1 && piece->tab[j][i] != EMPTY)
                collide = 1;
        }
    }

    if(piece->Y == FIELD_HEIGHT)
        collide = 1;

    return collide;
}

int CollideRight(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    return CollideLeftOrRight(field, piece, RIGHT);
}

int CollideLeft(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    return CollideLeftOrRight(field, piece, LEFT);
}

int CollideLeftOrRight(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece, int DIRECTION)
{
    int i, j;
    int X, Y;
    int collide = 0;

    for(j = 0 ; j < TAB_HEIGHT ; j++)
    {
        for(i = 0 ; i < TAB_LENGHT ; i++)
        {
            X = piece->X+i;
            Y = piece->Y+j;

                if((DIRECTION == RIGHT && piece->tab[i][j] != EMPTY && field[X+1][Y] != EMPTY) ||
                (DIRECTION == LEFT && piece->tab[i][j] != EMPTY && field[X-1][Y] != EMPTY))
                {
                    collide = 1;
                }
        }
    }

    for(i = 0 ; i < TAB_LENGHT ; i++)
    {
        for(j = 0 ; j < TAB_HEIGHT ; j++)
        {
            if((DIRECTION == RIGHT && piece->X == FIELD_LENGHT-i-1 && piece->tab[i][j] != EMPTY) ||
            (DIRECTION == LEFT && piece->X == i-TAB_LENGHT+1 && piece->tab[3-i][j] != EMPTY))
            {
                collide = 1;
            }
        }
    }

    return collide;
}

int CollideLeftOrRightNoForecast(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece)
{
    int i, j;
    int X, Y;
    int collide = 0;

    for(j = 0 ; j < TAB_HEIGHT ; j++)
    {
        for(i = 0 ; i < TAB_LENGHT ; i++)
        {
            X = piece->X+i;
            Y = piece->Y+j;

                if(piece->tab[i][j] != EMPTY && field[X][Y] != EMPTY)
                {
                    collide = 1;
                }
        }
    }

    for(i = 0 ; i < TAB_LENGHT ; i++)
    {
        for(j = 0 ; j < TAB_HEIGHT ; j++)
        {
            if((piece->X == FIELD_LENGHT-i && piece->tab[i][j] != EMPTY) ||
            (piece->X == i-TAB_LENGHT && piece->tab[3-i][j] != EMPTY))
            {
                collide = 1;
            }
        }
    }

    return collide;
}
