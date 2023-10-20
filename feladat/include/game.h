#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "camera.h"

/**
 * Updates game objects
 */
void update_game(Scene* scene, double delta);

/**
 * Make the ball move, once we have finalized drag distance
 */
void make_ball_move(Scene* scene, Camera* camera, double drag_distance);

/**
 * Reset the ball
 */
void reset_ball(GolfBall* ball);

/**
 * Returns the ID of the brick we are on
 * If none returns -1
 */
int on_ground(Scene* scene);

/**
 * Prevents us from colliding with a brick
 */
void prevent_colliding(Scene* scene);

/**
 * Stop colliding with a currently colliding brick
 */
void stop_colliding(Scene* scene);

/**
 * Calculate the distances from the sides of the brick
 */
void calc_distances_from_brick(Scene* scene, int colliding_brick, float* distance);

/**
 * Calculate the minimum distance
 */
float calc_min_distance(float* distance);

/**
 * Kick the ball out from the brick
 */
void kick_from_brick(Scene *scene, float min_distance, float *distance, int colliding_brick);

/**
 * Check if the ball is colliding with a brick returns the index of the brick, -1 if none
 */
int is_colliding_with_brick(Scene* scene);

/**
 * Check if the ball is going to collide with a brick in the next frame and the returns the index of the brick
 * Returns -1 if none
 */
int is_going_to_collide_with_brick(Scene* scene);

#endif /* GAME_H */