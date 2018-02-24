#ifndef SCREEN_H
#define SCREEN_H

#include "display.h"

typedef enum {
    CPG_LOOP,
    CPG_MAIN_MENU,
    CPG_OPTIONS,
    CPG_GAME,
    CPG_QUIT
} ExitCode;

typedef struct CPG_Screen CPG_Screen;

struct CPG_Screen {
    CPG_Display* display;
    void (*loop)(CPG_Screen*);
    ExitCode code;
};

CPG_Screen* CPG_Screen_Init(
        CPG_Display* display, 
        void (*loop)(CPG_Screen*));
void CPG_Screen_RunLoop(CPG_Screen* self);

#endif // SCREEN_H
