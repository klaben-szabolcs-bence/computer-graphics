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
    scene->invalid_material =
        create_material(ambient_material, diffuse_material, specular_material, 32.0, emission_material);

    GolfBall ball;
    ball.position = create_vec3(10, 0, 2);
    scene->golfball = ball;
    scene->golfball.glow = false;
    ball.speed = create_vec3(0.0f, 0.0f, 0.0f);
    ball.on_ground = false;
    ball.still = false;
    ambient_material = create_color(0, 0, 0, 1);
    diffuse_material = create_color(0.55, 0.55, 0.55, 1);
    specular_material = create_color(0.77, 0.77, 0.77, 1);
    emission_material = create_color(0, 0, 0, 1);
    scene->golfball.material =
        create_material(ambient_material, diffuse_material, specular_material, 1.0, emission_material);

    ambient_material = create_color(1, 1, 1, 1);
    diffuse_material = create_color(0, 0, 0, 1);
    specular_material = create_color(0, 0, 0, 1);
    emission_material = create_color(0, 0, 0, 1);
    scene->null_material =
        create_material(ambient_material, diffuse_material, specular_material, 0.0, emission_material);

    TexturedBrick unplayable_ground;
    unplayable_ground.rotation_angle = 0;
    unplayable_ground.position = create_vec3(-900, -900, -1);
    unplayable_ground.size = create_vec3(1800, 1800, 1);
    unplayable_ground.texture = load_texture("unplayable_ground.jpg");
    ambient_material = create_color(0.0215f, 0.1745f, 0.0215f, 1.0f);
    diffuse_material = create_color(0.07568f, 0.61424f, 0.07568f, 1.0f);
    specular_material = create_color(0.633f, 0.727811f, 0.633f, 1.0f);
    unplayable_ground.material =
        create_material(ambient_material, diffuse_material, specular_material, 76.8f, emission_material);

    unplayable_ground.wrap_3d = false;
    unplayable_ground.texture_size[0] = 900;
    unplayable_ground.texture_size[1] = 900;
    unplayable_ground.tiled_texture = true;
    scene->bricks[0] = unplayable_ground;

    scene->playable_ground_texture = load_texture("playable_ground.jpg");
    ambient_material = create_color(0.1215f, 0.2745f, 0.1215f, 1.0f);
    diffuse_material = create_color(0.17568f, 0.71424f, 0.17568f, 1.0f);
    specular_material = create_color(0.733f, 0.827811f, 0.733f, 1.0f);
    scene->playable_ground_material =
        create_material(ambient_material, diffuse_material, specular_material, 76.8f, emission_material);

    scene->wooden_texture = load_texture("wood.png");
    ambient_material = create_color(0.1f, 0.1f, 0.1f, 1.0f);
    diffuse_material = create_color(0.63529f, 0.4705f, 0.3843f, 1.0f);
    specular_material = create_color(0.63529f, 0.4705f, 0.3843f, 1.0f);
    scene->wooden_material =
        create_material(ambient_material, diffuse_material, specular_material, 160.0f, emission_material);

    TexturedBrick playable_ground;
    playable_ground.rotation_angle = 0;
    playable_ground.position = create_vec3(-25, -25, 0);
    playable_ground.size = create_vec3(50, 50, 1);
    playable_ground.texture = scene->playable_ground_texture;
    playable_ground.material = scene->playable_ground_material;
    playable_ground.wrap_3d = false;
    playable_ground.tiled_texture = true;
    playable_ground.texture_size[0] = 500;
    playable_ground.texture_size[1] = 500;
    scene->bricks[1] = playable_ground;

    TexturedBrick wooden_brick;
    wooden_brick.rotation_angle = 0;
    wooden_brick.position = create_vec3(-25, 25, 0);
    wooden_brick.size = create_vec3(51, 1, 3);
    wooden_brick.texture = scene->wooden_texture;
    wooden_brick.material = scene->wooden_material;
    wooden_brick.wrap_3d = false;
    wooden_brick.tiled_texture = true;
    wooden_brick.texture_size[0] = 4096;
    wooden_brick.texture_size[1] = 4096;
    scene->bricks[2] = wooden_brick;

    wooden_brick.position = create_vec3(25, -26, 0);
    wooden_brick.size = create_vec3(1, 51, 3);
    scene->bricks[3] = wooden_brick;

    wooden_brick.position = create_vec3(-26, -26, 0);
    wooden_brick.size = create_vec3(51, 1, 3);
    scene->bricks[4] = wooden_brick;

    wooden_brick.position = create_vec3(-26, -25, 0);
    // Direkt 1 magasságú, hogy tesztelni lehessen, mi van ha OOB a labda.
    wooden_brick.size = create_vec3(1, 26, 1);
    scene->bricks[5] = wooden_brick;

    scene->ascii_texture = load_ogl_texture("ascii.png");
    
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
    if (brick->tiled_texture)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    set_material(&(brick->material));
    glBindTexture(GL_TEXTURE_2D, brick->texture);
    glPushMatrix();
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
        float right_U = brick->size.x / brick->texture_size[0] * 50;
        float top_V_on_sides = brick->size.z / brick->texture_size[1] * 50;
        float top_V_on_top = brick->size.y / brick->texture_size[1] * 50;
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
        glVertex3f(0, 0, 0);
        glTexCoord2f(right_U, -top_V_on_top);
        glVertex3f(brick->size.x, 0, 0);
        glTexCoord2f(right_U, 0);
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
        glTexCoord2f(right_U, 0);
        glVertex3f(brick->size.x, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glEnd();

        //Left
        glBegin(GL_QUADS);
        glTexCoord2f(0, top_V_on_sides);
        glVertex3f(0, brick->size.y, brick->size.z);
        glTexCoord2f(right_U, top_V_on_sides);
        glVertex3f(0, 0, brick->size.z);
        glTexCoord2f(right_U, 0);
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
        glTexCoord2f(right_U, 0);
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
        glTexCoord2f(right_U, 0);
        glVertex3f(0, brick->size.y, 0);
        glTexCoord2f(0, 0);
        glVertex3f(brick->size.x, brick->size.y, 0);
        glEnd();
    }
    glPopMatrix();
    set_material(&(scene->invalid_material));
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void update_game(Scene *scene, double delta)
{
    //printf("Speed: %f %f %f\n", scene->golfball.speed.x, scene->golfball.speed.y, scene->golfball.speed.z);
    //printf("Pos: %f %f %f\n", scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);

    //Basic forces
    scene->golfball.position.x += scene->golfball.speed.x * delta;
    scene->golfball.position.y += scene->golfball.speed.y * delta;
    scene->golfball.position.z += scene->golfball.speed.z * delta;

    scene->golfball.speed.x /= 2.0f;
    scene->golfball.speed.y /= 2.0f;

    if (abs(scene->golfball.speed.x) < 0.1f)
        scene->golfball.speed.x = 0.0f;
    if (abs(scene->golfball.speed.y) < 0.1f)
        scene->golfball.speed.y = 0.0f;
    if (abs(scene->golfball.speed.z) < 0.1f)
        scene->golfball.speed.z = 0.0f;
    
    // Apply gravity
    if (scene->golfball.speed.z > -10.0f && !scene->golfball.on_ground)
        scene->golfball.speed.z += -1.0f;

    // Mitigate weird stuff
    if (scene->golfball.speed.z > 100000.0f)
        scene->golfball.speed.z = 0.0f;

    // Out of Out of Bounds
    if (scene->golfball.position.x > 900 || scene->golfball.position.x < -900 ||
        scene->golfball.position.y > 900 || scene->golfball.position.y < -900 ||
        scene->golfball.position.z < -1.0f || scene->golfball.position.z > 900)
    {
        scene->golfball.position.x = 0;
        scene->golfball.position.y = 0;
        scene->golfball.position.z = 10;
    }

    scene->golfball.on_ground = false;

    int colliding_brick = is_colliding_with_brick(scene);
    if (colliding_brick > -1 )
    {
        float distance[6];
        distance[0] = scene->golfball.position.x - scene->bricks[colliding_brick].position.x;
        distance[1] = scene->golfball.position.x - (scene->bricks[colliding_brick].position.x + scene->bricks[colliding_brick].size.x);
        distance[2] = scene->golfball.position.y - scene->bricks[colliding_brick].position.y;
        distance[3] = scene->golfball.position.y - (scene->bricks[colliding_brick].position.y + scene->bricks[colliding_brick].size.y);
        distance[4] = scene->golfball.position.z - scene->bricks[colliding_brick].position.z;
        distance[5] = scene->golfball.position.z - (scene->bricks[colliding_brick].position.z + scene->bricks[colliding_brick].size.z);

        

        int min_distance = fmin(abs(distance[0]), abs(distance[1]));

        int i;
        for (i = 2; i < 6; ++i)
        {
            min_distance = fmin(min_distance, abs(distance[i]));    
        }

        if (min_distance == abs(distance[0]) || min_distance == abs(distance[1]))
        {
            // Collission on left side
            // Collission on right side

            scene->golfball.speed.x *= -1.0f;

            
            if (scene->golfball.speed.x < 0)
            {
                scene->golfball.position.x -= distance[0] + 0.5f;
                printf("Collision with %d on LEFT.\n", colliding_brick);
            }
            else
            {
                scene->golfball.position.x -= distance[1] - 0.5f;
                printf("Collision with %d on RIGHT.\n", colliding_brick);
            }
            
        }
        else if (min_distance == abs(distance[2]) || min_distance == abs(distance[3]))
        {
            //Collission on front side
            //Collission on back side

            scene->golfball.speed.y *= -1.0f;

            
            if (scene->golfball.speed.y < 0)
            {
                scene->golfball.position.y -= distance[2] + 0.5f;
                printf("Collision with %d on FRONT.\n", colliding_brick);
            }
            else
            {
                scene->golfball.position.y -= distance[3] - 0.5f;
                printf("Collision with %d on BACK.\n", colliding_brick);
            }
            
        }
        else
        {
            //Collision on bottom side
            //Collision on top side

            scene->golfball.speed.z *= -0.1f;

            
            if (scene->golfball.speed.z < 0)
            {
                scene->golfball.position.z -= distance[4] + 0.5f;
                printf("Collision with %d on BOTTOM.\n", colliding_brick);
            }
            else
            {
                printf("Collision with %d on TOP.\n", colliding_brick);
                scene->golfball.position.z -= distance[5] - 0.5f;
                if (abs(scene->golfball.speed.z) < 0.1f)
                {
                    scene->golfball.speed.z = 0.0f;
                    scene->golfball.on_ground = true;
                }

            }
            
        }
    }

    if (scene->golfball.on_ground && scene->golfball.speed.x == 0 && scene->golfball.speed.y == 0)
    {
        scene->golfball.still = true;
        printf("STILL!\n");
    }
    else
    {
        scene->golfball.still = false;
    }
    
}

