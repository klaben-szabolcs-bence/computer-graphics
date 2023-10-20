#include "model.h"
#include "draw.h"

#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include <stdio.h>

double rotateX;
double rotateY;

struct Model model;

typedef GLubyte Pixel[3]; /*represents red green blue*/

/**
 * Load texture from file and returns with the texture name.
 */
GLuint initialize_texture(char* filename)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    int width;
    int height;

    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
            (Pixel*)image);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);

    return texture_name;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    GLfloat light_position[] = {300, 0, -1000, 0.};
    GLfloat light_color[] = {0, 1, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_color);

    glRotatef(-rotateY, 1.0, 0, 0);
    glRotatef(rotateX, 0, 1.0, 0);

    draw_model(&model);

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    glViewport (0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void mouseHandler(int button, int state, int x, int y)
{
}

void motionHandler(int x, int y)
{
    rotateX = x;
    rotateY = y;

    glutPostRedisplay();
}

void idle()
{
}

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.2, 0.2, 0.2, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.0, -5000, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 1.0, 0.0  // up
    );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearDepth(1.0);

    initialize_texture("tiger.png");

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    rotateX = 0.0;
    rotateY = 0.0;

    load_model("tiger.obj", &model);
    print_model_info(&model);
    print_bounding_box(&model);

    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    int window = glutCreateWindow("GLUT Window");
    glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
