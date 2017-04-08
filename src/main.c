#include "bshape.h"
#include "dbuff.h"
#include "mouse.h"
#include "fungsi.h"

// ====================================
///////////////////////////////////////
//////////    Column 1     ////////////
///////////////////////////////////////
// ====================================

/* Boundary of Drawing Square Choice */
#define xmin_square 200
#define ymin_square 0
#define xmax_square 230
#define ymax_square 30

/* Boundary of Drawing Triangle Choice */
#define xmin_triangle 200
#define ymin_triangle 32
#define xmax_triangle 230
#define ymax_triangle 62

/* Boundary of Drawing Circle Choice */
#define xmin_circle 200
#define ymin_circle 64
#define xmax_circle 230
#define ymax_circle 94

/* Boundary of Drawing Line Choice */
#define xmin_line 200
#define ymin_line 96
#define xmax_line 230
#define ymax_line 126


// ====================================
///////////////////////////////////////
//////////    Column 2     ////////////
///////////////////////////////////////
// ====================================

/* Boundary of Drawing Font Choice */
#define xmin_font 232
#define ymin_font 0
#define xmax_font 262
#define ymax_font 30

/* Boundary of Fill Drawing Choice */
#define xmin_fill 232
#define ymin_fill 32
#define xmax_fill 262
#define ymax_fill 62


// ====================================
///////////////////////////////////////
////////    Special Column     ////////
///////////////////////////////////////
// ====================================

/* Boundary of Clear */
#define xmin_clear 220
#define ymin_clear 175
#define xmax_clear 260
#define ymax_clear 185

/* Boundary of Palet Choice */
#define xmin_palet 200
#define ymin_palet 160
#define xmax_palet 280
#define ymax_palet 170

void clearchoice()
{
     draw_rect (xmin_square, ymin_square, xmax_square, ymax_square, WHITE);
     draw_rect (xmin_triangle, ymin_triangle, xmax_triangle, ymax_triangle, WHITE);
     draw_rect (xmin_circle, ymin_circle, xmax_circle, ymax_circle, WHITE);
     draw_rect (xmin_line, ymin_line, xmax_line, ymax_line, WHITE);
     draw_rect (xmin_fill, ymin_fill, xmax_fill, ymax_fill, WHITE);     
}

void clear_canvas()
{
	int i,j;
	for (i=MIN_WIDTH_CANVAS+1;i<=MAX_WIDTH_CANVAS-1;i++)
	{
		for (j=MIN_HEIGHT_CANVAS+1;j<=MAX_HEIGHT_CANVAS-1;j++)
		{
			draw_pixel(i,j,0);
		}                     
	}	
}

