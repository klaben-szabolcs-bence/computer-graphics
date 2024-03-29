#ifndef CAMERA_H
#define CAMERA_H

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

#include "utils.h"
#include "stdbool.h"
#include "scene.h"

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
    bool freecam;
    int distance;

} Camera;

typedef struct Screen
{
    int width;
    int height;
} Screen;

Screen screen;

/**
 * Is the texture preview visible?
 */
int is_preview_visible;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, double time, Scene* scene);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera, const Scene* scene);

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
 * Shows the texture preview.
 */
void show_texture_preview();

#endif /* CAMERA_H */
