#ifndef UTILS_H
#define UTILS_H
#define _USE_MATH_DEFINES
#define FALSE 0
#define TRUE 1

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient; 
    struct Color diffuse; 
    struct Color specular; 
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

/**
 * Turns an array to a vec3 (x, y, z)
 */
vec3 array_to_vec3(float array[3]);

/**
 * Creates a vec3
 */
vec3 create_vec3(float x, float y, float z);

/**
 * Turns an array to a color (rgb)
 */
Color array_to_color(float array[3]);

/**
 * Creates a color (rgb)
 */
Color create_color(float r, float g, float b);

/**
 * Creates a material
 */
Material create_material(Color ambient, Color diffuse, Color specular, float shininess);

/**
 * Creates a material only using floats
 */
Material create_material_10f(
	float ambient_red, float ambient_green, float ambient_blue,
	float diffuse_red, float diffuse_green, float diffuse_blue,
	float specular_red, float specular_green, float specular_blue,
	float shininess);

#endif /* UTILS_H */
