#include "cuboid.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	double w, h, d;

	printf("Input the three size of the cuboid in the following order\nseparated by space: width height depth!\n");
	while (scanf("%lf %lf %lf", &w, &h, &d) != 3)
    {
	    printf("Malformed input!\n");
	    while (getchar() != '\n');
    }

    Cuboid cuboid;

	set_size(&cuboid, w, h, d);
	double volume = calc_volume(&cuboid);
	double surface = calc_surface(&cuboid);
	int is_side_square = is_a_side_square(&cuboid);
	
	printf("== Cuboid ==\nVolume: %lf\nSurface: %lf\nIs a side a square? %s\n",
        volume, surface, is_side_square ? "Yes" : "No");
	
	return 0;
}
