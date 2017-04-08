#ifndef POINTC_H
#define POINTC_H

#include "fungsi.h"

typedef struct {
	int x;
	int y;
	byte color;
}pointc;

int get_pointc_x(pointc p);
int get_pointc_y(pointc p);
int get_pointc_color(pointc p);

void set_pointc_x(int newx, pointc *P);
void set_pointc_y(int newy, pointc *P);
void set_pointc_color(int newcolor, pointc *p);

void set_pointc_position(int newx, int newy, pointc *p);
void set_pointc(int newx, int newy, int newcolor,pointc *p);

#endif
