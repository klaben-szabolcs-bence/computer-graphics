#ifndef UTILS_H
#define UTILS_H
#define _USE_MATH_DEFINES
#define FALSE 0
#define TRUE 1
#include <math.h>

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
    float alpha;
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
    struct Color emission;
} Material;

typedef struct ArrayColor
{
    float color[4];
} ArrayColor;


/**
 * Two floats in a array. First is u, second is v.
 */
typedef struct ArrayUV
{
    float uv[2];
} ArrayUV;

/**
 * 4 UV coordinates: left-top, right-top, bottom-right, bottom-left.
 */
typedef struct ArrayUV4
{
    double uv[8];
} ArrayUV4;

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
 * Turns an array to a color (rgba)
 */
Color array_to_color(float array[4]);

/**
 * Creates a color (rgba)
 */
Color create_color(float r, float g, float b, float a);

/**
 * Turns a color to an array (rgba)
 */
ArrayColor color_to_array(Color color);

/**
 * Creates a material
 */
Material create_material(Color ambient, Color diffuse, Color specular, float shininess, Color emission);

/**
 * Generetaes the UV coordinates required for mapping. (Goes from bottom to top)
 */
ArrayUV4 get_uv(ArrayUV tiles, ArrayUV index);

/**
 * Generates the UV coodinates required for mapping. (Goes from top to bottom)
 */
ArrayUV4 get_uv2(ArrayUV tiles, ArrayUV index);

/**
 * Returns the sign of the number.
 */
signed char sgn(float num);

#endif /* UTILS_H */
