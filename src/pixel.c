#include "pixel.h"

byte *fb = (byte*) 0xA0000000L;

void set_mode(byte mode) {
  union REGS regs;

  regs.h.ah = 0x00;	/* prosedur 0x00: mengeset Video Mode */
  regs.h.al = mode;	/* video mode */
  int86(0x10, &regs, &regs) ;
}

/* Penggambaran titik*/

void draw_pixel(int x, int y, byte color) 
{
	if ((x >= 0) && (x < 320) && (y >= 0) && (y < 200))
		fb[(y<<8) + (y<<6) + x] = color;
}

byte get_color(int x, int y) 
{
	if ((x >= 0) && (x < 320) && (y >= 0) && (y < 200)) 
		return fb[(y<<8) + (y<<6) + x];
	else 
		return 0;
}

void draw_point(point p, byte color)
{
	if ((p.x >= 0) && (p.x < 320) && (p.y >= 0) && (p.y < 200))
		fb[(p.y<8) + (p.y<<6) + p.x] = color;
}

void draw_pointc(pointc p) 
{
	if ((p.x >= 0) && (p.x < 320) && (p.y >= 0) && (p.y < 200))
		fb[(p.y<8) + (p.y<<6) + p.x] = p.color;   
}
