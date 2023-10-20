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

Color array_to_color(float array[3])
{
	Color color;
	color.red = array[0];
	color.green = array[1];
	color.blue = array[2];
	return color;
}

Color create_color(float r, float g, float b)
{
	Color color;
	color.red = r;
	color.green = g;
	color.blue = b;
	return color;
}

Material create_material(Color ambient, Color diffuse, Color specular, float shininess)
{
	Material material;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	return material;
}

Material create_material_10f(
	float ambient_red, float ambient_green, float ambient_blue,
	float diffuse_red, float diffuse_green, float diffuse_blue,
	float specular_red, float specular_green, float specular_blue,
	float shininess)
{
	Color ambient = create_color(ambient_red, ambient_green, ambient_blue);
	Color diffuse = create_color(diffuse_red, diffuse_green, diffuse_blue);
	Color specular = create_color(specular_red, specular_green, specular_blue);
	return create_material(ambient, diffuse, specular, shininess);
}