#include "scene.h"

#include <GL/glut.h>


#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    //load_model(&(scene->cube), "golf_ball.obj");
    //scene->texture_id = load_texture("cube.png"); 

    //glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    Color ambient_material = create_color(0, 0, 0, 1);
    Color diffuse_material = create_color(0.55, 0.55, 0.55, 1);
    Color specular_material = create_color(0.77, 0.77, 0.77, 1);
    Color emission_material = create_color(0, 0, 0, 1);
    scene->material = create_material(ambient_material, diffuse_material, specular_material, 32.0, emission_material);

    GolfBall ball;
    ball.position = create_vec3(10, 0, 0);
    scene->golfball = ball;
    scene->golfball.glow = false;
}

void set_lighting(const Scene* scene)
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 0.001f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 0.1f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 0.1f };
    float position[] = { 10000.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    ambient_light[3] = 1.0f;
    diffuse_light[3] = 1.0f;
    specular_light[3] = 1.0f;
    position[0] = scene->golfball.position.x;
    position[1] = scene->golfball.position.y;
    position[2] = scene->golfball.position.z;

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void set_material(const Material* material)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_to_array(material->ambient).color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_to_array(material->diffuse).color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_to_array(material->specular).color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color_to_array(material->emission).color);
}

void draw_scene(const Scene* scene)
{
    draw_origin();
    set_material(&(scene->material));
    set_lighting(scene);
    //draw_model(&(scene->cube));
    glPushMatrix();
    glTranslatef(scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
    glutSolidSphere(1, 36, 36);
    glPopMatrix();
    
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
