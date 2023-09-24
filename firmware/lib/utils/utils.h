#ifndef utils_h
#define utils_h
#include <arduino.h>

inline float clamp(float min, float val, float max) {
    if (val < min) return min;
    if (val > max) return max;
    else return val;
}
inline int sgn(float x) {
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}

#endif
