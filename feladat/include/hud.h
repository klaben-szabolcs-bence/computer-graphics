#ifndef HUD_H
#define HUD_H

#include "scene.h"
#include "camera.h"

#include <GL/glut.h>

#define MAX_DRAG_DISTANCE 10

/**
 * Toggle for showing help message
 */
bool show_help;

/**
 * Drag distance with the mouse
 */
double drag_distance;

/**
 * Draw HUD
 */
void draw_hud(Screen* screen, Scene* scene);

/**
 * Draws the powerbar for the HUD
 */
void draw_powerbar(Scene* scene, int x, int y, int width, int height);

/**
 * Writes the character to the screen
 */
void write_char_to_screen(char character, GLuint ascii_map, int x, int y, int size);

/**
 * Writes the text on the screen
 */
void write_text_to_screen(const char* text, GLuint ascii_map, int x, int y, int size);

#endif /* HUD_H */