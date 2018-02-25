#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"
#include "../include/pad.h"
#include "../include/ball.h"

CPG_Pad padPlayer1 =  {
    50, 
    (CPG_UI_SIZE + CPG_SCREEN_HEIGHT - CPG_PAD_HEIGHT) / 2, 
    SDLK_w, 
    SDLK_s,
    SDL_FALSE
};
CPG_Pad padPlayer2 = {
    CPG_SCREEN_WIDTH - 50 - CPG_PAD_WIDTH, 
    (CPG_UI_SIZE + CPG_SCREEN_HEIGHT - CPG_PAD_HEIGHT) / 2, 
    SDLK_UP, 
    SDLK_DOWN,
    SDL_FALSE
};
CPG_Ball ball;

void CPG_GameScreen_Loop(CPG_Screen* screen) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                screen->code = CPG_QUIT;
                return;
        }

        CPG_Pad_HandleKeys(&padPlayer1, &event);
        CPG_Pad_HandleKeys(&padPlayer2, &event);
    }
    
    CPG_Display_Clear(screen->display, CPG_BLACK);

    CPG_Pad_Draw(&padPlayer1, screen->display);
    CPG_Pad_Draw(&padPlayer2, screen->display);
    CPG_Ball_Draw(&ball, screen->display);

    CPG_Ball_Collide(&ball, &padPlayer1);
    CPG_Ball_Collide(&ball, &padPlayer2);

    CPG_Pad_Move(&padPlayer1);
    CPG_Pad_Move(&padPlayer2);
    CPG_Ball_Move(&ball);

    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

void CPG_GameScreen_Reset() {
    CPG_Ball_Reset(&ball);
}

CPG_Screen* CPG_GameScreen_Init(CPG_Display* display) {
    CPG_GameScreen_Reset();
    return CPG_Screen_Init(display, CPG_GameScreen_Loop);
}
