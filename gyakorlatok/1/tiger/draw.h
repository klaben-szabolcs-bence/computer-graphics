#ifndef DRAW_H
#define DRAW_H

#include "model.h"

/**
 * Draw the model.
 */
void draw_model(const struct Model* model);

/**
 * Draw the triangles of the model.
 */
void draw_triangles(const struct Model* model);

/**
 * Draw the quads of the model.
 */
void draw_quads(const struct Model* model);

/**
 * Draw the normal vectors of the model.
 *
 * NOTE: It assumes that all vertex has normal vector with the same index.
 */
void draw_normals(const struct Model* model, double length);

#endif // DRAW_H
