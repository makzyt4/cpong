#include "../include/game_screen.h"
#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"
#include "../include/pad.h"
#include "../include/ball.h"
#include "../include/star.h"
#include <time.h>

uint8_t score;
struct timespec start;
struct timespec now;

CPG_Pad padPlayer1;
CPG_Pad padPlayer2;

CPG_Ball ball;
CPG_Star stars[CPG_STAR_NUMBER];
CPG_GameState state;

uint8_t CPG_GameScreen_ScoreLeft() {
    return score >> 4;
}

uint8_t CPG_GameScreen_ScoreRight() {
    return score & 0x0f;
}

void CPG_GameScreen_AddScoreLeft() {
    uint8_t sc = CPG_GameScreen_ScoreLeft();
    score &= 0x0f;
    sc++;
    score |= sc << 4;
}

void CPG_GameScreen_AddScoreRight() {
    uint8_t sc = CPG_GameScreen_ScoreRight();
    score &= 0xf0;
    sc++;
    score |= sc;
}

void CPG_GameScreen_DrawBallLine(CPG_Display* display) {
    CPG_Display_SetColor(display, CPG_YELLOW);
    CPG_Display_DrawLine(
            display,
            ball.x + CPG_BALL_SIZE / 2,
            ball.y + CPG_BALL_SIZE / 2,
            ball.x + CPG_BALL_SIZE / 2 + ball.velocityX * 15.0f,
            ball.y + CPG_BALL_SIZE / 2 + ball.velocityY * 15.0f
    );
}

void CPG_GameScreen_DrawUiBar(CPG_Display* display) {
    CPG_Display_SetColor(display, CPG_WHITE);
    SDL_Rect rect = { 0, CPG_UI_SIZE - 10, CPG_SCREEN_WIDTH, 10 };
    CPG_Display_DrawRect(display, &rect);
}

void CPG_GameScreen_DrawDashedLine(CPG_Display* display) {
    CPG_Display_SetColor(display, CPG_WHITE);

    int y;
    for (y = CPG_UI_SIZE; y < CPG_SCREEN_HEIGHT; y += 20) {
        SDL_Rect rect = { (CPG_SCREEN_WIDTH - 10) / 2, y, 10, 10 };
        CPG_Display_DrawRect(display, &rect);
    }
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

void CPG_GameScreen_Reset() {
    CPG_Ball_Reset(&ball);
    CPG_GameScreen_ResetPads();
    clock_gettime(CLOCK_MONOTONIC, &start);
    state = CPG_STATE_COUNTING;
}

void CPG_GameScreen_Score() {
    if (ball.x > CPG_SCREEN_WIDTH) {
        CPG_GameScreen_AddScoreLeft();
        CPG_GameScreen_Reset();
    } else if (ball.x + CPG_BALL_SIZE < 0) {
        CPG_GameScreen_AddScoreRight();
        CPG_GameScreen_Reset();
    }

    const uint8_t sc1 = CPG_GameScreen_ScoreLeft();
    const uint8_t sc2 = CPG_GameScreen_ScoreRight();

    if (sc1 == CPG_WIN_POINTS || sc2 == CPG_WIN_POINTS) {
        state = CPG_STATE_GAMEOVER;
    }
}

void CPG_GameScreen_DrawScore(CPG_Display* display) {
    char bufferL[4];
    sprintf(bufferL, "%02d", CPG_GameScreen_ScoreLeft());
    CPG_Text scoreTextLeft = {
        bufferL,
        100, 20, 
        CPG_SCOREFONT_SIZE
    };

    char bufferR[4];
    sprintf(bufferR, "%02d", CPG_GameScreen_ScoreRight());
    CPG_Text scoreTextRight = {
        bufferR,
        CPG_SCREEN_WIDTH - 100 - CPG_SCOREFONT_SIZE * 16, 20, 
        CPG_SCOREFONT_SIZE 
    };

    CPG_Display_SetColor(display, CPG_WHITE);
    CPG_Display_DrawText(display, &scoreTextLeft);
    CPG_Display_DrawText(display, &scoreTextRight);
}

void CPG_GameScreen_Loop(CPG_Screen* screen) {
    clock_gettime(CLOCK_MONOTONIC, &now);
    long elapsedTime = now.tv_sec - start.tv_sec;

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

    if (state == CPG_STATE_COUNTING) {
        CPG_GameScreen_DrawBallLine(screen->display);
    }

    CPG_GameScreen_DrawUiBar(screen->display);
    CPG_GameScreen_DrawScore(screen->display);
    CPG_GameScreen_DrawDashedLine(screen->display);

    CPG_Pad_Draw(&padPlayer1, screen->display);
    CPG_Pad_Draw(&padPlayer2, screen->display);
    CPG_Ball_Draw(&ball, screen->display);

    if (state == CPG_STATE_PLAYING || state == CPG_STATE_COUNTING) {
        CPG_Pad_Move(&padPlayer1);
        CPG_Pad_Move(&padPlayer2);
    }

    if (state == CPG_STATE_PLAYING) {
        CPG_Ball_Collide(&ball, &padPlayer1);
        CPG_Ball_Collide(&ball, &padPlayer2);

        CPG_Ball_Move(&ball);

        CPG_GameScreen_Score();
    } else if (state == CPG_STATE_GAMEOVER) {
        const uint8_t result = CPG_GameScreen_ScoreLeft() == CPG_WIN_POINTS;
        CPG_Color color = result ? CPG_BLUE : CPG_RED;
        CPG_Text gameoverText = {
            result ? "Player 1 wins" : "Player 2 wins",
            (CPG_SCREEN_WIDTH - 13 * 3 * 8) / 2, 
            (CPG_SCREEN_HEIGHT - 20) / 2, 
            3
        };

        CPG_Display_SetColor(screen->display, color);
        CPG_Display_DrawText(screen->display, &gameoverText);
    } else if (state == CPG_STATE_COUNTING) {
        char countBuffer[5];
        sprintf(countBuffer, "%1ld...", CPG_START_TIME - elapsedTime);
        CPG_Text counterText = {
            countBuffer,
            (CPG_SCREEN_WIDTH - 4 * 3 * 8) / 2, 
            (CPG_SCREEN_HEIGHT - 20) / 2, 
            3
        };

        CPG_Display_SetColor(screen->display, CPG_SILVER);
        CPG_Display_DrawText(screen->display, &counterText);

        if (CPG_START_TIME - elapsedTime == 0) {
            state = CPG_STATE_PLAYING;
        }
    }

    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

CPG_Screen* CPG_GameScreen_Init(CPG_Display* display) {
    int i;
    for (i = 0; i < CPG_STAR_NUMBER; i++) {
        CPG_Star_Init(&stars[i]);
    }

    score = 0;

    CPG_GameScreen_Reset();
    
    return CPG_Screen_Init(display, CPG_GameScreen_Loop);
}
