#ifndef PIXEL_H
#define PIXEL_H

#include "point.h"
#include "pointc.h"
#include "fungsi.h"

void set_mode(byte mode);
void draw_pixel(int x, int y, byte color);
void draw_point(point p, byte color);
void draw_pointc(pointc p);
byte get_color(int x, int y);
#endif
