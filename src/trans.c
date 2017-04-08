#include "trans.h"

void Translation(point *p, int horizontal, int vertical)
{
	int tx, ty;
	tx = p->x;
	ty = p->y;
	p->x = tx + horizontal;
	p->y = ty - vertical;
}

void SetMatrix(Matrix *M, float a, float c, float b, float d)
{
	M->a = a;
	M->c = c;
	M->b = b;
	M->d = d;
}

void TransformPoint(point *p, point titikpusat, Matrix M)
{
	int tx, ty;
	
	tx = p->x - titikpusat.x;
	ty = p->y - titikpusat.y;
	p->x = (int) tx*M.a + ty*M.c + titikpusat.x;
	p->y = (int) tx*M.b + ty*M.d + titikpusat.y;
}

void ComposeMatrix(Matrix *M, Matrix M1, Matrix M2)
{
	M->a = M1.a*M2.a + M1.b*M2.c;	
	M->b = M1.a*M2.b + M1.b*M2.d;
	M->c = M1.c*M2.a + M1.d*M2.c;
	M->d = M1.c*M2.b + M1.d*M2.d;
}

void RotatePointBasedOnGivenPoint(point *terputar, point titikpusat, int sp)
{
    int tx, ty; 	
	float sudutputar = (float)sp * pi / 180.0;
    tx = terputar->x - titikpusat.x;
    ty = terputar->y - titikpusat.y;
	terputar->x = (tx*cos(sudutputar)) - (ty*sin(sudutputar)) + titikpusat.x;
    terputar->y = (tx*sin(sudutputar)) + (ty*cos(sudutputar)) + titikpusat.y;
}

