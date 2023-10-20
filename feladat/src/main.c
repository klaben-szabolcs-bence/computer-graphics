#include "callbacks.h"
#include "init.h"

#include <GL/glut.h>

#include <stdio.h>

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

    window = glutCreateWindow("Scene with a camera");
    glutSetWindow(window);
    glutSetCursor(GLUT_CURSOR_NONE);

    init_opengl();
    init_scene(&scene);
    init_camera(&camera);
    drag_distance = 0.0;
    show_help = false;
    in_hole = false;
    shots_taken = 0;
    set_callbacks();

    glutMainLoop();

    return 0;
}