#include "pointc.h"

int get_pointc_x(pointc p)
{
	return p.x;
}

int get_pointc_y(pointc p)
{
	return p.y;
}

int get_pointc_color(pointc p)
{
	return p.color;
}

void set_pointc_x(int newx, pointc *p)
{
	p->x = newx;
}

void set_pointc_y(int newy, pointc *p)
{
	p->y = newy;
}

void set_pointc_position(int newx, int newy, pointc *p)
{
	p->x = newx;
	p->y = newy;
}

void set_pointc_color(int newcolor, pointc *p)
{
	p->color = newcolor;
}

void set_pointc(int newx, int newy, int newcolor, pointc *p)
{
	p->x = newx;
	p->y = newy;
	p->color = newcolor;
}

