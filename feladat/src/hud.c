#include "hud.h"

void draw_hud(Screen* screen, Scene* scene, Camera* camera)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef(0, 0, 0);
    glOrtho(0, screen->width, screen->height, 0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    set_material(&(scene->null_material));
    

    glPushMatrix();
    if (!show_help)
    {
        write_text_to_screen("Press F1 to open the help menu!", scene->ascii_texture, 8, 8, 16);
    } else
    {
        write_text_to_screen("Use the mouse to look around",scene->ascii_texture, 8, 8, 16);
        write_text_to_screen("Drag and release to move", scene->ascii_texture, 8, 8 + 16, 16);
        write_text_to_screen("f: Make the ball glow", scene->ascii_texture, 8, 8 + 16 * 2, 16);
        write_text_to_screen("c: Toggle free-cam mode", scene->ascii_texture, 8, 8 + 16 * 3, 16);
        write_text_to_screen("r: Reset the ball", scene->ascii_texture, 8, 8 + 16 * 4, 16);
    }
    char pos_text[64];
    char dir_text[64];
    char spd_text[64];
    char shots[12];
    sprintf(pos_text,"Pos: %+07.3f %+07.3f %+07.3f", scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
    sprintf(dir_text,"Dir: %+07.3f %+07.3f %+07.3f", scene->golfball.direction_vector.x, scene->golfball.direction_vector.y, scene->golfball.direction_vector.z);
    sprintf(spd_text,"Speed: %+07.3f / Velocity: %+07.3f", scene->golfball.speed, scene->golfball.velocity);
    sprintf(shots, "Shots: %03d", shots_taken);
    write_text_to_screen(pos_text,scene->ascii_texture, screen->width - 28 * 12, screen->height - 26 - 12 * 3, 12);
    write_text_to_screen(dir_text,scene->ascii_texture, screen->width - 28 * 12, screen->height - 26 - 12 * 2, 12);
    write_text_to_screen(spd_text,scene->ascii_texture, screen->width - 34 * 12, screen->height - 26 - 12 * 1, 12);
    write_text_to_screen(shots, scene->ascii_texture, screen->width - 10 * 24, screen->height - 20, 24);

    if (in_hole)
    {
        int x_center = screen->width / 2;
        int y_center = screen->height / 2;
        write_text_to_screen("Congratulations!", scene->ascii_texture, x_center - 16 * 16, y_center - 16, 32);
        write_text_to_screen("Try to get in with as few shots as possible!", scene->ascii_texture,
                            x_center - 44 * 6, y_center + 16, 12);
        
        Material base_material = scene->null_material;
        if (glutGet(GLUT_ELAPSED_TIME) % 16 >= 8)
        {
            base_material.ambient = create_color(1, 1, 0, 1);
            set_material(&base_material);
        } else {
            base_material.emission = create_color(1, 1, 1, 1);
            set_material(&base_material);
        }

        write_text_to_screen("Press r to try again.", scene->ascii_texture,
                            x_center - 21 * 6, y_center + 28, 12);
    }
    glDisable(GL_LIGHTING);
    draw_powerbar(10, screen->height - 60, 100, 50, can_move(scene, camera));
    glEnable(GL_LIGHTING);
    set_material(&(scene->invalid_material));
    glPopMatrix();
}

void draw_powerbar(int x, int y, int width, int height, bool can_move_calced)
{
    glPushMatrix();
    // Colored power bar
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glVertex2f(x, y + height);

    //Change the color based on, if you can shoot
    if (can_move_calced)
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

void write_char_to_screen(char character, GLuint ascii_map, int x, int y, int size)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ascii_map);
    float sd2 = size / 2;
    glTranslatef(x, y, 0);

    ArrayUV4 uv4;
    ArrayUV tiles, index;
    tiles.uv[0] = 18.0;
    tiles.uv[1] = 18.0;

    if (character > '~' || character < ' ')
    {
        character = '~' + 1;
    }

    character -= 32;
    index.uv[0] = character % (int)tiles.uv[0];
    index.uv[1] = character / (int)tiles.uv[0];

    uv4 = get_uv2(tiles, index);
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);

    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex2f(-sd2, -sd2);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex2f(sd2, -sd2);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex2f(sd2, sd2);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex2f(-sd2, sd2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void write_text_to_screen(const char *text, GLuint ascii_map, int x, int y, int size)
{
    unsigned int i;
    for (i = 0; i < strlen(text); ++i)
    {
        write_char_to_screen(text[i], ascii_map, x + (i * size), y, size);
    }
}