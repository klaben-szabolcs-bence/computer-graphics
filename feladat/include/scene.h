#ifndef SCENE_H
#define SCENE_H

#include "texture.h"
#include "utils.h"
#include "stdbool.h"

#include <obj/model.h>

typedef struct GolfBall
{
    Material material;
    vec3 position;
    bool glow;
} GolfBall;

typedef struct Scene
{
    Material invalid_material;
    Material null_material;
    GolfBall golfball;
    GLuint skybox_texture;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

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

/**
 * Draws a skybox.
 */
void draw_skybox(const Scene* scene);

#endif /* SCENE_H */