int is_colliding_with_brick(Scene* scene)
{
    int i;
    for (i = 0; i < N_BRICKS; ++i)
    {
        if
        (
            scene->golfball.position.x + 0.5f > scene->bricks[i].position.x &&
            scene->golfball.position.x - 0.5f< scene->bricks[i].position.x + scene->bricks[i].size.x &&
            scene->golfball.position.y + 0.5f> scene->bricks[i].position.y &&
            scene->golfball.position.y - 0.5f< scene->bricks[i].position.y + scene->bricks[i].size.y &&
            scene->golfball.position.z + 0.5f> scene->bricks[i].position.z &&
            scene->golfball.position.z - 0.5f< scene->bricks[i].position.z + scene->bricks[i].size.z
        )
        {
            return i;
        }
    }
    return -1;
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

    character -= 32;
    index.uv[0] = character % (int)tiles.uv[0];
    index.uv[1] = character / (int)tiles.uv[0];

    printf("Printing character at (%d; %d)\n", (int)index.uv[0], (int)index.uv[1]);

    uv4 = get_uv(tiles, index);
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

void write_text_to_screen(const char* text, GLuint ascii_map, int x, int y, int size)
{
    unsigned int i;
    for(i = 0; i < strlen(text) - 1; ++i)
    {
        write_char_to_screen(text[i], ascii_map, x + (i * size), y, size);
    }
}