#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"
#include "game.h"
#include <stdlib.h>

#include <GL/glut.h>

/**
 * Scene
 */
Scene scene;

/**
 * Camera
 */
Camera camera;

/**
 * Drag distance with the mouse
 */
double drag_distance;
#define MAX_DRAG_DISTANCE 10

/**
 * Toggle for showing help message
 */
bool show_help;

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse button event.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call after mouse event.
 */
void motion(int x, int y);

/**
 * Call after mouse movement event.
 */
void passive_motion(int x, int y);

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after keyboard release event.
 */
void keyboard_up(unsigned char key, int x, int y);

/**
 * Call after special keyboard event.
 */
void special_keyboard(int key, int x, int y);

/**
 * Call when there is no other event.
 */
void idle();

/**
 * Make the ball move, once we have finalized drag distance
 */
void make_ball_move();

/**
 * Draw HUD
 */
void draw_hud();

/**
 * Draws the powerbar for the HUD
 */
void draw_powerbar(int x, int y, int width, int height);


#endif /* CALLBACKS_H */
