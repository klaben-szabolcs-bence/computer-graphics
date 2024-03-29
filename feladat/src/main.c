#include "callbacks.h"
#include "init.h"

#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Set the callbacks for GLUT.
 */
void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passive_motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special_keyboard);
    glutIdleFunc(idle);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    int window;

    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Minigolf Prototype");
    glutSetWindow(window);
    glutSetCursor(GLUT_CURSOR_NONE);

    init_opengl();
    init_scene(&scene);
    init_camera(&camera);
    init_game(&scene);

    time_t t;
    srand((unsigned) time(&t));

    set_callbacks();

    glutMainLoop();

    return 0;
}