int main()
{
	int tmp1, tmp2, tmp3, tmp4, tmp5;
	int exitprog = 0;
	unsigned char *double_buffer;
	int x, y, prev_x, prev_y;
	int i, j, n_line, n_square, n_triangle, n_circle, n_fill, active, color;	
	byte current_color = WHITE;
	Objek o1, o2, o3, o4, o5, o6, o7, o8, o9, o10;
	float a, b, c, d, a1, b1, c1, d1;
	point p;
	Objek AO_line[N_OBJECT], AO_square[N_OBJECT], AO_circle[N_OBJECT], AO_triangle[N_OBJECT], AO_fill[N_OBJECT];	
	
	double_buffer = (unsigned char*) malloc (320*200);
	
	if (double_buffer == NULL)
	{
		printf("Not enough memory for double buffer.\n");
		exit(1);
	}
	
	if (!mouse_on())
	{
		printf("Mouse not found.\n");
		exit(1);
	}
	
	set_mode (VGA_MODE);

	/* main canvas */
	draw_rect (MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, WHITE);

	/* navigate button */
	draw_rect (0, 181, 10, 190, WHITE);		/* left scroll */
	draw_line(9, 182, 1, 185, WHITE);
	draw_line(1, 185, 9, 189, WHITE); 
	draw_rect (11, 181, 21, 190, WHITE);	/* right scroll */
	draw_line(12, 182, 20, 185, WHITE);
	draw_line(20, 185, 12, 189, WHITE); 
	draw_rect (181, 0, 191, 10, WHITE);		/* up scroll */
	draw_line(186, 1, 182, 9, WHITE);
	draw_line(186, 1, 190, 9, WHITE);
	draw_rect (181, 11, 191, 21, WHITE);	/* down scroll */
	draw_line(186, 20, 182, 12, WHITE);
	draw_line(186, 20, 190, 12, WHITE);
	
	/* transform button */
	draw_rect (30, 181, 40, 190, WHITE);	/* zoom in */
	draw_line(32, 185, 38, 185, WHITE);
	draw_line(35, 183, 35, 188, WHITE);
	draw_rect (41, 181, 51, 190, WHITE);	/* zoom out */
	draw_line(43, 185, 49, 185, WHITE);
	draw_rect (181, 30, 191, 40, WHITE);	/* rotate clockwise */
	draw_rect (181, 41, 191, 51, WHITE);	/* rotate unclockwise */
	
	/* object component button */
	
	/* square = 1*/
	draw_rect (xmin_square, ymin_square, xmax_square, ymax_square, WHITE);
	tmp5 = (ymax_square-ymin_square)/4;
	draw_rect (xmin_square+tmp5, ymin_square+tmp5, xmax_square-tmp5, ymax_square-tmp5, WHITE);
	
	/* circle = 2*/
	draw_rect (xmin_circle, ymin_circle, xmax_circle, ymax_circle, WHITE);	
    tmp1 = xmin_circle+((xmax_circle-xmin_circle)/2);
    tmp2 = ymin_circle+((ymax_circle-ymin_circle)/2);
	set_point(tmp1, tmp2, &p);
	draw_circle(p, 8, WHITE);
	
	/* triangle = 3*/
    draw_rect (xmin_triangle, ymin_triangle, xmax_triangle, ymax_triangle, WHITE);
    draw_triangle(xmin_triangle+tmp5, ymin_triangle+tmp5, xmax_triangle-tmp5, ymax_triangle-tmp5, WHITE);
	
	/* line = 4*/
	draw_rect (xmin_line, ymin_line, xmax_line, ymax_line, WHITE);		
	draw_line (xmin_line+tmp5, ymin_line+tmp5, xmax_line-tmp5, ymax_line-tmp5, WHITE);
	

	/* font = 5*/	
	/*
	draw_rect (xmin_font, ymin_font, xmax_font, ymax_font, WHITE);	
	tmp1 = xmin_font+((xmax_font-xmin_font)/2);
	tmp2 = ymin_font+((ymax_font-ymin_font)/2);
	tmp3 = tmp1-((xmin_font+tmp5-tmp1)/2);
	tmp4 = tmp1+((xmin_font+tmp5-tmp1)/2);	
	draw_line(tmp1, ymin_font+tmp5, xmin_font+tmp5, ymax_font-tmp5, WHITE);
	draw_line(tmp1, ymin_font+tmp5, xmax_font-tmp5, ymax_font-tmp5, WHITE);
	draw_line(tmp3, tmp2, tmp4, tmp2, WHITE);
	*/
	
	/* fill */
	draw_rect (xmin_fill, ymin_fill, xmax_fill, ymax_fill, WHITE);
	draw_rect_fill (xmin_fill+tmp5, ymin_fill+tmp5, xmax_fill-tmp5, ymax_fill-tmp5, WHITE);
	
	/* cls */
	draw_rect (xmin_clear, ymin_clear, xmax_clear, ymax_clear, WHITE);	
	draw_line (xmin_clear, ymin_clear, xmax_clear, ymax_clear, WHITE);	
	draw_line (xmin_clear, ymax_clear, xmax_clear, ymin_clear, WHITE);

	/* color palette */
    draw_rect (xmin_palet, ymin_palet, xmax_palet, ymax_palet, WHITE);			
	color = 32;
	for (i=xmin_palet+1; i<= xmax_palet-1; i++)
		draw_line(i, ymin_palet+1, i, ymax_palet-1, color++);
		
	/* selected color box */	
	draw_rect (200, 148, 280, 158, WHITE);		
	for (i=201; i<= 279; i++)
		draw_line(i, 149, i, 157, current_color);
		
	/* close button */	
	draw_rect (300, 0, 310, 10, WHITE);		
	for (i=301; i<= 309; i++)
		draw_line(i, 1, i, 9, RED);
	draw_line(301, 1, 309, 9, WHITE);
	draw_line(309, 1, 301, 9, WHITE);
		
	/* mouse pointer (starting point is in the center) */  
	prev_x = MAX_WIDTH/2;
	prev_y = MAX_HEIGHT/2;
	draw_mouse(prev_x, prev_y, YELLOW);
		
	n_line = 1;
	n_square = 1;
	n_triangle = 1;
	n_circle = 1;
	n_fill = 1;
	active = 0;
	do {
		// Get current mouse pointer position
		get_mouse_position(&x, &y);

		// if the pointer is not the same as before, it means the mouse is moved and needs to re-render
		if (prev_x != x || prev_y != y)
		{
			hide_mouse(prev_x, prev_y);
			draw_mouse(x, y, YELLOW);
			prev_x = x;
			prev_y = y;
		}
		
		if (left_button_released())
		{
			if ((x>=MIN_WIDTH_CANVAS) && (x<=MAX_WIDTH_CANVAS) && (y>=MIN_HEIGHT_CANVAS) && (y<=MAX_HEIGHT_CANVAS)) /* Canvas */
			{ 
				if (active == 1) /* square */
				{ 
					a = x; AO_square[n_square].x1 = x;
					b = y; AO_square[n_square].y1 = y;
					save_double_buffer(double_buffer, a, b, x, y);
					while (!left_button_released())
					{
						get_mouse_position(&x, &y);
						if (prev_x != x || prev_y != y)
						{
							hide_mouse(prev_x, prev_y);
							draw_double_buffer(double_buffer, a,b,prev_x, prev_y);
							save_double_buffer(double_buffer, a,b,x,y);
							draw_rect_canvas(a,b,x,y,current_color);
							draw_mouse(x, y, YELLOW);
							prev_x = x;
							prev_y = y;
						}
					}
					AO_square[n_square].x2 = x;
					AO_square[n_square].y2 = y;
					AO_square[n_square].color = current_color;
					n_square++;
				}
				else if (active == 2) /* circle */
				{ 
					a = x; AO_circle[n_circle].x1 = x;
					b = y; AO_circle[n_circle].y1 = y;
					save_double_buffer(double_buffer, a, b, x, y);
					while (!left_button_released())
					{
						get_mouse_position(&x, &y);
						if (prev_x != x || prev_y != y)
						{
							hide_mouse(prev_x, prev_y);
							save_double_buffer(double_buffer, a,b,x,y);							
							draw_mouse(x, y, YELLOW);
							prev_x = x;
							prev_y = y;
						}
					}
					hide_mouse(prev_x, prev_y);
					save_double_buffer(double_buffer, a,b,x,y);		
					draw_circle_canvas(a,b,x,y, current_color);
					draw_mouse(x, y, YELLOW);
					AO_circle[n_circle].x2 = x;
					AO_circle[n_circle].y2 = y;
					AO_circle[n_circle].color = current_color;
					n_circle++;
				}
				else if (active == 3) /* triangle */
				{ 
					draw_pixel(x,y,0);
                    a = x; AO_triangle[n_triangle].x1 = x;					
					b = y; AO_triangle[n_triangle].y1 = y;
					save_double_buffer(double_buffer, a, b, x, y);
					while (!left_button_released())
					{
						get_mouse_position(&x, &y);
						if (prev_x != x || prev_y != y)
						{
							hide_mouse(prev_x, prev_y);
							draw_double_buffer(double_buffer, a,b,prev_x, prev_y);
							save_double_buffer(double_buffer, a,b,x,y);
							draw_triangle_canvas(a,b,x,y,current_color);
							draw_mouse(x, y, YELLOW);
							prev_x = x;
							prev_y = y;
						}
					}
					AO_triangle[n_triangle].x2 = x;
					AO_triangle[n_triangle].y2 = y;
					AO_triangle[n_triangle].color = current_color;
					n_triangle++;
				}
				else if (active == 4) /* line */
				{ 
					a = x; AO_line[n_line].x1 = x;
					b = y; AO_line[n_line].y1 = y;
					save_double_buffer(double_buffer, a, b, x, y);
					while (!left_button_released())
					{
						get_mouse_position(&x, &y);
						if (prev_x != x || prev_y != y)
						{
							hide_mouse(prev_x, prev_y);
							draw_double_buffer(double_buffer, a,b,prev_x, prev_y);
							save_double_buffer(double_buffer, a,b,x,y);
							draw_line_canvas(a,b,x,y, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, current_color);
							draw_mouse(x, y, YELLOW);
							prev_x = x;
							prev_y = y;
						}
					}
					AO_line[n_line].x2 = x;
					AO_line[n_line].y2 = y;
					AO_line[n_line].color = current_color;
					n_line++;
				}
				else if (active == 6) /* fill */
				{ 
			        get_mouse_position(&x, &y);			        
			        hide_mouse(x, y);
			        if (!left_button_released())
					{
						flood_fill(x, y, current_color);
						AO_fill[n_fill].x1 = x;
						AO_fill[n_fill].y1 = y;
						AO_fill[n_fill].x2 = 0;
						AO_fill[n_fill].y2 = 0;
						AO_fill[n_fill].color = current_color;
						n_fill++;
					}
					draw_mouse(x,y,YELLOW);
				}
			}
			else if ((x>=xmin_clear) && (x<=xmax_clear) && (y>=ymin_clear) && (y<=ymax_clear))
			{
				clear_canvas();         
			}
			else if ((x>=xmin_palet) && (x<=xmax_palet) && (y>=ymin_palet) && (y<=ymax_palet)) /* color palette */
			{ 
				current_color = get_color(x, y-1);
				for (i=201; i<= 279; i++)
					draw_line(i, 149, i, 157, current_color);
			}			
			else if ((x>=300) && (x<=310) && (y>=0) && (y<=10)) /* close button */
			{ 
				exitprog = 1;
			}
			else if ((x>=xmin_square) && (x<=xmax_square) && (y>=ymin_square) && (y<=ymax_square)) /* toolbox: square */
			{ 
				active = 1;
				hide_mouse(prev_x, prev_y);
				clearchoice();				
				draw_rect (xmin_square, ymin_square, xmax_square, ymax_square, BROWN);		/* square = 1*/			
				draw_mouse(x, y, YELLOW);
			}		
			else if ((x>=xmin_circle) && (x<=xmax_circle) && (y>=ymin_circle) && (y<=ymax_circle)) /* toolbox: circle */
			{ 
				active = 2;
				hide_mouse(prev_x, prev_y);
				clearchoice();				
				draw_rect (xmin_circle, ymin_circle, xmax_circle, ymax_circle, BROWN);		/* circle = 2*/
				draw_mouse(x, y, YELLOW);
			}			
			else if ((x>=xmin_triangle) && (x<=xmax_triangle) && (y>=ymin_triangle) && (y<=ymax_triangle)) /* toolbox: triangle */
			{
				active = 3;
				hide_mouse(prev_x, prev_y);
				clearchoice();
				draw_rect (xmin_triangle, ymin_triangle, xmax_triangle, ymax_triangle, BROWN);	/* triangle = 3*/
				draw_mouse(x, y, YELLOW);
			}
			else if ((x>=xmin_line) && (x<=xmax_line) && (y>=ymin_line) && (y<=ymax_line)) /* toolbox: line */
			{ 
				active = 4;
				hide_mouse(prev_x, prev_y);
				clearchoice();
				draw_rect (xmin_line, ymin_line, xmax_line, ymax_line, BROWN);		/* line = 4*/
				draw_mouse(x, y, YELLOW);
			}
			else if ((x>=xmin_fill) && (x<=xmax_fill) && (y>=ymin_fill) && (y<=ymax_fill)) /* toolbox: fill */
			{ 
				active = 6;
				hide_mouse(prev_x, prev_y);
				clearchoice();
				draw_rect (xmin_fill, ymin_fill, xmax_fill, ymax_fill, BROWN);		/* fill = 6*/
				draw_mouse(x, y, YELLOW);
			}
			else if ((x>=0) && (x<=10) && (y>=181) && (y<=190)) /* navigate button : left scroll */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					move_left(1,&AO_line[i]);
				for (i=1; i<n_square; i++)
					move_left(2,&AO_square[i]);
				for (i=1; i<n_triangle; i++)
					move_left(3,&AO_triangle[i]); 
				for (i=1; i<n_circle; i++)
					move_left(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					move_left(6, &AO_fill[i]);
			}
			else if ((x>=11) && (x<=21) && (y>=181) && (y<=190)) /* navigate button : right scroll */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					move_right(1,&AO_line[i]);
				for (i=1; i<n_square; i++)
					move_right(2,&AO_square[i]);
				for (i=1; i<n_triangle; i++)
					move_right(3,&AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					move_right(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					move_right(6, &AO_fill[i]);
			}
			else if ((x>=181) && (x<=191) && (y>=0) && (y<=10)) /* navigate button : up scroll */
			{
				clear_canvas();
				for (i=1; i<n_line; i++)
					move_up(1,&AO_line[i]);
				for (i=1; i<n_square; i++)
					move_up(2,&AO_square[i]);
				for (i=1; i<n_triangle; i++)
					move_up(3, &AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					move_up(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					move_up(6, &AO_fill[i]);
			}
			else if ((x>=181) && (x<=191) && (y>=11) && (y<=21)) /* navigate button : down scroll */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					move_down(1,&AO_line[i]);
				for (i=1; i<n_square; i++)
					move_down(2,&AO_square[i]);
				for (i=1; i<n_triangle; i++)
					move_down(3, &AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					move_down(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					move_down(6, &AO_fill[i]);
			}
			else if ((x>=30) && (x<=40) && (y>=181) && (y<=190)) /* tool button : zoom in */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					ZoomIn(1, &AO_line[i]);
				for (i=1; i<n_square; i++)
					ZoomIn(2, &AO_square[i]);
				for (i=1; i<n_triangle; i++)
					ZoomIn(3, &AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					ZoomIn(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					ZoomIn(6, &AO_fill[i]);
			}
			else if ((x>=41) && (x<=51) && (y>=181) && (y<=190)) /* tool button : zoom out */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					ZoomOut(1, &AO_line[i]);
				for (i=1; i<n_square; i++)
					ZoomOut(2, &AO_square[i]);
				for (i=1; i<n_triangle; i++)
					ZoomOut(3, &AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					ZoomOut(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					ZoomOut(6, &AO_fill[i]);
			}
			else if ((x>=181) && (x<=191) && (y>=30) && (y<=40)) /* tool button : rotate clockwise */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					RotateClockWise(1, &AO_line[i]);
				for (i=1; i<n_square; i++)
					RotateClockWise(2, &AO_square[i]);
				for (i=1; i<n_triangle; i++)
					RotateClockWise(3, &AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					RotateClockWise(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					RotateClockWise(6, &AO_fill[i]);
			}
			else if ((x>=181) && (x<=191) && (y>=41) && (y<=51)) /* tool button : rotate unclockwise */
			{ 
				clear_canvas();
				for (i=1; i<n_line; i++)
					RotateUnClockWise(1, &AO_line[i]);
				for (i=1; i<n_square; i++)
					RotateUnClockWise(2, &AO_square[i]);
				for (i=1; i<n_triangle; i++)
					RotateUnClockWise(3, &AO_triangle[i]);
				for (i=1; i<n_circle; i++)
					RotateUnClockWise(4,&AO_circle[i]); 
				for (i=1; i<n_fill; i++)
					RotateUnClockWise(6, &AO_fill[i]);
			}
			draw_rect (0, 0, 180, 180, WHITE);
		}
		
	} while (exitprog != 1);	

	set_mode (TEXT_MODE);
	free(double_buffer);
	
	return 0;
}


