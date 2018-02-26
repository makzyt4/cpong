#include "../include/star.h"

void CPG_Star_Init(CPG_Star* star) {
    star->x1 = (((rand() % 201) - 100) / 100.0f) * 3.0f;
    star->y1 = (((rand() % 201) - 100) / 100.0f) * 3.0f;
    star->x2 = star->x1 * 3.0f;
    star->y2 = star->y1 * 3.0f;
}

void CPG_Star_Draw(CPG_Star* self, CPG_Display* display) {
    CPG_Display_SetColor(display, CPG_DARKGRAY);
    CPG_Display_DrawLine(
            display, 
            self->x1 + CPG_SCREEN_CENTER_X, 
            self->y1 + CPG_SCREEN_CENTER_Y, 
            self->x2 + CPG_SCREEN_CENTER_X, 
            self->y2 + CPG_SCREEN_CENTER_Y);
}

void CPG_Star_Update(CPG_Star* self) {
    self->x1 *= CPG_STAR_MOVEMENT_MULTIPLIER;
    self->y1 *= CPG_STAR_MOVEMENT_MULTIPLIER;
    self->x2 *= CPG_STAR_MOVEMENT_MULTIPLIER;
    self->y2 *= CPG_STAR_MOVEMENT_MULTIPLIER;

    if (self->x1 < -CPG_SCREEN_CENTER_X
            || self->y1 < -CPG_SCREEN_CENTER_Y
            || self->x1 > CPG_SCREEN_WIDTH
            || self->y1 > CPG_SCREEN_HEIGHT) {
        CPG_Star_Init(self);
    }
}
