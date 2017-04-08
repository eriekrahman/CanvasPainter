#ifndef FUNGSI_H
#define FUNGSI_H

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include <math.h>
#include <conio.h>

#define TEXT_MODE 0x03
#define VGA_MODE  0x13

#define NIL 0
#define address int
#define true 1
#define false 0
#define boolean unsigned char
#define pi 3.1415926535897932384626433832795

#define MAX_WIDTH 320
#define MAX_HEIGHT 200

#define MIN_WIDTH 0
#define MIN_HEIGHT 0

#define MAX_WIDTH_CANVAS 180
#define MIN_WIDTH_CANVAS 0

#define MAX_HEIGHT_CANVAS 180
#define MIN_HEIGHT_CANVAS 0

#define N_OBJECT 100

typedef unsigned char  byte;
typedef unsigned short word;
typedef long           fixed16_16;

void swap(int*, int*);
void wait(int );
int char2int(char );
char int2char(int );


#endif
