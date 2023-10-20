#include "callbacks.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

struct
{
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera, &scene);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible)
    {
        show_texture_preview();
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;

    if ((button == 3) || (button == 4)) // It's a wheel event
    {
        if (state == GLUT_UP)
            return;
        if (button == 3)
            camera.distance--;
        else
            camera.distance++;

        if (camera.distance < 5)
            camera.distance = 5;
        if (camera.distance > 50)
            camera.distance = 50;
    }
}

void motion(int x, int y)
{
    //Handle moving
    if (scene.golfball.still && !camera.freecam)
    {
        double drag_distance = y - mouse_position.y;
        if (drag_distance > 0)
        {
            make_ball_move(drag_distance);
        }
    }
    mouse_position.x = x;
    mouse_position.y = y;
}

void passive_motion(int x, int y)
{
    rotate_camera(&camera, (x - 640 / 2) / 10.0, -(y - 480 / 2) / 10.0);
    glutWarpPointer(640 / 2, 480 / 2);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        set_camera_speed(&camera, 1);
        break;
    case 's':
        set_camera_speed(&camera, -1);
        break;
    case 'a':
        set_camera_side_speed(&camera, 1);
        break;
    case 'd':
        set_camera_side_speed(&camera, -1);
        break;
    case 't':
        if (is_preview_visible)
        {
            is_preview_visible = FALSE;
        }
        else
        {
            is_preview_visible = TRUE;
        }
        break;
    case 'c':
        camera.freecam = !camera.freecam;
        camera.rotation = create_vec3(0, 0, 0);
        if (camera.freecam)
        {
            camera.position = scene.golfball.position;
        }
        break;
    case 27:
        exit(0);
    case 'f':
        scene.golfball.glow = !scene.golfball.glow;

        if (scene.golfball.glow)
            glEnable(GL_LIGHT1);
        else
            glDisable(GL_LIGHT1);

        if (scene.golfball.glow)
            scene.golfball.material.emission = create_color(1, 1, 1, 1);
        else
            scene.golfball.material.emission = create_color(0, 0, 0, 1);
        break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;

    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time, &scene);
    update_game(&scene, elapsed_time);
    glutPostRedisplay();
}

void make_ball_move(double drag_distance)
{
    //Create vector between camera and ball
    vec3 look = create_vec3(
        scene.golfball.position.x - camera.position.x,
        scene.golfball.position.y - camera.position.y,
        scene.golfball.position.z - camera.position.z);

    //Normalize it
    look = create_vec3(look.x / abs(look.x), look.y / abs(look.y), look.z / abs(look.z));

    //Multiply it, by drag distance
    look = create_vec3(look.x * drag_distance, look.y * drag_distance, look.z * drag_distance);

    //Add it to the speed vector of the ball
    scene.golfball.speed.x += look.x;
    scene.golfball.speed.y += look.y;
    scene.golfball.speed.z += look.z;
}
