#ifndef CPG_SCREEN_H
#define CPG_SCREEN_H

#include "display.h"

#define CPG_MENUS_FONTSIZE 3
#define CPG_SCOREFONT_SIZE 5
#define CPG_LOGO_SIZE      7

typedef enum {
    CPG_LOOP,
    CPG_MAIN_MENU,
    CPG_HELP,
    CPG_GAME,
    CPG_QUIT
} CPG_ExitCode;

typedef struct CPG_Screen {
    CPG_Display* display;
    void (*loop)(struct CPG_Screen*);
    CPG_ExitCode code;
} CPG_Screen;

CPG_Screen* CPG_Screen_Init(
        CPG_Display* display, 
        void (*loop)(struct CPG_Screen*));
void CPG_Screen_RunLoop(CPG_Screen* self);

#endif // CPG_SCREEN_H
