#ifndef CPG_DISPLAY_H
#define CPG_DISPLAY_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include "color.h"
#include "text.h"

#define CPG_SCREEN_WIDTH  800
#define CPG_SCREEN_HEIGHT 600
#define CPG_SCREEN_TITLE  "C Pong"
#define CPG_UI_SIZE 90

typedef struct {
   SDL_Window* window;
   SDL_Renderer* renderer;
} CPG_Display;

CPG_Display* CPG_Display_Init(int width, int height, char* title);
void CPG_Display_Clear(CPG_Display* self, CPG_Color color);
void CPG_Display_Destroy(CPG_Display* self);
void CPG_Display_DrawLine(CPG_Display* self, int x1, int y1, int x2, int y2);
void CPG_Display_DrawRect(CPG_Display* self, SDL_Rect* rect);
void CPG_Display_DrawText(CPG_Display* self, CPG_Text* text);
void CPG_Display_Refresh(CPG_Display* self);
void CPG_Display_SetColor(CPG_Display* self, CPG_Color color);

#endif // CPG_DISPLAY_H
