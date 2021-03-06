#ifndef H_CONST
#define H_CONST

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

#define TILE_NUMBER_MAP 6
#define TILE_NUMBER_WORLD 6

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 13

    enum{QUADRILLAGE_MAP, BLOC, OBSTACLE, OBSTACLE2, INTERRUPTEUR_GAUCHE, INTERRUPTEUR_DROITE}; //For MAP
    enum{QUADRILLAGE_WORLD, ONE, TWO, THREE, TWO2, FOUR}; //For WORLD
    enum{SELECTION = 100, TILE_TOOL_BOX = 101}; //For INTERFACE

    enum{WORLD, MAP}; // FOR Mode Selection
    enum{EDIT, SELECTION_MAP, SELECTION_INITIAL_MAP}; // FOR Edit Mode


    enum{UP, DOWN, LEFT, RIGHT};    // For LinkWorld

#endif

