#include "../include/text.h"
#include "../include/font.h"

void CPG_Text_DrawCharacter(
        SDL_Renderer* renderer,
        char c,
        int16_t x, int16_t y,
        uint8_t fontSize) {
    
    if (c < 0x20 || c > 0x7f) {
        c = 0x20;
    }

    uint8_t i, j;
    const uint64_t ch = ascii_font[c - 0x20];

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (ch & (1LL << ((7 - j) + 8 * (7 - i)))) {
                SDL_Rect r = {
                    x + i * fontSize,
                    y + j * fontSize,
                    fontSize, fontSize
                };
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }
}

void CPG_Text_Draw(CPG_Text* text, SDL_Renderer* renderer) {
    char* c = text->text;
    int16_t x = text->x;
    int16_t y = text->y;

    while (*c) {
        switch (*c) {
            case '\n':
                x = text->x;
                y += text->fontSize * 8;
                break;
            case '\t':
                x += text->fontSize * 32;
                break;
            default:
                CPG_Text_DrawCharacter(renderer, *c, x, y, text->fontSize);
                x += 8 * text->fontSize;
        }

        c++;
    }
}
