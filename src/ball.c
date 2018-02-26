#include "../include/ball.h"
#include <math.h>

void CPG_Ball_Collide(CPG_Ball* self, CPG_Pad* pad) {
    uint8_t flags = 0;
    // Top
    flags |= (self->y + CPG_BALL_SIZE >= pad->y)  << 0;
    // Bottom
    flags |= (self->y <= pad->y + CPG_PAD_HEIGHT) << 1;
    // Left
    flags |= (self->x + CPG_BALL_SIZE >= pad->x)  << 2;
    // Right
    flags |= (self->x <= pad->x + CPG_PAD_WIDTH)  << 3;
    // Top inner collision
    flags |= (self->y + CPG_BALL_SIZE >= pad->y + fabs(self->velocityY))  << 4;
    // Bottom inner collision
    flags |= (self->y <= pad->y + CPG_PAD_HEIGHT - fabs(self->velocityY)) << 5;

    // If all flags are set to true then there is a collision.
    if ((flags & 0xf) == 0xf) {
        const float ballCenter = self->y + CPG_BALL_SIZE / 2.0f;
        const float padCenter = pad->y + CPG_PAD_HEIGHT / 2.0f;
        const float verticalVelocity = (ballCenter - padCenter) / (CPG_PAD_HEIGHT / 2.0f);

        self->velocityX += sgn(self->velocityX) * CPG_BALL_SPEEDDELTA;
        self->velocityX *= -1;
        self->velocityY = verticalVelocity * -CPG_BALL_VERTSPEEDMAX;

        /*
        if (((self->velocityY > 0) && (flags & 0x10))
                || ((self->velocityY < 0) && (flags & 0x20))) {
            self->velocityY *= -1;
        }
        */
    }
}

void CPG_Ball_Draw(CPG_Ball* self, CPG_Display* display) {
    SDL_Rect rect = {
        self->x, 
        self->y,
        CPG_BALL_SIZE,
        CPG_BALL_SIZE
    };
    CPG_Display_SetColor(display, CPG_WHITE);
    CPG_Display_DrawRect(display, &rect);
}

void CPG_Ball_Move(CPG_Ball* self) {
    self->x += self->velocityX;
    self->y += self->velocityY;

    if (self->y <= CPG_UI_SIZE) {
        self->y = CPG_UI_SIZE;
        self->velocityY *= -1;
    } else if (self->y + CPG_BALL_SIZE >= CPG_SCREEN_HEIGHT) {
        self->y = CPG_SCREEN_HEIGHT - CPG_BALL_SIZE;
        self->velocityY *= -1;
    }
}

void CPG_Ball_Reset(CPG_Ball* self) {
    self->x = (CPG_SCREEN_WIDTH - CPG_BALL_SIZE) / 2.0f;
    self->y = (CPG_SCREEN_HEIGHT - CPG_BALL_SIZE) / 2.0f;

    self->velocityX = (((rand() % 2) * 2) - 1) * CPG_BALL_STARTSPEED;
    self->velocityY = (((rand() % 201) - 100) / 100.f) * CPG_BALL_VERTSPEEDMAX;
}
