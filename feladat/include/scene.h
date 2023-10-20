#ifndef SCENE_H
#define SCENE_H

#include "texture.h"
#include "utils.h"
#include "stdbool.h"

#include <obj/model.h>

typedef struct MaterialBrickParticle
{
    Material* material;
    vec3 position;
    vec3 size;
    vec3 speed;
    int lifespan;
    float rotation_angle;
} MaterialBrickParticle;

typedef struct TexturedBrick
{
    Material* material;
    GLuint texture;
    vec3 position;
    float rotation_angle;
    vec3 size;
    bool wrap_3d;
    int texture_size[2];
    bool tiled_texture;
    bool open_top;
} TexturedBrick;

typedef struct GolfBall
{
    Material* material;
    vec3 position;
    bool glow;
    double speed;
    double velocity;
    vec3 direction_vector;
    bool still;
    GLuint texture;
} GolfBall;

#define N_BRICKS 10
#define N_PARTICLES 500

typedef struct Scene
{
    GolfBall golfball;
    TexturedBrick bricks[N_BRICKS];
    MaterialBrickParticle particles[N_PARTICLES];
    int hole;
    Material invalid_material;
    Material null_material;
    Material playable_ground_material;
    Material wooden_material;
    Material plastic_material;
    Material unplayable_material;
    Material cherry_material;
    GLuint skybox_texture;
    GLuint ascii_texture;
    GLuint playable_ground_texture;
    GLuint wooden_texture;
    GLuint plastic_texture;
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

/**
 * Draw a MaterialBrickParticle
 */
void draw_material_brick_particle(const MaterialBrickParticle *brick);

#endif /* SCENE_H */