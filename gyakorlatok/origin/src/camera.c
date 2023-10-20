#include "camera.h"

#include <GL/glut.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = -0.06;
    camera->position.y = -0.08;
    camera->position.z = 0.02;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 30.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    camera->rotation_speed.x = 0.0;
    camera->rotation_speed.y = 0.0;
    camera->rotation_speed.z = 0.0;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
    camera->position.z += camera->speed.z * time;

    rotate_camera_horizontally(camera, camera->rotation_speed.z * time);
    rotate_camera_vertically(camera, camera->rotation_speed.x * time);

}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z = horizontal;
    camera->rotation.x = vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void rotate_camera_horizontally(Camera* camera, double rotation)
{
    
    rotate_camera(camera, camera->rotation.z + rotation, camera->rotation.x);
}

void rotate_camera_vertically(Camera* camera, double rotation)
{
    
    rotate_camera(camera, camera->rotation.z, camera->rotation.x + rotation);
}

void set_camera_horizontal_rotation_speed(Camera* camera, double speed)
{
    camera->rotation_speed.z = speed;
}

void set_camera_vertical_rotation_speed(Camera* camera, double speed)
{
    camera->rotation_speed.x = speed;
}

void print_camera_info(Camera* camera)
{
    printf("Camera Position: %.4f %.4f %.4f\n", camera->position.x, camera->position.y, camera->position.z);
    printf("Camera Rotation: %.4f %.4f %.4f\n", camera->rotation.x, camera->rotation.y, camera->rotation.z);
}