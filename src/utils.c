#include "../include/utils.h"

#define CPG_SGN(a) (a > 0) - (a < 0)

int sgn(int v) {
    return CPG_SGN(v);
}

int sgnd(double v) {
    return CPG_SGN(v);
}

int sgnf(float v) {
    return CPG_SGN(v);
}
