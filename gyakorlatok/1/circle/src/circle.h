#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;

/**
 * Set the data of the circle
 */
double set_circle_data(Circle* circle, double x, double y, double radius);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

#endif // CIRCLE_H
