#ifndef CPG_COLOR_H
#define CPG_COLOR_H

#include <stdint.h>

typedef struct {
    uint8_t r, g, b, a;
} CPG_Color;

extern CPG_Color CPG_BLACK;
extern CPG_Color CPG_NAVY;
extern CPG_Color CPG_BLUE;
extern CPG_Color CPG_GREEN;
extern CPG_Color CPG_TEAL;
extern CPG_Color CPG_LIME;
extern CPG_Color CPG_AQUA;
extern CPG_Color CPG_MAROON;
extern CPG_Color CPG_PURPLE;
extern CPG_Color CPG_OLIVE;
extern CPG_Color CPG_GRAY;
extern CPG_Color CPG_DARKGRAY;
extern CPG_Color CPG_SILVER;
extern CPG_Color CPG_RED;
extern CPG_Color CPG_FUCHSIA;
extern CPG_Color CPG_YELLOW;
extern CPG_Color CPG_WHITE;

#endif // CPG_COLOR_H
