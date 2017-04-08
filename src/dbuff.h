#ifndef DBUFF_H
#define DBUFF_H

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>

void save_double_buffer(unsigned char *double_buffer, int x1, int y1, int x2, int y2);
void draw_double_buffer(unsigned char *double_buffer, int x1, int y1, int x2, int y2);

#endif
