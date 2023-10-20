#include <GL/glut.h>

void init_opengl()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

