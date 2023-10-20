#include "pad.h"

void move_pad(Pad* pad, float position, float limit)
{
    if (position < 0.0) {
        pad->position = 0.0;
    } else if (position + pad->size > limit) {
        pad->position = limit - pad->size;
    } else {
        pad->position = position;
    }
}

