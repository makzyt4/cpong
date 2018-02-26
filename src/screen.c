#include "../include/screen.h"
#include "../include/game_screen.h"
#include "../include/main_screen.h"
#include "../include/help_screen.h"

CPG_Screen* CPG_Screen_Init(
        CPG_Display* display, 
        void (*loop)(CPG_Screen*)) {

   CPG_Screen* screen = (CPG_Screen*) malloc(sizeof(CPG_Screen)); 
   screen->display = display;
   screen->loop = loop;
   screen->code = CPG_LOOP;
   
   return screen;
}

void CPG_Screen_Update(CPG_Screen* self) {
    while (self->code == CPG_LOOP) {
        self->loop(self);
    }
}

void CPG_Screen_HandleExitCode(CPG_Screen* self) {
    CPG_Screen* newScreen;

    if (self->code == CPG_GAME) {
        newScreen = CPG_GameScreen_Init(self->display);
        self->loop = newScreen->loop;
        self->code = CPG_LOOP;
    } else if (self->code == CPG_MAIN_MENU) {
        newScreen = CPG_MainScreen_Init(self->display);
        self->loop = newScreen->loop;
        self->code = CPG_LOOP;
    } else if (self->code == CPG_HELP) {
        newScreen = CPG_HelpScreen_Init(self->display);
        self->loop = newScreen->loop;
        self->code = CPG_LOOP;
    }
}

void CPG_Screen_RunLoop(CPG_Screen* self) {
    CPG_Screen_Update(self);
    CPG_Screen_HandleExitCode(self);
}
