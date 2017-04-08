#ifndef bshape_H
#define bshape_H

#include "queuep.h"
#include "line.h"

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
	unsigned char color;
} Objek;

/* Draw line */
void draw_line_n(line );
void draw_line_point(point , point , byte );
void draw_line(int, int, int, int, byte);
void draw_line_move(point , point , int , byte );

/* Draw Circle */
void draw_circle(point , int , byte );
void draw_circle_canvas(int, int, int, int, byte);
void draw_circle_fill(point , int , byte );

/* Draw Triangle */
void draw_triangle(int, int, int, int, byte);
void draw_triangle_canvas(int, int, int, int, byte);

/* Draw Rectangle */
void draw_rect_point(point , point , byte );
void draw_rect(int , int , int, int, byte );
void draw_rect_canvas(int , int , int , int , byte );

/* Extended methods */
void fill_all(byte color);
void fill_rect(point p, point q, byte color);
void draw_screen_background(unsigned char color);
void clear_all(int, Objek *o);

void ZoomIn(int, Objek *o);
void ZoomOut(int, Objek *o);
void RotateClockWise(int, Objek *o);
void RotateUnClockWise(int, Objek *o);

void move_left(int, Objek *o);
void move_right(int, Objek *o);
void move_up(int, Objek *o);
void move_down(int, Objek *o);

int get_section(int x, int y, int xcanvas1, int ycanvas1, int xcanvas2, int ycanvas2);
void draw_line_canvas(int x1, int y1, int x2, int y2, int xcanvas1, int ycanvas1, int xcanvas2, int ycanvas2, unsigned char color);


#endif

