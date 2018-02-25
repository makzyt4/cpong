#ifndef CPG_BALL_H
#define CPG_BALL_H

#include "display.h"
#include "pad.h"
#include "utils.h"

#define CPG_BALL_SIZE         15
#define CPG_BALL_SPEEDDELTA   0.12f
#define CPG_BALL_STARTSPEED   7.0f
#define CPG_BALL_VERTSPEEDMAX 5.0f

typedef struct {
    float x, y;
    float velocityX, velocityY;
} CPG_Ball;

void CPG_Ball_Collide(CPG_Ball* self, CPG_Pad* pad);
void CPG_Ball_Draw(CPG_Ball* self, CPG_Display* display);
void CPG_Ball_Move(CPG_Ball* self);
void CPG_Ball_RandomizeDirection(CPG_Ball* self);
void CPG_Ball_Reset(CPG_Ball* self);

#endif // CPG_BALL_H
