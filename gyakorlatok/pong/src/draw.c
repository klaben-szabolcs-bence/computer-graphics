#include "draw.h"

#include "GL/glut.h"

void draw_game(Game* game)
{
    float x1, x2, y1, y2;

    x1 = 0;
    x2 = 50;
    y1 = game->left_pad.position;
    y2 = y1 + game->left_pad.size;

    glBegin(GL_QUADS);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x1, y1);

    glColor3f(0.8, 0.2, 0.0);
    glVertex2f(x2, y1);

    glColor3f(1.0, 0.4, 0.0);
    glVertex2f(x2, y2);

    glColor3f(0.9, 0.3, 0.0);
    glVertex2f(x1, y2);

    glEnd();

    x1 = game->width - 50;
    x2 = game->width;
    y1 = game->right_pad.position;
    y2 = y1 + game->right_pad.size;

    glBegin(GL_QUADS);

    glColor3f(0.0, 0.1, 0.0);
    glVertex2f(x1, y1);

    glColor3f(0.0, 0.8, 0.2);
    glVertex2f(x2, y1);

    glColor3f(0.0, 1.0, 0.4);
    glVertex2f(x2, y2);

    glColor3f(0.0, 0.9, 0.2);
    glVertex2f(x1, y2);

    glEnd();

    glPushMatrix();
    glTranslatef(game->ball.x, game->ball.y, 0.0);
    glColor3f(1.0, 0.9, 0.8);
    glutSolidSphere(game->ball.radius, 8, 8);
    glPopMatrix();
}

