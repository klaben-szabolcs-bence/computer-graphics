#include "scene.h"

#include <GL/glut.h>

void init_scene(Scene* scene)
{
}

void draw_scene(const Scene* scene)
{
    draw_origin();
    draw_pyramid(.2, .2, .2, .1, .1);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();    
}

void draw_pyramid(double x, double y, double z, double width, double height)
{
    int i = 0;
    double h_width = width/2;
    double baseline = z - height;
    const double color_multiplier = 1000/255;

    glBegin(GL_TRIANGLE_FAN);

    glColor3f((int)(x) % 255 * color_multiplier, (int)y % 255 * color_multiplier, (int)z % 255 * color_multiplier);
    glVertex3f(x, y, z);
    glColor3f( (int)(x + 10) % 255, (int)y % 255, (int)z % 255);
    glVertex3f(x - h_width, y - h_width, baseline);
    glColor3f((int)x % 255, (int)(y + 10) % 255, (int)z % 255);
    glVertex3f(x + h_width, y - h_width, baseline);
    glColor3f((int)x % 255, (int)y % 255, (int)(z + 10) % 255);
    glVertex3f(x + h_width, y + h_width, baseline);
    glColor3f((int)(x - 10) % 255, (int)(y - 10) % 255, (int)(z - 10)  % 255);
    glVertex3f(x - h_width, y + h_width, baseline);

    glEnd();

    glBegin(GL_QUADS);

    glVertex3f(x - h_width, y + h_width, baseline);
    glColor3f((int)x % 255, (int)y % 255, (int)(z + 10) % 255);
    glVertex3f(x + h_width, y + h_width, baseline);
    glColor3f((int)x % 255, (int)(y + 10) % 255, (int)z % 255);
    glVertex3f(x + h_width, y - h_width, baseline);
    glColor3f((int)(x + 10) % 255, (int)y % 255, (int)z % 255);
    glVertex3f(x - h_width, y - h_width, baseline);

    glEnd();
}