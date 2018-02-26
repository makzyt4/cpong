#include <SDL2/SDL.h>
#include <time.h>
#include "../include/display.h"
#include "../include/text.h"
#include "../include/main_screen.h"

int main() {
    srand(time(NULL));

    CPG_Display* display = CPG_Display_Init(
            CPG_SCREEN_WIDTH, 
            CPG_SCREEN_HEIGHT, 
            CPG_SCREEN_TITLE);
    CPG_Screen* screen = CPG_MainScreen_Init(display);

    while (screen->code != CPG_QUIT) {
        CPG_Screen_RunLoop(screen);
    }

    free(screen);
    CPG_Display_Destroy(display);

    return 0;
}
