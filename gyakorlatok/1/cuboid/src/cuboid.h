#ifndef CUBOID_H
#define CUBOID_H

/**
 * Data of a cuboid object in Descartes coordinate system
 */
typedef struct Cuboid
{
	double width;
	double height;
	double depth;
} Cuboid;

/// Set the data of the cuboid
void set_size(Cuboid* cuboid, double width, double height, double depth);

/// Calculate the volume of the cuboid.
double calc_volume(const Cuboid* cuboid);

/// Calculate the surface of the cuboid.
double calc_surface(const Cuboid* cuboid);

/// Check if a side is a square
int is_a_side_square(const Cuboid* cuboid);

#endif // CUBOID_H
