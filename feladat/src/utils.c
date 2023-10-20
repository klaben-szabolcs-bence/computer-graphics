#include "utils.h"

#include <math.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

vec3 array_to_vec3(float array[3])
{
	vec3 vector;
	vector.x = array[0];
	vector.y = array[1];
	vector.z = array[2];
	return vector;
}

vec3 create_vec3(float x, float y, float z)
{
	vec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

Color array_to_color(float array[4])
{
	Color color;
	color.red = array[0];
	color.green = array[1];
	color.blue = array[2];
	color.alpha = array[3];
	return color;
}

Color create_color(float r, float g, float b, float a)
{
	Color color;
	color.red = r;
	color.green = g;
	color.blue = b;
	color.alpha = a;
	return color;
}

ArrayColor color_to_array(Color color)
{
	ArrayColor array;
	array.color[0] = color.red;
	array.color[1] = color.green;
	array.color[2] = color.blue;
	array.color[3] = color.alpha;
	return array;
}

Material create_material(Color ambient, Color diffuse, Color specular, float shininess, Color emission)
{
	Material material;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	material.emission = emission;
	return material;
}

ArrayUV4 get_uv(ArrayUV tiles, ArrayUV index)
{
	float left_U = index.uv[0] / tiles.uv[0];
	float right_U = (index.uv[0] + 1.0f) / tiles.uv[0];
	float top_V = (tiles.uv[1] - index.uv[1]) / tiles.uv[1];
	float bottom_V = (tiles.uv[1] - index.uv[1] - 1.0f) / tiles.uv[1];

	ArrayUV4 uv4;
	uv4.uv4[0].uv[0] = left_U;
	uv4.uv4[0].uv[1] = top_V;
	uv4.uv4[1].uv[0] = right_U;
	uv4.uv4[1].uv[1] = top_V;
	uv4.uv4[2].uv[0] = right_U;
	uv4.uv4[2].uv[1] = bottom_V;
	uv4.uv4[3].uv[0] = left_U;
	uv4.uv4[3].uv[1] = bottom_V;
	return uv4;
}