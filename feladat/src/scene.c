#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    //load_model(&(scene->cube), "golf_ball.obj");
    //scene->texture_id = load_texture("cube.png"); 

    //glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    float ambient_material[] = {0, 0, 0};
    float diffuse_material[] = {0.55, 0.55, 0.55};
    float specular_material[] = {0.77, 0.77, 0.77};

    scene->material.ambient = array_to_color(ambient_material);
    scene->material.diffuse = array_to_color(diffuse_material);
    scene->material.specular = array_to_color(specular_material);
    scene->material.shininess = 32.0;

    GolfBall ball;
    float pos[] = {10, 0, 0};
    ball.position = array_to_vec3(pos);

    scene->golfball = ball;

}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 0.01f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 0.1f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 0.1f };
    float position[] = { 10000.0f, 10000.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    //draw_model(&(scene->cube));
    glPushMatrix();
    glTranslatef(scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
    glutSolidSphere(2, 36, 36);
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
