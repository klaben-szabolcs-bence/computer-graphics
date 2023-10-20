#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

typedef struct Scene
{
    // NOTE: Place for model structures and texture ids.
} Scene;

/**
 * Initialize the scene.
 */
void init_scene(Scene* scene);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * @brief Draw a pyramid
 */
void draw_pyramid(double x, double y, double z, double width, double height);

#endif /* SCENE_H */

