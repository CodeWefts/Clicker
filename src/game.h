#pragma once

// Game data
typedef struct Game
{
    int value;
} Game;

void game_init(Game* game);
void game_update(Game* game);
void game_shutdown(Game* game);
