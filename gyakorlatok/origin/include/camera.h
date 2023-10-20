#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
    vec3 rotation_speed;
} Camera;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, double time);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera* camera, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_camera_side_speed(Camera* camera, double speed);

/**
 * @brief Set the vertical speed of the camera.
 */
void set_camera_vertical_speed(Camera* camera, double speed);

/**
 * @brief Rotates the camera horizontally.
 */
void rotate_camera_horizontally(Camera* camera, double rotation);

/**
 * @brief Rotates the camera vertically.
 */
void rotate_camera_vertically(Camera* camera, double rotation);

/**
 * @brief Set the horizontal rotational speed of the camera.
 */
void set_camera_horizontal_rotation_speed(Camera* camera, double speed);

/**
 * @brief Set the vertical rotational speed of the camera.
 */
void set_camera_vertical_rotation_speed(Camera* camera, double speed);

/**
 * @brief Print the camera's position and rotation to the terminal.
 */
void print_camera_info(Camera* camera);

#endif /* CAMERA_H */

