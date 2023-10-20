#ifndef SCENE_H
#define SCENE_H

#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct GolfBall
{
    vec3 position;
} GolfBall;

typedef struct Scene
{
    Material material;
    GolfBall golfball;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
