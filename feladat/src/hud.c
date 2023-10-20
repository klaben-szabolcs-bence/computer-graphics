#include "hud.h"

void draw_hud(Screen* screen, Scene* scene)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef(0, 0, 0);
    glOrtho(0, screen->width, screen->height, 0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    set_material(&(scene->null_material));
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
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
    sprintf(pos_text,"Pos: %+07.3f %+07.3f %+07.3f", scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
    sprintf(dir_text,"Dir: %+07.3f %+07.3f %+07.3f", scene->golfball.direction_vector.x, scene->golfball.direction_vector.y, scene->golfball.direction_vector.z);
    sprintf(spd_text,"Speed: %+07.3f / Velocity: %+07.3f", scene->golfball.speed, scene->golfball.velocity);
    write_text_to_screen(pos_text,scene->ascii_texture, screen->width - 28 * 12, screen->height - 3*12, 12);
    write_text_to_screen(dir_text,scene->ascii_texture, screen->width - 28 * 12, screen->height - 2*12, 12);
    write_text_to_screen(spd_text,scene->ascii_texture, screen->width - 35 * 12, screen->height - 12, 12);
    draw_powerbar(scene, 10, screen->height - 60, 100, 50);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void draw_powerbar(Scene* scene, int x, int y, int width, int height)
{
    glPushMatrix();
    // Colored power bar
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glVertex2f(x, y + height);

    //Change the color based on, if you can shoot
    if (scene->golfball.still)
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