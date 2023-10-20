/**
 * NOTE: For further callbacks see:
 *       https://www.opengl.org/resources/libraries/glut/spec3/node45.html
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "game.h"

#include <GL/glut.h>

/**
 * Game state object
 */
Game game;

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse event.
 */
void motion(int x, int y);

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call when there is no other event.
 */
void idle();

#endif /* CALLBACKS_H */
