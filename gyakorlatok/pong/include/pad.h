#ifndef PAD_H
#define PAD_H

/**
 * Pad position and size
 */
typedef struct Pad
{
    float position;
    float size;
} Pad;

/**
 * Move the pad to the given position.
 * @param position required position of the pad
 * @param limit last reachable point of the pad
 */
void move_pad(Pad* pad, float position, float limit);

#endif /* PAD_H */
