#include "line.h"

point get_line_a(line p)
{
	return p.a;
}

point get_line_b(line p)
{
	return p.b;
}

void set_line_a(point newa, line *p)
{
	p->a = newa;
}

void set_line_b(point newb, line *p)
{
	p->b = newb;
}

void set_line_pos(point newa, point newb, line *p)
{
	p->a = newa;
	p->b = newb;
}
