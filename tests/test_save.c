/*
#include <stdbool.h>
#include <stdio.h>

#include "../src/gui.h"

typedef struct GameState
{
    int candies;
    int lollipops;
    int candiesEaten;
    bool eatAllUnlocked;
    bool throwUnlocked;
} GameState;

void t_game_state_update(GameState* self)
{
    // Modify game data
    self->candies += 1;
    self->lollipops += 10;

    if (self->candies > 100)
        self->eatAllUnlocked = true;
        
    if (self->candies > 1000)
        self->throwUnlocked = true;

    // Display game state
    im_print(1, 1, "Candies: %d", self->candies);
    im_print(1, 2, "Lollipops: %d", self->lollipops);
    
    if (self->eatAllUnlocked)
    {
        if (im_button(1, 3, "Eat all"))
        {
            self->candiesEaten += self->candies;
            self->candies = 0;
        }

        if (self->candiesEaten > 0)
            im_print(1, 4, "Candies eaten: %d", self->candiesEaten);
    }
    
    if (self->throwUnlocked && im_button(1, 6, "Throw all"))
        self->candies = 0;
}

void t_game_state_save(GameState* self, const char* filename)
{
    // TODO: Savegardez l'état du gamestate "self"

    // Fonctions fopen -> fwrite -> fclose

    FILE* file = fopen(filename,"wb");
    fwrite(self,sizeof(GameState),1,file);
    fclose(file);
}

void t_game_state_load(GameState* self, const char* filename)
{
    // TODO: Chargez l'état du gamestate "self"
    FILE* file = fopen(filename,"rb");
    fread(self,sizeof(GameState),1,file);
    fclose(file);
    // Fonctions fopen -> fread -> fclose
}

void t_game_state_save_text(GameState* self, const char* filename)
{
    FILE* file = fopen(filename,"r");
    fwrite(self,sizeof(GameState),1,file);
    fclose(file);

}

void t_game_state_load_text(GameState* self, const char* filename)
{
    FILE* file = fopen(filename,"r");
    fread(self,sizeof(GameState),1,file);
    fclose(file);
}

GameState gameState = {0};

void t_test_save_update(void)
{
    game_state_update(&gameState);
    
    if (im_button(1, 12, "Save binary"))
        game_state_save(&gameState, "save.bin");
    if (im_button(1, 13, "Load binary"))
        game_state_load(&gameState, "save.bin");
    
    if (im_button(1, 15, "Save text"))
        game_state_save_text(&gameState, "save.txt");
    if (im_button(1, 16, "Load text"))
        game_state_load_text(&gameState, "save.txt");
}
*/