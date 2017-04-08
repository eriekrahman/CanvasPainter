#include "point.h"


int get_point_x(point p)
{
	return p.x;
}

int get_point_y(point p)
{
	return p.y;
}

void set_point_x(int newx, point *p)
{
	(*p).x = newx;
}

void set_point_y(int newy, point *p)
{
	(*p).y = newy;
}

void set_point(int newx, int newy, point *p)
{
	(*p).x = newx;
	(*p).y = newy;
}

void tulis_point(point p)
{
	printf("x = %i, y = %i \n", p.x, p.y);
}
