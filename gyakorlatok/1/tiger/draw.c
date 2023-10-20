#include "draw.h"

#include <GL/glut.h>

#include <stdio.h>

void draw_model(const struct Model* model)
{
    draw_triangles(model);
    // draw_quads(model);
}

void draw_triangles(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, normal_x, normal_y, normal_z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1-v);

            normal_index = model->triangles[i].points[k].normal_index;
            normal_x = model->normals[normal_index].x;
            normal_y = model->normals[normal_index].y;
            normal_z = model->normals[normal_index].z;
            glNormal3d(normal_x, normal_y, normal_z);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

    glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_normals(const struct Model* model, double length)
{
    int i;
    double x1, y1, z1, x2, y2, z2;

    glColor3f(0, 0, 1);

    glBegin(GL_LINES);

    for (i = 0; i < model->n_vertices; ++i) {
        x1 = model->vertices[i].x;
        y1 = model->vertices[i].y;
        z1 = model->vertices[i].z;
        x2 = x1 + model->normals[i].x * length;
        y2 = y1 + model->normals[i].y * length;
        z2 = z1 + model->normals[i].z * length;
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
    }

    glEnd();
}
