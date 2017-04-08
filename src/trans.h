#ifndef TRANS_H
#define TRANS_H

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>

#include "point.h"
#include "fungsi.h"

typedef struct{
	float a;
	float c;
	float b;
	float d;
} Matrix;
/* Matriks
   |a  b|
   |c  d|
*/

void Translation(point* p, int horizontal, int vertical);
void SetMatrix(Matrix *M, float a, float c, float b, float d);
void TransformPoint(point *p, point titikpusat, Matrix M);
void ComposeMatrix(Matrix *M, Matrix M1, Matrix M2);
void RotatePointBasedOnGivenPoint(point *terputar, point titikpusat, int sp);

#endif
