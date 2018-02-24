#include "../include/display.h"

CPG_Display* CPG_Display_Init(int width, int height, char* title) {
    CPG_Display* display = (CPG_Display*) malloc(sizeof(CPG_Display));

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
        return NULL;
    }

    display->window = SDL_CreateWindow(
            title, 
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN);
    display->renderer = SDL_CreateRenderer(
            display->window, 
            -1, 
            SDL_RENDERER_ACCELERATED);

    return display;
}

void CPG_Display_Clear(CPG_Display* self, CPG_Color color) {
    uint8_t r = color.r;
    uint8_t g = color.g;
    uint8_t b = color.b;
    uint8_t a = color.a;

    SDL_SetRenderDrawColor(self->renderer, r, g, b, a);
    SDL_RenderClear(self->renderer);
}

void CPG_Display_Destroy(CPG_Display* self) {
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    free(self);
}

void CPG_Display_DrawRect(CPG_Display* self, SDL_Rect* rect) {
    SDL_RenderFillRect(self->renderer, rect);
}

void CPG_Display_DrawText(CPG_Display* self, CPG_Text* text) {
    CPG_Text_Draw(text, self->renderer);
}

void CPG_Display_Refresh(CPG_Display* self) {
    SDL_RenderPresent(self->renderer);
}

void CPG_Display_SetColor(CPG_Display* self, CPG_Color color) {
    uint8_t r = color.r;
    uint8_t g = color.g;
    uint8_t b = color.b;
    uint8_t a = color.a;

    SDL_SetRenderDrawColor(self->renderer, r, g, b, a);
}
