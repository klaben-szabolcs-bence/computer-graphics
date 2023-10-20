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

Color array_to_color(float array[3])
{
	Color color;
	color.red = array[0];
	color.green = array[1];
	color.blue = array[2];
	return color;
}
