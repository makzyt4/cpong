#ifndef CPG_PAD_H
#define CPG_PAD_H

#include <SDL2/SDL.h>
#include "color.h"
#include "display.h"

#define CPG_PAD_WIDTH           15
#define CPG_PAD_HEIGHT          100
#define CPG_PAD_VELOCITY_BRAKE  0.9f
#define CPG_PAD_VELOCITY_DELTA  1.0f
#define CPG_PAD_VELOCITY_MAX    7.0f
#define CPG_PAD_COLLISION_BRAKE -0.9f

typedef struct {
    float x, y;
    int upKey, downKey;
    uint8_t aiControlled;
    float velocityY;
    uint8_t pressed;
} CPG_Pad;

void CPG_Pad_Draw(CPG_Pad* self, CPG_Display* display);
void CPG_Pad_HandleKeys(CPG_Pad* self, SDL_Event* event);
void CPG_Pad_Move(CPG_Pad* self);

#endif // CPG_PAD_H
