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
    bool tiled_texture;
} TexturedBrick;

typedef struct GolfBall
{
    Material material;
    vec3 position;
    bool glow;
    double speed;
    double velocity;
    vec3 direction_vector;
    bool still;
} GolfBall;

#define N_BRICKS 6

typedef struct Scene
{
    Material invalid_material;
    Material null_material;
    GolfBall golfball;
    GLuint skybox_texture;
    GLuint playable_ground_texture;
    Material playable_ground_material;
    GLuint wooden_texture;
    Material wooden_material;
    TexturedBrick bricks[N_BRICKS];
    GLuint ascii_texture;
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
 * Updates game objects
 */
void update_game(Scene* scene, double delta);

/**
 * Check if the ball is colliding with a brick returns the index of the brick, -1 if none
 */
int is_colliding_with_brick(Scene* scene);

/**
 * Check if the ball is going to collide with a brick in the next frame and the returns the index of the brick
 * Returns -1 if none
 */
int is_going_to_collide_with_brick(Scene* scene);

/**
 * Writes the character to the screen
 */
void write_char_to_screen(char character, GLuint ascii_map, int x, int y, int size);

/**
 * Writes the text on the screen
 */
void write_text_to_screen(const char* text, GLuint ascii_map, int x, int y, int size);

/**
 * Reset the ball
 */
void reset_ball(GolfBall* ball);

/**
 * Returns the ID of the brick we are on
 * If none returns -1
 */
int on_ground(Scene* scene);

#endif /* SCENE_H */
