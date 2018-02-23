#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct {
    char* text;
    int16_t x, y;
    uint8_t fontSize;
} Text;

void Text_Draw(Text* text, SDL_Renderer* renderer);

#endif // TEXT_H
