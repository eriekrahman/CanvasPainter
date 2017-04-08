#ifndef MOUSE_H
#define MOUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include "bshape.h"

#define MOUSE_WIDTH 	6
#define MOUSE_HEIGHT 	11
#define MOUSE_INT		0x33

unsigned char mouse_on();
unsigned char right_button_pressed();
unsigned char right_button_released();
unsigned char left_button_pressed();
unsigned char left_button_released();
void get_mouse_position(int *x, int *y);
void draw_mouse(int x, int y, unsigned char color);
void hide_mouse(int x, int y);

#endif
