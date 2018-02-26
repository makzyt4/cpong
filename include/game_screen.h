#ifndef CPG_GAME_SCREEN_H
#define CPG_GAME_SCREEN_H

#include <stdlib.h>
#include "display.h"
#include "pad.h"
#include "screen.h"

#define CPG_WIN_POINTS  15
#define CPG_STAR_NUMBER 50
#define CPG_START_TIME  3

typedef enum {
    CPG_STATE_PLAYING,
    CPG_STATE_COUNTING,
    CPG_STATE_PAUSED,
    CPG_STATE_GAMEOVER
} CPG_GameState;

CPG_Screen* CPG_GameScreen_Init(CPG_Display* display);

#endif // CPG_GAME_SCREEN_H
