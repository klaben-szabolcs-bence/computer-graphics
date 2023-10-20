#ifndef SCENE_H
#define SCENE_H

#include "texture.h"
#include "utils.h"
#include "stdbool.h"

#include <obj/model.h>

typedef struct TexturedBrick
{
    Material material;
    GLuint texture;
    vec3 position;
    float rotation_angle;
    vec3 size;
    bool wrap_3d;
    int texture_size[2];
} TexturedBrick;

typedef struct GolfBall
{
    Material material;
    vec3 position;
    bool glow;
} GolfBall;

#define N_BRICKS 1

typedef struct Scene
{
    Material invalid_material;
    Material null_material;
    GolfBall golfball;
    GLuint skybox_texture;
    GLuint playable_ground_texture;
    TexturedBrick bricks[N_BRICKS];
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

/**
 * Draws a TexturedBrick.
 */
void draw_textured_brick(const TexturedBrick *brick, const Scene *scene);

#endif /* SCENE_H */
