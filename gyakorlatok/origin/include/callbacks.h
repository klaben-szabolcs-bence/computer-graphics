#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"

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
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * @brief Call after a mouse event
 * 
 * @param button Which button was clicked: GLUT_#_BUTTON, where # can be LEFT, RIGHT and MIDDLE.
 * @param state Which state the button was pressed: GLUT_UP or GLUT_DOWN.
 * @param x The x position on the window.
 * @param y The y position on the window.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after keyboard release event.
 */
void keyboard_up(unsigned char key, int x, int y);

/**
 * Call when there is no other event.
 */
void idle();

#endif // CALLBACKS_H

