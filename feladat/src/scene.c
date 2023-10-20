#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    //load_model(&(scene->cube), "golf_ball.obj");
    scene->skybox_texture = load_texture("skybox.png");

    Color ambient_material = create_color(0.55, 0, 0.55, 1);
    Color diffuse_material = create_color(0.755, 0.755, 0, 1);
    Color specular_material = create_color(0, 0.755, 0.755, 1);
    Color emission_material = create_color(0, 0, 0, 1);
    scene->invalid_material = create_material(ambient_material, diffuse_material, specular_material, 32.0, emission_material);

    GolfBall ball;
    ball.position = create_vec3(10, 0, 0);
    scene->golfball = ball;
    scene->golfball.glow = false;
    ambient_material = create_color(0, 0, 0, 1);
    diffuse_material = create_color(0.55, 0.55, 0.55, 1);
    specular_material = create_color(0.77, 0.77, 0.77, 1);
    emission_material = create_color(0, 0, 0, 1);
    scene->golfball.material = create_material(ambient_material, diffuse_material, specular_material, 1.0, emission_material);

    ambient_material = create_color(1, 1, 1, 1);
    diffuse_material = create_color(0, 0, 0, 1);
    specular_material = create_color(0, 0, 0, 1);
    emission_material = create_color(0, 0, 0, 1);
    scene->null_material = create_material(ambient_material, diffuse_material, specular_material, 0.0, emission_material);

    TexturedBrick unplayable_ground;
    unplayable_ground.rotation_angle = 0;
    unplayable_ground.position = create_vec3(-900, -900, -1);
    unplayable_ground.size = create_vec3(1800, 1800, 1);
    unplayable_ground.texture = load_texture("unplayable_ground.jpg");
    ambient_material = create_color(0.0215f,0.1745f,0.0215f,1.0f);
    diffuse_material = create_color(0.07568f,0.61424f,0.07568f,1.0f);
    specular_material = create_color(0.633f,0.727811f,0.633f,1.0f);
    unplayable_ground.material = create_material(ambient_material, diffuse_material, specular_material, 76.8f, emission_material);
    unplayable_ground.wrap_3d = false;
    unplayable_ground.texture_size[0] = 900;
    unplayable_ground.texture_size[1] = 901;
    scene->bricks[0] = unplayable_ground;

    scene->playable_ground_texture = load_texture("playable_ground.jpg");

}

void set_lighting(const Scene *scene)
{
    float ambient_light[] = {1.0f, 1.0f, 1.0f, 0.001f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 0.1f};
    float specular_light[] = {1.0f, 1.0f, 1.0f, 0.1f};
    float position[] = {10000.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    ambient_light[3] = 0.0f;
    diffuse_light[3] = 0.01f;
    specular_light[3] = 0.01f;
    position[0] = scene->golfball.position.x;
    position[1] = scene->golfball.position.y;
    position[2] = scene->golfball.position.z;

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void set_material(const Material *material)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_to_array(material->ambient).color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_to_array(material->diffuse).color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_to_array(material->specular).color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color_to_array(material->emission).color);
}

void draw_scene(const Scene *scene)
{

    set_material(&(scene->null_material));
    draw_origin();
    draw_skybox(scene);
    set_lighting(scene);
    //draw_model(&(scene->cube));

    int i;
    for (i = 0; i < N_BRICKS; ++i)
    {
        draw_textured_brick(&(scene->bricks[i]), scene);
    }

    set_material(&(scene->golfball.material));
    glPushMatrix();
    glTranslatef(scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
    glutSolidSphere(1, 36, 36);
    glPopMatrix();

    set_material(&(scene->invalid_material));

    glPushMatrix();
    glTranslatef(0, 5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, 0);
    glutSolidCube(2);
    glPopMatrix();
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

void draw_skybox(const Scene *scene)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture);
    const int D = 900 * 4;
    ArrayUV4 uv4;
    ArrayUV tiles, index;
    tiles.uv[0] = 4.0;
    tiles.uv[1] = 3.0;

    // All of them go clockwise, and from top-left

    // Top
    index.uv[0] = 1;
    index.uv[1] = 0;
    uv4 = get_uv(tiles, index);
    glBegin(GL_QUADS);
    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex3f(-D, D, -D);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex3f(D, D, -D);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex3f(D, -D, -D);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex3f(-D, -D, -D);
    glEnd();

    //Bottom
    index.uv[1] = 2;
    uv4 = get_uv(tiles, index);
    glBegin(GL_QUADS);
    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex3f(-D, -D, D);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex3f(D, -D, D);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex3f(D, D, D);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex3f(-D, D, D);
    glEnd();

    //Front
    index.uv[1] = 1;
    uv4 = get_uv(tiles, index);
    glBegin(GL_QUADS);
    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex3f(-D, -D, -D);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex3f(D, -D, -D);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex3f(D, -D, D);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex3f(-D, -D, D);
    glEnd();

    //Left
    index.uv[0] = 0;
    uv4 = get_uv(tiles, index);
    glBegin(GL_QUADS);
    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex3f(-D, D, -D);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex3f(-D, -D, -D);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex3f(-D, -D, D);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex3f(-D, D, D);
    glEnd();

    //Right
    index.uv[0] = 2;
    uv4 = get_uv(tiles, index);
    glBegin(GL_QUADS);
    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex3f(D, -D, -D);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex3f(D, D, -D);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex3f(D, D, D);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex3f(D, -D, D);
    glEnd();

    //Back
    index.uv[0] = 3;
    uv4 = get_uv(tiles, index);
    glBegin(GL_QUADS);
    glTexCoord2f(uv4.uv[0], uv4.uv[1]);
    glVertex3f(D, D, -D);
    glTexCoord2f(uv4.uv[2], uv4.uv[3]);
    glVertex3f(-D, D, -D);
    glTexCoord2f(uv4.uv[4], uv4.uv[5]);
    glVertex3f(-D, D, D);
    glTexCoord2f(uv4.uv[6], uv4.uv[7]);
    glVertex3f(D, D, D);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); //Unbind texture
    glPopMatrix();
}

