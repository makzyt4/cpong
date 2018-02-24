#include "../include/screen.h"

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
    switch (self->code) {
        // TODO Exit code handling
        default:
            break;
    }
}

void CPG_Screen_RunLoop(CPG_Screen* self) {
    CPG_Screen_Update(self);
    CPG_Screen_HandleExitCode(self);
}
