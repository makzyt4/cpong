#include <SDL2/SDL.h>
#include "../include/display.h"
#include "../include/text.h"

int main() {
    CPG_Display* display = CPG_Display_CreateNew(800, 600, "Test");
    CPG_Text t = {"Testing...", 50, 50, 1};
    CPG_Color white = {255, 255, 255, 255};
    CPG_Color blue = {0, 0, 255, 255};

    while (SDL_TRUE) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
        }

        CPG_Display_Clear(display, white);
        CPG_Display_ChangeRenderColor(display, blue);
        CPG_Display_DrawText(display, &t, 1);

        CPG_Display_Refresh(display);
        SDL_Delay(16);
    }
    return 0;
}
