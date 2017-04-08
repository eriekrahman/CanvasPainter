#ifndef POINT_H
#define POINT_H

#include "point.h"

typedef struct {
	int x;
	int y;
}point;

int get_point_x(point p);
int get_point_y(point p);

void set_point_x(int newx, point *P);
void set_point_y(int newy, point *P);

void set_point(int newx, int newy, point *p);

void tulis_point(point p);
#endif
