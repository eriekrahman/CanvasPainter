#include "mouse.h"

unsigned char mouse[MOUSE_WIDTH][MOUSE_HEIGHT] = {	
                                               { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                               { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                                               { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                                               { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                               { 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1},
                                               { 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1}
};

unsigned char mouse_background[MOUSE_WIDTH][MOUSE_HEIGHT];


unsigned char mouse_on()
{
	union REGS regs;
	
	regs.x.ax = 0x00;
	int86(MOUSE_INT, &regs, &regs);
	return regs.x.ax;
}

unsigned char right_button_pressed()
{
	union REGS regs;
	
	regs.x.ax = 0x05;
	regs.x.bx = 0x01;
	int86(MOUSE_INT, &regs, &regs);

	return regs.x.bx;

}

unsigned char right_button_released()
{
	union REGS regs;
	
	regs.x.ax = 0x06;
	regs.x.bx = 0x01;
	int86(MOUSE_INT, &regs, &regs);

	return regs.x.bx;

}

unsigned char left_button_pressed()
{
	union REGS regs;
	
	regs.x.ax = 0x05;
	regs.x.bx = 0x00;
	int86(MOUSE_INT, &regs, &regs);

	return regs.x.bx;
}

unsigned char left_button_released()
{
	union REGS regs;

	regs.x.ax = 0x06;
	regs.x.bx = 0x00;
	int86(MOUSE_INT, &regs, &regs);

	return regs.x.bx;
}

void get_mouse_position(int *x, int *y)
{
	union REGS regs;
	
	regs.x.ax = 0x03;
	int86(MOUSE_INT, &regs, &regs);
	*x = (int)regs.x.cx;
	*y = (int)regs.x.dx;
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	if (*x > 319)
		*x = 319;
	if (*y > 319)
		*y = 319;
}

void draw_mouse(int x, int y, unsigned char color)
{
	unsigned char *fb=(unsigned char *)0xA0000000L;        /* this points to video memory. */
	int i, j, k, l;

	for (i = 0; i < MOUSE_WIDTH; i++)
	{
		for (j = 0; j < MOUSE_HEIGHT; j++)
		{
			k = x+i;
			l = y+j;
			mouse_background[i][j] = fb[(l<<8) + (l<<6) + k];
			if (mouse[i][j] != 0 && k < MAX_WIDTH && l < MAX_HEIGHT)
				fb[(l<<8) + (l<<6) + k] = color;
		}
	}
}

void hide_mouse(int x, int y)
{
	unsigned char *fb=(unsigned char *)0xA0000000L;        /* this points to video memory. */
	int i, j, k, l;

	for (i = 0; i < MOUSE_WIDTH; i++)
	{
		for (j = 0; j < MOUSE_HEIGHT; j++)
		{
			k = x+i;
			l = y+j;
			if (k < MAX_WIDTH && l < MAX_HEIGHT)
				fb[(l<<8) + (l<<6) + k] = mouse_background[i][j];
		}
	}
}

