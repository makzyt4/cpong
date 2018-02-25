#ifndef CPG_TEXT_H
#define CPG_TEXT_H

#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct {
    char* text;
    int16_t x, y;
    uint8_t fontSize;
} CPG_Text;

void CPG_Text_Draw(CPG_Text* text, SDL_Renderer* renderer);

#endif // CPG_TEXT_H
