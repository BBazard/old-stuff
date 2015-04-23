#ifndef FILE_FUNCTIONS
#define FILE_FUNCTIONS

#include <SDL_ttf.h>

void UpdateEvents(Input* in);

int SpendTime(Time *time);

int activeFrame(Time* time, int frameMax);

void InitialisePiece(Piece* piece);

void InitialiseField(int field[FIELD_LENGHT][FIELD_HEIGHT]);


// BLIT FUNCTIONS :

void BlitAll(SDL_Surface *background, Piece *piece, int field[FIELD_LENGHT][FIELD_HEIGHT], SDL_Surface *color, SDL_Surface *screen);

void BlitText(SDL_Surface* text, TTF_Font *police, SDL_Color colorPolice, SDL_Surface *screen);

void BlitBackground(SDL_Surface *background, SDL_Surface *screen);

void BlitField(int field[FIELD_LENGHT][FIELD_HEIGHT], SDL_Surface *color, SDL_Surface *screen);

void BlitPiece(Piece *piece, SDL_Surface *color, SDL_Surface *screen);

void BlitNextPiece(Piece *piece, SDL_Surface *color, SDL_Surface *screen);


// COLLIDE FUNCTIONS :

int CollideDown(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

int CollideLeft(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

int CollideRight(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

int CollideLeftOrRight(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece, int DIRECTION);

int CollideLeftOrRightNoForecast(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);


// EVENT FUNCTIONS :

void ManageEvent(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece, Time* time);

void Move(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

void TurnPiece(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

void Drop(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

int SaveMap(Input* in, int Field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

int LoadMap(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);

void GameOver(Input* in, int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece, SDL_Surface *gameOver, SDL_Surface *background, SDL_Surface *screen);


int RemoveLign(int field[FIELD_LENGHT][FIELD_HEIGHT]);

void DeleteLign(int field[FIELD_LENGHT][FIELD_HEIGHT]);

void NewPiece(int field[FIELD_LENGHT][FIELD_HEIGHT], Piece *piece);


#endif


