#pragma once
#include <stdbool.h>

typedef enum  Display
{
    INTRO,
    MAIN,
    DEBUG,
    VILLAGE,
    HOTEL,
    MERCHANT,

}Display;

typedef enum  Dialogue
{
    DIA1,
    DIA2,
    DIA3,
    DIA4,
    DIA5,

}Dialogue;
typedef enum  Dialogue_merchant
{
    DIAA1,
    DIAA2,

}Dialogue_merchant;

typedef struct Count
{
    float freq;
    int value;
    float timer;

}Count;

typedef struct Size
{
    int width;
    int height;
}Size;

typedef struct Research
{
    bool lollipop1;
    bool lollipop2;
    bool lollipop3;
    bool lollipop4;

    int lollipopvalue;

}Research;

// Game data
typedef struct Game
{
    Size screenSize;
    Display display;
    Dialogue dialogue;
    Dialogue_merchant dialogue_merchant;
    Research research;

    // State
    Count candyCounter; 
    Count lollipopCounter;
    int candiesEaten;
    int candiesThrown;

    //REMEMBER : De base le type bool est initialiser en false
    bool village;    
    bool eatAllUnlocked;
    bool throwUnlocked;

} Game;







void game_init(Game* game, int WIDTH, int HEIGHT);
void counter_candy(Game* game);

void game_state_save_text(Game* self, const char* filename);
void game_state_load_text(Game* self, const char* filename);

void game_update(Game* game);
void game_shutdown(Game* game);

//void counter_update(Count* candy, float frameTime);
//void counter_candy(Game* game);

void hotel_update(Game* game);

