#ifndef CPG_STAR_H
#define CPG_STAR_H

#include "display.h"

#define CPG_SCREEN_CENTER_X (CPG_SCREEN_WIDTH / 2)
#define CPG_SCREEN_CENTER_Y (CPG_SCREEN_HEIGHT / 2)
#define CPG_STAR_MOVEMENT_MULTIPLIER 1.1f

typedef struct {
    float x1, y1;
    float x2, y2;
} CPG_Star;

void CPG_Star_Init(CPG_Star* star);
void CPG_Star_Draw(CPG_Star* self, CPG_Display* display);
void CPG_Star_Update(CPG_Star* self);

#endif // CPG_STAR_H
