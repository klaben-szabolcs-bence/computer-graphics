#include "callbacks.h"

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
    draw_hud();
    glPopMatrix();

    if (is_preview_visible)
    {
        show_texture_preview();
    }

    glutSwapBuffers();
}

void draw_hud()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef(0, 0, 0);
    glOrtho(0, screen.width, screen.height, 0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    set_material(&(scene.null_material));
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    if (!show_help)
    {
        write_text_to_screen("Press F1 to open the help menu!", scene.ascii_texture, 8, 8, 16);
    } else
    {
        write_text_to_screen("Use the mouse to look around",scene.ascii_texture, 8, 8, 16);
        write_text_to_screen("Drag and release to move", scene.ascii_texture, 8, 8 + 16, 16);
        write_text_to_screen("f: Make the ball glow", scene.ascii_texture, 8, 8 + 16 * 2, 16);
        write_text_to_screen("c: Toggle free-cam mode", scene.ascii_texture, 8, 8 + 16 * 3, 16);
        write_text_to_screen("r: Reset the ball", scene.ascii_texture, 8, 8 + 16 * 4, 16);
    }
    char pos_text[64];
    char dir_text[64];
    char spd_text[64];
    sprintf(pos_text,"Pos: %+07.3f %+07.3f %+07.3f", scene.golfball.position.x, scene.golfball.position.y, scene.golfball.position.z);
    sprintf(dir_text,"Dir: %+07.3f %+07.3f %+07.3f", scene.golfball.direction_vector.x, scene.golfball.direction_vector.y, scene.golfball.direction_vector.z);
    sprintf(spd_text,"Speed: %+07.3f / Velocity: %+07.3f", scene.golfball.speed, scene.golfball.velocity);
    write_text_to_screen(pos_text,scene.ascii_texture, screen.width - 28 * 12, screen.height - 3*12, 12);
    write_text_to_screen(dir_text,scene.ascii_texture, screen.width - 28 * 12, screen.height - 2*12, 12);
    write_text_to_screen(spd_text,scene.ascii_texture, screen.width - 35 * 12, screen.height - 12, 12);
    draw_powerbar(10, screen.height - 60, 100, 50);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    screen.height = height;
    screen.width = width;
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

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (drag_distance > 0) make_ball_move();
        drag_distance = 0.0;
    }

    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    // Handle moving
    if (scene.golfball.still && !camera.freecam)
    {
        double raw_drag_distance = (mouse_position.y - y) * -1;
        drag_distance += raw_drag_distance;
        
        // Clamp value
        if (drag_distance < 0)
        {
            drag_distance = 0;
        }
        if (drag_distance > MAX_DRAG_DISTANCE)
        {
            drag_distance = MAX_DRAG_DISTANCE;
        }
    }
    mouse_position.x = x;
    mouse_position.y = y;
    glutWarpPointer(640 / 2, 480 / 2);
}

void passive_motion(int x, int y)
{
    rotate_camera(&camera, (x - 640 / 2) / 10.0, -(y - 480 / 2) / 10.0);
    mouse_position.x = x;
    mouse_position.y = y;
    glutWarpPointer(640 / 2, 480 / 2);
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
    case 'r':
        reset_ball(&(scene.golfball));
        break;
    }

    glutPostRedisplay();
}

void special_keyboard(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_F1:
        show_help = !show_help;
        break;
    }
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

void make_ball_move()
{
    //Create vector between camera and ball
    vec3 look = create_vec3(
        scene.golfball.position.x - camera.position.x,
        scene.golfball.position.y - camera.position.y,
        scene.golfball.position.z - camera.position.z);

    //Make the velocity the drag distance
    scene.golfball.velocity = drag_distance;

    double cam_dist = sqrt(pow(look.x, 2) + pow(look.y, 2));

    //Normalize the vectors
    look.x = (look.x / cam_dist);
    look.y = (look.y / cam_dist);

    //Set the vectors
    scene.golfball.direction_vector.x = look.x;
    scene.golfball.direction_vector.y = look.y;

    //The direction vector may be inf, if we are looking at the ball from the top, so we just set it to 0
    if (scene.golfball.direction_vector.x > 1)
        scene.golfball.direction_vector.x = 0;
    if (scene.golfball.direction_vector.y > 1)
        scene.golfball.direction_vector.y = 0;
    if (scene.golfball.direction_vector.x < -1)
        scene.golfball.direction_vector.x = 0;
    if (scene.golfball.direction_vector.y < -1)
        scene.golfball.direction_vector.y = 0;
}

void draw_powerbar(int x, int y, int width, int height)
{
    glPushMatrix();
    // Colored power bar
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glVertex2f(x, y + height);

    //Change the color based on, if you can shoot
    if (scene.golfball.still)
        glColor3f(1, 0, 0);
    else
        glColor3f(0, 0, 0);

    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();

    double not_active_percent = 1 - (drag_distance / MAX_DRAG_DISTANCE);
    
    float z = 1.0;
    // Darkening "curtain" that gets pulled back based on the drag distance
    glBegin(GL_QUADS);
    glColor4f(0.0 , 0.0, 0.0, 0.5);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width - not_active_percent * width , y + height, z);
    glVertex3f(x + width - not_active_percent * width, y, z);
    glEnd();
    glPopMatrix();
}