#ifndef LINEC_H
#define LINEC_H

#include "fungsi.h"
#include "point.h"

typedef struct {
	point a;
	point b;
}line;

point get_line_a(line );
point get_line_b(line );

void set_line_a(point , line*);
void set_line_b(point , line*);
void set_line_pos(point , point ,line*);

#endif
