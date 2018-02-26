#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"
#include "../include/pad.h"
#include "../include/ball.h"
#include "../include/star.h"

#define CPG_STAR_NUMBER 300

uint8_t scoreLeft, scoreRight;
CPG_Pad padPlayer1;
CPG_Pad padPlayer2;
CPG_Ball ball;
CPG_Star stars[CPG_STAR_NUMBER];

void CPG_GameScreen_DrawUiBar(CPG_Display* display) {
    CPG_Display_SetColor(display, CPG_WHITE);
    SDL_Rect rect = { 0, CPG_UI_SIZE - 10, CPG_SCREEN_WIDTH, 10 };
    CPG_Display_DrawRect(display, &rect);
}

void CPG_GameScreen_ResetPads() {
    padPlayer1 = (CPG_Pad) {
        50, 
        (CPG_UI_SIZE + CPG_SCREEN_HEIGHT - CPG_PAD_HEIGHT) / 2, 
        SDLK_w, 
        SDLK_s,
        SDL_FALSE
    };
    padPlayer2 = (CPG_Pad) {
        CPG_SCREEN_WIDTH - 50 - CPG_PAD_WIDTH, 
        (CPG_UI_SIZE + CPG_SCREEN_HEIGHT - CPG_PAD_HEIGHT) / 2, 
        SDLK_UP, 
        SDLK_DOWN,
        SDL_FALSE
    };
}

void CPG_GameScreen_Score() {
    if (ball.x > CPG_SCREEN_WIDTH) {
        scoreLeft++;
        CPG_Ball_Reset(&ball);
    } else if (ball.x + CPG_BALL_SIZE < 0) {
        scoreRight++;
        CPG_Ball_Reset(&ball);
    }
}

void CPG_GameScreen_DrawScore(CPG_Display* display) {
    char bufferL[16];
    sprintf(bufferL, "%d", scoreLeft);
    CPG_Text scoreTextLeft = {
        bufferL,
        100, 20, 
        CPG_SCOREFONT_SIZE
    };

    char bufferR[16];
    sprintf(bufferR, "%d", scoreRight);
    CPG_Text scoreTextRight = {
        bufferR,
        CPG_SCREEN_WIDTH - 100 - CPG_SCOREFONT_SIZE * 8, 20, 
        CPG_SCOREFONT_SIZE 
    };

    CPG_Display_SetColor(display, CPG_WHITE);
    CPG_Display_DrawText(display, &scoreTextLeft);
    CPG_Display_DrawText(display, &scoreTextRight);
}

void CPG_GameScreen_Loop(CPG_Screen* screen) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    screen->code = CPG_MAIN_MENU;
                }
                break;
            case SDL_QUIT:
                screen->code = CPG_QUIT;
                return;
        }

        CPG_Pad_HandleKeys(&padPlayer1, &event);
        CPG_Pad_HandleKeys(&padPlayer2, &event);
    }
    
    CPG_Display_Clear(screen->display, CPG_BLACK);

    int i;
    for (i = 0; i < CPG_STAR_NUMBER; i++) {
        CPG_Star_Update(&stars[i]);
        CPG_Star_Draw(&stars[i], screen->display);
    }

    CPG_GameScreen_DrawUiBar(screen->display);
    CPG_GameScreen_DrawScore(screen->display);

    CPG_Pad_Draw(&padPlayer1, screen->display);
    CPG_Pad_Draw(&padPlayer2, screen->display);
    CPG_Ball_Draw(&ball, screen->display);

    CPG_Ball_Collide(&ball, &padPlayer1);
    CPG_Ball_Collide(&ball, &padPlayer2);

    CPG_Pad_Move(&padPlayer1);
    CPG_Pad_Move(&padPlayer2);
    CPG_Ball_Move(&ball);

    CPG_GameScreen_Score();

    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

void CPG_GameScreen_Reset() {
    CPG_Ball_Reset(&ball);
    CPG_GameScreen_ResetPads();
}

CPG_Screen* CPG_GameScreen_Init(CPG_Display* display) {
    int i;
    for (i = 0; i < CPG_STAR_NUMBER; i++) {
        CPG_Star_Init(&stars[i]);
    }

    scoreLeft = 0;
    scoreRight = 0;
    CPG_GameScreen_Reset();
    
    return CPG_Screen_Init(display, CPG_GameScreen_Loop);
}