void draw_textured_brick(const TexturedBrick *brick, const Scene *scene)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, brick->texture);
    set_material(&(brick->material));
    glTranslatef(brick->position.x, brick->position.y, brick->position.z);
    glRotatef(brick->rotation_angle, 0, 0, 0);
    if (brick->wrap_3d)
    {
        glBegin(GL_QUAD_STRIP);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1);
        glVertex3f(0, 0, brick->size.z);
        glTexCoord2f(1, 0);
        glVertex3f(brick->size.x, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(brick->size.x, 0, brick->size.z);
        glTexCoord2f(0, 0);
        glVertex3f(brick->size.x, brick->size.y, 0);
        glTexCoord2f(0, 1);
        glVertex3f(brick->size.x, brick->size.y, brick->size.z);
        glTexCoord2f(1, 0);
        glVertex3f(0, brick->size.y, 0);
        glTexCoord2f(1, 1);
        glVertex3f(0, brick->size.y, brick->size.z);
        glEnd();

        glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex3f(0, brick->size.y, brick->size.z);
        glTexCoord2f(0, 1);
        glVertex3f(brick->size.x, brick->size.y, brick->size.z);
        glTexCoord2f(1, 1);
        glVertex3f(brick->size.x, 0, brick->size.z);
        glTexCoord2f(0, 1);
        glVertex3f(0, 0, brick->size.z);
        glEnd();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0);
        glVertex3f(brick->size.x, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(brick->size.x, brick->size.y, 0);
        glTexCoord2f(1, 0);
        glVertex3f(0, brick->size.y, 0);
        glEnd();
    }
    else
    {
        float right_U = brick->size.x / brick->texture_size[0];
        float top_V_on_sides = brick->size.z / brick->texture_size[1];
        float top_V_on_top = brick->size.y / brick->texture_size[1];
        printf("%.3f\n", right_U);
        //Top
        glBegin(GL_QUADS);
        glTexCoord2f(0, top_V_on_top);
        glVertex3f(0, brick->size.y, brick->size.z);
        glTexCoord2f(right_U, top_V_on_top);
        glVertex3f(brick->size.x, brick->size.y, brick->size.z);
        glTexCoord2f(right_U, 0);
        glVertex3f(brick->size.x, 0, brick->size.z);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, brick->size.z);
        glEnd();

        //Bottom
        glBegin(GL_QUADS);
        glTexCoord2f(0, -top_V_on_top);
        glVertex3f(0, 0, brick->size.z);
        glTexCoord2f(right_U, -top_V_on_top);
        glVertex3f(brick->size.x, 0, 0);
        glTexCoord2f(right_U,0);
        glVertex3f(brick->size.x, brick->size.y, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, brick->size.y, 0);
        glEnd();

        //Front
        glBegin(GL_QUADS);
        glTexCoord2f(0, top_V_on_sides);
        glVertex3f(0, 0, brick->size.z);
        glTexCoord2f(right_U, top_V_on_sides);
        glVertex3f(brick->size.x, 0, brick->size.z);
        glTexCoord2f(right_U,0);
        glVertex3f(brick->size.x, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(brick->size.x, 0, 0);
        glEnd();

        //Left
        glBegin(GL_QUADS);
        glTexCoord2f(0, top_V_on_sides);
        glVertex3f(0, brick->size.y, brick->size.z);
        glTexCoord2f(right_U, top_V_on_sides);
        glVertex3f(0, 0, brick->size.z);
        glTexCoord2f(right_U,0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, brick->size.y, 0);
        glEnd();

        //Right
        glBegin(GL_QUADS);
        glTexCoord2f(0, top_V_on_sides);
        glVertex3f(brick->size.x, 0, brick->size.z);
        glTexCoord2f(right_U, top_V_on_sides);
        glVertex3f(brick->size.x, brick->size.y, brick->size.z);
        glTexCoord2f(right_U,0);
        glVertex3f(brick->size.x, brick->size.y, 0);
        glTexCoord2f(0, 0);
        glVertex3f(brick->size.x, 0, 0);
        glEnd();

        //Back
        glBegin(GL_QUADS);
        glTexCoord2f(0, top_V_on_sides);
        glVertex3f(brick->size.x, brick->size.y, brick->size.z);
        glTexCoord2f(right_U, top_V_on_sides);
        glVertex3f(0, brick->size.y, brick->size.z);
        glTexCoord2f(right_U,0);
        glVertex3f(0, brick->size.y, 0);
        glTexCoord2f(0, 0);
        glVertex3f(brick->size.x, brick->size.y, 0);
        glEnd();
    }
    glPopMatrix();
    set_material(&(scene->invalid_material));
    glBindTexture(GL_TEXTURE_2D, 0);
}