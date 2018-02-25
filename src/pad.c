#include "../include/pad.h"

void CPG_Pad_Draw(CPG_Pad* self, CPG_Display* display) {
    SDL_Rect rect = {
        self->x, 
        self->y,
        CPG_PAD_WIDTH,
        CPG_PAD_HEIGHT
    };
    CPG_Display_SetColor(display, CPG_WHITE);
    CPG_Display_DrawRect(display, &rect);
}

void CPG_Pad_HandleKeys(CPG_Pad* self, SDL_Event* event) {
    int key = event->key.keysym.sym;

    if (event->type == SDL_KEYDOWN) {
        if (key == self->upKey) {
            self->pressed |= 0x01;
        } else if (key == self->downKey) {
            self->pressed |= 0x02;
        }
    } else if (event->type == SDL_KEYUP) {
        if (key == self->upKey) {
            self->pressed &= ~0x01;
        } else if (key == self->downKey) {
            self->pressed &= ~0x02;
        }
    }
}

void CPG_Pad_Move(CPG_Pad* self) {
    if (self->pressed & 0x01) {
        self->velocityY -= CPG_PAD_VELOCITY_DELTA;
    } else if (self->pressed & 0x02) {
        self->velocityY += CPG_PAD_VELOCITY_DELTA;
    } else {
        self->velocityY *= CPG_PAD_VELOCITY_BRAKE;
    }

    if (self->velocityY < -CPG_PAD_VELOCITY_MAX) {
        self->velocityY = -CPG_PAD_VELOCITY_MAX;
    } else if (self->velocityY > CPG_PAD_VELOCITY_MAX) {
        self->velocityY = CPG_PAD_VELOCITY_MAX;
    }

    self->y += self->velocityY;

    if (self->y < 0) {
        self->y = 0;
        self->velocityY *= CPG_PAD_COLLISION_BRAKE;
    } else if (self->y + CPG_PAD_HEIGHT > CPG_SCREEN_HEIGHT) {
        self->y = CPG_SCREEN_HEIGHT - CPG_PAD_HEIGHT;
        self->velocityY *= CPG_PAD_COLLISION_BRAKE;
    }
}
