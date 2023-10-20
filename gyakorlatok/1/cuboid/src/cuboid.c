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
