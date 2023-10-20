#include "camera.h"
#include "scene.h"

#include <GL/glut.h>

#include <math.h>

void init_camera(Camera *camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 0.0;
    camera->rotation.x = 1.0;
    camera->rotation.y = 1.0;
    camera->rotation.z = 1.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    camera->follow_distance = 100;

    camera->freecam = false;
    is_preview_visible = FALSE;
}

void update_camera(Camera *camera, double time, Scene *scene)
{
    if (!camera->freecam)
    {
        double angle;
        double up_angle;

        angle = degree_to_radian(camera->rotation.z);
        up_angle = degree_to_radian(camera->rotation.x);

        camera->position = create_vec3(sin(angle) * sqrt(camera->follow_distance), sin(up_angle) * cbrt(camera->follow_distance), cos(angle) * sqrt(camera->follow_distance));
    }
    else
    {
        double angle;
        double side_angle;
        double up_angle;

        angle = degree_to_radian(camera->rotation.z + 90);
        side_angle = degree_to_radian(camera->rotation.z);
        up_angle = degree_to_radian(camera->rotation.x - 45);

        camera->position.x -= sin(angle) * camera->speed.y * time;
        camera->position.y -= cos(angle) * camera->speed.y * time;
        camera->position.x -= sin(side_angle) * camera->speed.x * time;
        camera->position.y -= cos(side_angle) * camera->speed.x * time;
        camera->position.z += sin(up_angle) * camera->speed.y * time;
        camera->position.z += cos(up_angle) * camera->speed.y * time;
    }
    
}

void set_view(const Camera *camera, const Scene *scene)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (!camera->freecam)
    {
        gluLookAt(camera->position.x, camera->position.y, camera->position.z, scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z, 0, 1, 0);
    }
    else
    {
        glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
        glRotatef(-(camera->rotation.y), 0, 1.0, 0);
        glRotatef((camera->rotation.z - 90), 0, 0, 1.0);
        glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
    }
}

void rotate_camera(Camera *camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    
    if (camera->rotation.z < 0)
    {
        camera->rotation.z += 720.0;
    }

    if (camera->rotation.z > 720.0)
    {
        camera->rotation.z -= 720.0;
    }

    if (camera->rotation.x < 0)
    {
        camera->rotation.x += 720.0;
    }

    if (camera->rotation.x > 720.0)
    {
        camera->rotation.x -= 720.0;
    }
    
}

void set_camera_speed(Camera *camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera *camera, double speed)
{
    camera->speed.x = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
