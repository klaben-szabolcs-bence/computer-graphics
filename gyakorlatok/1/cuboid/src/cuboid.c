#include "cuboid.h"

#include <math.h>

void set_size(Cuboid* cuboid, double width, double height, double depth)
{
	cuboid->width = width;
	cuboid->height = height;
	cuboid->depth = depth;
}

double calc_volume(const Cuboid* cuboid)
{
	double volume = cuboid->width * cuboid->height * cuboid->depth;
	return volume;
}

double calc_surface(const Cuboid* cuboid)
{
    double front_surface = cuboid->width * cuboid->height;
    double side_surface = cuboid->height * cuboid->depth;
    double top_surface = cuboid->width * cuboid->depth;
    return 2 * (front_surface + side_surface + top_surface);
}

int is_a_side_square(const Cuboid* cuboid)
{
    if (cuboid->width == cuboid->height) return 1;
    if (cuboid->width == cuboid->depth) return 1;
    if (cuboid->height == cuboid->depth) return 1;
    return 0;
}
