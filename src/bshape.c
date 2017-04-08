#include "bshape.h"
#include "trans.h"
#include "fungsi.h"


// =================================================================================
////////////////////////////////////////////////////////////////////////////////////
//////////////////                MAIN METHODS                 /////////////////////
////////////////////////////////////////////////////////////////////////////////////
// =================================================================================

fixed16_16 SIN_ACOS[1024];

// =================================================================================
// Methode 		: draw_line_n
// Purpose		: To render one line based on given Line object
// Input		: Line
// Output		: N/A
// =================================================================================
void draw_line_n(line l) 
{
    int isSteep = abs(l.b.y - l.a.y) > abs(l.b.x - l.a.x);
    int deltax, deltay, error, deltaerr;
    int x, y, ystep;
    byte color = 15;
    
    if (isSteep) 
	{
        swap(&l.a.x, &l.a.y);
        swap(&l.b.x, &l.b.y);
    }
    
    deltax = abs(l.b.x - l.a.x);
    deltay = abs(l.b.y - l.a.y);
    
    if (l.a.x < l.a.x)
    {
        error = 0;
        deltaerr = deltay;
        y = l.a.y;
        ystep = (l.a.y < l.b.y) ? 1 : -1;
        
        for (x = l.a.x; x <= l.b.x; x++) 
		{
            isSteep ? draw_pixel(y,x,color) : draw_pixel(x,y,color);
            error += deltaerr;
            if (deltax <= (error << 1)) 
			{
               y += ystep;
               error -= deltax;
            }
        }
    } 
	else 
    {
        error = 0;
        deltaerr = deltay;
        y = l.a.y;
        ystep = (l.a.y < l.b.y) ? 1 : -1;
        
        for (x = l.a.x; x >= l.b.x; x--) 
		{
            isSteep ? draw_pixel(y,x,color) : draw_pixel(x,y,color);
            error += deltaerr;
            if (deltax <= (error << 1)) 
			{
                y += ystep;
                error -= deltax;
            }
        }    
    }
}

// =================================================================================
// Methode 		: draw_line_point
// Purpose		: To render one line based on given two Point objects with specific color
// Input		: Point, Point, Color
// Output		: N/A
// =================================================================================
void draw_line_point(point a, point b, byte color) 
{
    int isSteep = abs(b.y - a.y) > abs(b.x - a.x);
    int deltax, deltay, error, deltaerr;
    int x, y, ystep;
    
    if (isSteep) 
	{
        swap(&a.x, &a.y);
        swap(&b.x, &b.y);
    }
    
    deltax = abs(b.x - a.x);
    deltay = abs(b.y - a.y);
    
    if (a.x < b.x)
    {
        error = 0;
        deltaerr = deltay;
        y = a.y;
        ystep = (a.y < b.y) ? 1 : -1;
        
        for (x = a.x; x <= b.x; x++) 
		{
            isSteep ? draw_pixel(y,x,color) : draw_pixel(x,y,color);
            error += deltaerr;
            if (deltax <= (error << 1)) 
			{
               y += ystep;
               error -= deltax;
            }
        }
    } 
	else 
    {
        error = 0;
        deltaerr = deltay;
        y = a.y;
        ystep = (a.y < b.y) ? 1 : -1;
        
        for (x = a.x; x >= b.x; x--) 
		{
            isSteep ? draw_pixel(y,x,color) : draw_pixel(x,y,color);
            error += deltaerr;
            if (deltax <= (error << 1)) 
			{
                y += ystep;
                error -= deltax;
            }
        }    
    }
}

// =================================================================================
// Methode 		: draw_line
// Purpose		: To render one line based on given coordinate (x1, y1) and (x2, y2) with specific color
// Input		: x1, y1, x2, y2, Color
// Output		: N/A
// =================================================================================
void draw_line(int ax, int ay, int bx, int by, byte color) 
{
	int isSteep = abs(by - ay) > abs(bx - ax);
    int deltax, deltay, error, deltaerr;
    int x, y, ystep;
    
    if (isSteep) 
	{
        swap(&ax, &ay);
        swap(&bx, &by);
    }
    
    deltax = abs(bx - ax);
    deltay = abs(by - ay);
    
    if (ax < bx)
    {
        error = 0;
        deltaerr = deltay;
        y = ay;
        ystep = (ay < by) ? 1 : -1;
        
        for (x = ax; x <= bx; x++) 
		{
            isSteep ? draw_pixel(y,x,color) : draw_pixel(x,y,color);
            error += deltaerr;
            if (deltax <= (error << 1)) 
			{
				y += ystep;
				error -= deltax;
            }
        }
    } 
	else 
    {
        error = 0;
        deltaerr = deltay;
        y = ay;
        ystep = (ay < by) ? 1 : -1;
        
        for (x = ax; x >= bx; x--) 
		{
            isSteep ? draw_pixel(y,x,color) : draw_pixel(x,y,color);
            error += deltaerr;
            if (deltax <= (error << 1)) 
			{
                y += ystep;
                error -= deltax;
            }
        }    
    }
}

// =================================================================================
// Methode 		: draw_line_canvas
// Purpose		: To render one line based on given coordinate (x1, y1) and (x2, y2) 
//				  with boundary of canvas whose coordinate (x3, y3) and (x4, y4) and specific color
// Input		: x1, y1, x2, y2, x3, y3, x4, y4, Color
// Output		: N/A
// =================================================================================
void draw_line_canvas(int x1, int y1, int x2, int y2, int xcanvas1, int ycanvas1, int xcanvas2, int ycanvas2, unsigned char color)
{
	float xx, yy, xx2, yy2;
	if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		draw_line(x1, y1, x2, y2, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		yy = (float)(xcanvas2 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;

		if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)) 
			draw_line(x1, y1, xcanvas2-1, yy, color);
		else 
			draw_line(x2, y2, xcanvas2-1, yy, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		yy = (float)(xcanvas1 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;

		if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
			draw_line(x1, y1, xcanvas1+1, yy, color);
		else
			draw_line(x2, y2, xcanvas1+1, yy, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
			draw_line(x1, y1, xx, ycanvas1+1, color);
		else
			draw_line(x2, y2, xx, ycanvas1+1, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
			draw_line(x1, y1, xx, ycanvas2-1, color);
		else
			draw_line(x2, y2, xx, ycanvas2-1, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		if ((xx >= xcanvas1) && (xx <= xcanvas2))
		{
			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xx, ycanvas1+1, color);
			else
				draw_line(x2, y2, xx, ycanvas1+1, color);
		}
		else
		{
			yy = (float)(xcanvas1 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xcanvas1+1, yy, color);
			else
				draw_line(x2, y2, xcanvas1+1, yy, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		if ((xx >= xcanvas1) && (xx <= xcanvas2))
		{
			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xx, ycanvas1+1, color);
			else
				draw_line(x2, y2, xx, ycanvas1+1, color);
		}
		else
		{
			yy = (float)(xcanvas2 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xcanvas2-1, yy, color);
			else
				draw_line(x2, y2, xcanvas2-1, yy, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		if ((xx >= xcanvas1) && (xx <= xcanvas2))
		{
			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xx, ycanvas2-1, color);
			else
				draw_line(x2, y2, xx, ycanvas2-1, color);
		}
		else
		{
			yy = (float)(xcanvas1 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xcanvas1+1, yy, color);
			else
				draw_line(x2, y2, xcanvas1+1, yy, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		if ((xx >= xcanvas1) && (xx <= xcanvas2))
		{
			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xx, ycanvas2-1, color);
			else
				draw_line(x2, y2, xx, ycanvas2-1, color);
		}
		else
		{
			yy = (float)(xcanvas2 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			if ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 0))
				draw_line(x1, y1, xcanvas2-1, yy, color);
			else
				draw_line(x2, y2, xcanvas2-1, yy, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2))
			draw_line(xx, ycanvas1+1, xcanvas2-1, yy2, color);
		else if (xx <= xcanvas1)
		{
			yy = (float)(xcanvas1 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas1+1, yy, xcanvas2-1, yy2, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2))
			draw_line(xx, ycanvas2-1, xcanvas2-1, yy2, color);
		else if (xx <= xcanvas1)
		{
			yy = (float)(xcanvas1 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas1+1, yy, xcanvas2-1, yy2, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		xx2 = (float)(ycanvas2 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2)){
			draw_line(xx, ycanvas1+1, xx2, ycanvas2-1, color);
		}
		else if (xx2 > xcanvas1)
		{
			yy = (float)(xcanvas1 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas1+1, yy, xx2, ycanvas2-1, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		yy2 = (float)(xcanvas1 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2))
			draw_line(xx, ycanvas1+1, xcanvas1+1, yy2, color);
		else if (xx >= xcanvas2)
		{
			yy = (float)(xcanvas2 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas2-1, yy, xcanvas1+1, yy2, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		yy2 = (float)(xcanvas1 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2))
			draw_line(xx, ycanvas2-1, xcanvas1+1, yy2, color);
		else if (xx >= xcanvas2)
		{
			yy = (float)(xcanvas2 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas2-1, yy, xcanvas1+1, yy2, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		xx2 = (float)(ycanvas2 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2))
			draw_line(xx, ycanvas1+1, xx2, ycanvas2-1, color);
		else if (xx2 < xcanvas2)
		{
			yy = (float)(xcanvas2 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas2-1, yy, xx2, ycanvas2-1, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		xx2 = (float)(ycanvas1 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2)){
			draw_line(xx, ycanvas2-1, xx2, ycanvas1+1, color);
		}
		else if (xx2 > xcanvas1)
		{
			yy = (float)(xcanvas1 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas1+1, yy, xx2, ycanvas1+1, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2)))
	{
		xx = (float)(ycanvas2 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		xx2 = (float)(ycanvas1 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		if ((xx >= xcanvas1) && (xx <= xcanvas2)){
			draw_line(xx, ycanvas2-1, xx2, ycanvas1+1, color);
		}
		else if (xx2 < xcanvas2)
		{
			yy = (float)(xcanvas2 - x1);
			yy = yy / (float) (x2 - x1);
			yy = yy * (float) (y2 - y1);
			yy = yy + (float)y1;

			draw_line(xcanvas2-1, yy, xx2, ycanvas1+1, color);
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 8) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 1)))
	{
		yy = (float)(xcanvas1 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;
		
		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		if ((yy >= ycanvas1) && (yy <= ycanvas2)){
			if ((yy2 >= ycanvas1) && (yy2 <= ycanvas2))
				draw_line(xcanvas1+1, yy, xcanvas2-1, yy2, color);
			else
			{
				xx2 = (float)(ycanvas2 - y1);
				xx2 = xx2 / (float) (y2 - y1);
				xx2 = xx2 * (float) (x2 - x1);
				xx2 = xx2 + (float)x1;
				draw_line(xcanvas1+1, yy, xx2, ycanvas2-1, color);
			}
		}
		else
		{
			xx = (float)(ycanvas1 - y1);
			xx = xx / (float) (y2 - y1);
			xx = xx * (float) (x2 - x1);
			xx = xx + (float)x1;
			
			if ((yy2 >= ycanvas1) && (yy2 <= ycanvas2))
				draw_line(xx, ycanvas1+1, xcanvas2-1, yy2, color);
			else
			{
				xx2 = (float)(ycanvas2 - y1);
				xx2 = xx2 / (float) (y2 - y1);
				xx2 = xx2 * (float) (x2 - x1);
				xx2 = xx2 + (float)x1;
				draw_line(xx, ycanvas1+1, xx2, ycanvas2-1, color);
			}
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 6) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 3)))
	{
		yy = (float)(xcanvas1 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;
		
		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		if ((yy >= ycanvas1) && (yy <= ycanvas2))
		{
			if ((yy2 >= ycanvas1) && (yy2 <= ycanvas2))
				draw_line(xcanvas1+1, yy, xcanvas2-1, yy2, color);
			else
			{
				xx2 = (float)(ycanvas1 - y1);
				xx2 = xx2 / (float) (y2 - y1);
				xx2 = xx2 * (float) (x2 - x1);
				xx2 = xx2 + (float)x1;
				draw_line(xcanvas1+1, yy, xx2, ycanvas1+1, color);
			}
		}
		else
		{
			xx = (float)(ycanvas2 - y1);
			xx = xx / (float) (y2 - y1);
			xx = xx * (float) (x2 - x1);
			xx = xx + (float)x1;
			
			if ((yy2 >= ycanvas1) && (yy2 <= ycanvas2))
				draw_line(xx, ycanvas2-1, xcanvas2-1, yy2, color);
			else
			{
				xx2 = (float)(ycanvas1 - y1);
				xx2 = xx2 / (float) (y2 - y1);
				xx2 = xx2 * (float) (x2 - x1);
				xx2 = xx2 + (float)x1;
				draw_line(xx, ycanvas2-1, xx2, ycanvas1+1, color);
			}
		}
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2)))
	{
		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;

		xx2 = (float)(ycanvas2 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		draw_line(xx, ycanvas1+1, xx2, ycanvas2-1, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4)))
	{
		yy = (float)(xcanvas1 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;

		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;
		
		draw_line(xcanvas1+1, yy, xcanvas2-1, yy2, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4)))
	{
		yy = (float)(xcanvas1 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;

		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;
		
		if ((yy >= ycanvas1) && (yy <= ycanvas2))
			draw_line(xcanvas1+1, yy, xx, ycanvas1+1, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 2) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5)))
	{
		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;

		xx = (float)(ycanvas1 - y1);
		xx = xx / (float) (y2 - y1);
		xx = xx * (float) (x2 - x1);
		xx = xx + (float)x1;
		
		if ((yy2 >= ycanvas1) && (yy2 <= ycanvas2))
			draw_line(xcanvas2-1, yy2, xx, ycanvas1+1, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 4) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7)))
	{
		yy = (float)(xcanvas1 - x1);
		yy = yy / (float) (x2 - x1);
		yy = yy * (float) (y2 - y1);
		yy = yy + (float)y1;

		xx2 = (float)(ycanvas2 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		if ((yy >= ycanvas1) && (yy <= ycanvas2))
			draw_line(xcanvas1+1, yy, xx2, ycanvas2-1, color);
	}
	else if (((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5)) ||
			 ((get_section(x1,y1,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 5) && (get_section(x2,y2,xcanvas1,ycanvas1,xcanvas2,ycanvas2) == 7)))
	{
		yy2 = (float)(xcanvas2 - x1);
		yy2 = yy2 / (float) (x2 - x1);
		yy2 = yy2 * (float) (y2 - y1);
		yy2 = yy2 + (float)y1;

		xx2 = (float)(ycanvas2 - y1);
		xx2 = xx2 / (float) (y2 - y1);
		xx2 = xx2 * (float) (x2 - x1);
		xx2 = xx2 + (float)x1;
		
		if ((yy2 >= ycanvas1) && (yy2 <= ycanvas2))
			draw_line(xcanvas2-1, yy2, xx2, ycanvas2-1, color);
	}	
}

// =================================================================================
// Methode 		: draw_line_move
// Purpose		: To render one line based on given two Point with specific length and color
// Input		: Point, Point, Length, Color
// Output		: N/A
// =================================================================================
void draw_line_move(point origin, point target, int length, byte color) 
{
	int isSteep = abs(target.y - origin.y) > abs(target.x - origin.x);
	int deltax, deltay, error, deltaerr;
	int lengthnow, x, y, ystep;
	Queue buffer;
	pointc m;
	
	CreateEmpty(&buffer, length);

	if (isSteep) 
	{
		swap(&origin.x, &origin.y);
		swap(&target.x, &target.y);
	}

	deltax = abs(target.x - origin.x);
	deltay = abs(target.y - origin.y);

	if (origin.x < target.x)
	{
		error = 0;
		deltaerr = deltay;
		y = origin.y;
		ystep = (origin.y < target.y) ? 1 : -1;

		for (x = origin.x; x <= target.x; x++) 
		{			
			if (isSteep) 
			{	
				if (x >= (origin.x + length))
				{
					DelQ(&buffer, &m);
					draw_pixel(m.x, m.y, 16);
				}
				draw_pixel(y,x,color);
				set_pointc(y, x, color, &m); 
				AddQ(&buffer, m);
			}
			else 
			{		
				if (x >= (origin.x + length))
				{
					DelQ(&buffer, &m);
					draw_pixel(m.x,m.y,16);
				}
				draw_pixel(x,y,color);
				set_pointc(x, y, color, &m); 
				AddQ(&buffer, m);
			}
		  
			error += deltaerr;
			if (deltax <= (error << 1)) 
			{
				y += ystep;
				error -= deltax;
			}  
			wait(1);
		}
	} 
	else 
	{
		error = 0;
		deltaerr = deltay;
		y = origin.y;
		ystep = (origin.y < target.y) ? 1 : -1;

		for (x = origin.x; x >= target.x; x--) 
		{
			if (isSteep) 
			{	
				if (x <= (origin.x - length))
				{
					DelQ(&buffer, &m);
					draw_pixel(m.x,m.y,16);
				}
				draw_pixel(y,x,color);
				set_pointc(y, x, color, &m); 
				AddQ(&buffer, m);
			}
			else 
			{		
				if (x <= (origin.x - length))
				{
					DelQ(&buffer, &m);
					draw_pixel(m.x,m.y,16);
				}
				draw_pixel(x,y,color);
				set_pointc(x, y, color, &m); 
				AddQ(&buffer, m);
			}
			error += deltaerr;
			if (deltax <= (error << 1)) 
			{
				y += ystep;
				error -= deltax;
			}
			wait(1);
		}
	}
	while (!IsEmpty(buffer))
	{
		DelQ(&buffer, &m);
		draw_pixel(m.x,m.y,16);
	}
}

// =================================================================================
// Methode 		: draw_circle
// Purpose		: To render one circle based on given Point and radius with specific side color
// Input		: Point, Radius, Color
// Output		: N/A
// =================================================================================
void draw_circle(point p, int radius, byte color)
{
	word dxoffset,dyoffset,offset = (p.y<<8)+(p.y<<6)+p.x;
	fixed16_16 n=0,invradius=(1/(float)radius)*0x10000L;  
	byte *li = (byte*) 0xA0000000L;
	int dx=0,dy=radius-1;
	int i;	
	
	// inisialisasi tabel sinus
	for(i=0;i<1024;i++)
	{
		SIN_ACOS[i]=sin(acos((float)i/1024))*0x10000L;
	}

	while (dx<=dy)
	{
		dxoffset = (dx<<8) + (dx<<6);
		dyoffset = (dy<<8) + (dy<<6);

		li[offset+dy-dxoffset] = color; 
		li[offset+dx-dyoffset] = color; 
		li[offset-dx-dyoffset] = color;  
		li[offset-dy-dxoffset] = color;
		li[offset-dy+dxoffset] = color;
		li[offset-dx+dyoffset] = color; 
		li[offset+dx+dyoffset] = color; 
		li[offset+dy+dxoffset] = color;
		dx++;
		n+=invradius;
		dy = (int)((radius * SIN_ACOS[(int)(n>>6)]) >> 16);
	}
}

// =================================================================================
// Methode 		: draw_circle_canvas
// Purpose		: To render one circle based on given coordinate (x1, y1) as center and 
//				  (x2, y2) as one of outer point with canvas boundary and specific side color
// Input		: x1, y1, x2, y2, Color
// Output		: N/A
// =================================================================================
void draw_circle_canvas(int a, int b, int c, int d, byte color)
{
	word dxoffset,dyoffset,offset = (b<<8)+(b<<6)+a;
	int radius = sqrt(pow(c-a,2)+pow(d-b,2));
	fixed16_16 n=0,invradius=(1/(float)radius)*0x10000L;  
	byte *li = (byte*) 0xA0000000L;
	int dx=0,dy=radius-1;
	int i;	
	
	// inisialisasi tabel sinus
	for(i=0;i<1024;i++)
	{
		SIN_ACOS[i]=sin(acos((float)i/1024))*0x10000L;
	}
  
	while (dx<=dy)
	{
		dxoffset = (dx<<8) + (dx<<6);
		dyoffset = (dy<<8) + (dy<<6);

		if ((a+dy+1 >= MIN_WIDTH_CANVAS) && (a+dy+1 <= MAX_WIDTH_CANVAS) && (b-dx >= MIN_HEIGHT_CANVAS) && (b-dx <= MAX_HEIGHT_CANVAS))
			li[offset+dy-dxoffset] = color;
		if ((a+dx >= MIN_WIDTH_CANVAS) && (a+dx <= MAX_WIDTH_CANVAS) && (b-dy-1 >= MIN_HEIGHT_CANVAS) && (b-dy-1 <= MAX_HEIGHT_CANVAS))
			li[offset+dx-dyoffset] = color;
		if ((a-dx >= MIN_WIDTH_CANVAS) && (a-dx <= MAX_WIDTH_CANVAS) && (b-dy-1 >= MIN_HEIGHT_CANVAS) && (b-dy-1 <= MAX_HEIGHT_CANVAS))
			li[offset-dx-dyoffset] = color;   
		if ((a-dy-1 >= MIN_WIDTH_CANVAS) && (a-dy-1 <= MAX_WIDTH_CANVAS) && (b-dx >= MIN_HEIGHT_CANVAS) && (b-dx <= MAX_HEIGHT_CANVAS))
			li[offset-dy-dxoffset] = color;
		if ((a-dy-1 >= MIN_WIDTH_CANVAS) && (a-dy-1 <= MAX_WIDTH_CANVAS) && (b+dx >= MIN_HEIGHT_CANVAS) && (b+dx <= MAX_HEIGHT_CANVAS))
			li[offset-dy+dxoffset] = color;
		if ((a-dx >= MIN_WIDTH_CANVAS) && (a-dx <= MAX_WIDTH_CANVAS) && (b+dy+1 >= MIN_HEIGHT_CANVAS) && (b+dy+1 <= MAX_HEIGHT_CANVAS))
			li[offset-dx+dyoffset] = color;
		if ((a+dx >= MIN_WIDTH_CANVAS) && (a+dx <= MAX_WIDTH_CANVAS) && (b+dy+1 >= MIN_HEIGHT_CANVAS) && (b+dy+1 <= MAX_HEIGHT_CANVAS))
			li[offset+dx+dyoffset] = color; 
		if ((a+dy+1 >= MIN_WIDTH_CANVAS) && (a+dy+1 <= MAX_WIDTH_CANVAS) && (b+dx >= MIN_HEIGHT_CANVAS) && (b+dx <= MAX_HEIGHT_CANVAS))
			li[offset+dy+dxoffset] = color;

		dx++;
		n+=invradius;
		dy = (int)((radius * SIN_ACOS[(int)(n>>6)]) >> 16);
	}
}

// =================================================================================
// Methode 		: draw_circle_fill
// Purpose		: To render one circle based on given Point and radius with specific fill color
// Input		: Point, Radius, Color
// Output		: N/A
// =================================================================================
void draw_circle_fill(point p, int radius, byte color)
{
	fixed16_16 n=0,invradius=(1/(float)radius)*0x10000L;
	int dx=0,dy=radius-1,i;
	word dxoffset,dyoffset,offset = (p.y<<8)+(p.y<<6)+p.x;
	byte *li = (byte*) 0xA0000000L;

	// inisialisasi tabel sinus
	for(i=0;i<1024;i++)
	{
		SIN_ACOS[i]=sin(acos((float)i/1024))*0x10000L;
	}

	while (dx<=dy)
	{
		dxoffset = (dx<<8) + (dx<<6);
		dyoffset = (dy<<8) + (dy<<6);
		for(i=dy;i>=dx;i--,dyoffset-=MAX_WIDTH)
		{
			li[offset+i -dxoffset] = color;  
			li[offset+dx-dyoffset] = color;  
			li[offset-dx-dyoffset] = color;  
			li[offset-i -dxoffset] = color; 
			li[offset-i +dxoffset] = color;  
			li[offset-dx+dyoffset] = color;  
			li[offset+dx+dyoffset] = color;  
			li[offset+i +dxoffset] = color; 
		}
		dx++;
		n+=invradius;
		dy = (int)((radius * SIN_ACOS[(int)(n>>6)]) >> 16);
	}     
}

// =================================================================================
// Methode 		: draw_triangle
// Purpose		: To render one triangle based on given (x1, y1) as coordinate for the first corner
//				  and (x2, y2) as coordinate for second corner with specific side color 
// Input		: x1, y1, x2, y2, Color
// Output		: N/A
// =================================================================================
void draw_triangle(int a, int b, int c, int d, byte color)
{
	draw_line((a+c)/2, b, a, d, color);
	draw_line((a+c)/2, b, c, d, color);
	draw_line(c, d, a, d, color);
}

// =================================================================================
// Methode 		: draw_triangle_canvas
// Purpose		: To render one triangle based on given (x1, y1) as coordinate for the first corner
//				  and (x2, y2) as coordinate for second corner with canvas boundary and specific side color 
// Input		: x1, y1, x2, y2, Color
// Output		: N/A
// =================================================================================
void draw_triangle_canvas(int a, int b, int c, int d, byte color)
{
	draw_line_canvas((a+c)/2, b, a, d, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
	draw_line_canvas((a+c)/2, b, c, d, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
	draw_line_canvas(c, d, a, d, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
}

// =================================================================================
// Methode 		: draw_rect_point
// Purpose		: To render one rectangle based on given 2 Points as corners with specific side color 
// Input		: Point, Point, Color
// Output		: N/A
// =================================================================================
void draw_rect_point(point a, point b, byte color)
{
   point c,d;
   c.x = a.x; c.y = b.y;
   d.x = b.x; d.y = a.y;
   draw_line_point(a, c, color);
   draw_line_point(c, b, color);
   draw_line_point(b, d, color);
   draw_line_point(d, a, color);
}

// =================================================================================
// Methode 		: draw_rect
// Purpose		: To render one rectangle based on given (x1, y1) as first corner and
//				  (x2, y2) as second corner with specific side color 
// Input		: Point, Point, Color
// Output		: N/A
// =================================================================================
void draw_rect(int a, int b, int c, int d, byte color)
{
	point p1,p2,p3,p4;

	set_point(a,b,&p1);
	set_point(c,d,&p2);

	p3.x = p1.x; p3.y = p2.y;
	p4.x = p2.x; p4.y = p1.y;
	draw_line_point(p1, p3, color);
	draw_line_point(p3, p2, color);
	draw_line_point(p2, p4, color);
	draw_line_point(p4, p1, color);
}

// =================================================================================
// Methode 		: draw_rect_fill
// Purpose		: To render one rectangle based on given (x1, y1) as first corner and
//				  (x2, y2) as second corner with specific fill color
// Input		: Point, Point, Color
// Output		: N/A
// =================================================================================
void draw_rect_fill(int a, int b, int c, int d, byte color)
{
	int i;	 
	for (i=b;i<=d;i++)
	{
		draw_line(a,i,c,i,color);
	}
}

// =================================================================================
// Methode 		: draw_rect_canvas
// Purpose		: To render one rectangle based on given (x1, y1) as first corner and
//				  (x2, y2) as second corner with canvas boundary and specific fill color
// Input		: Point, Point, Color
// Output		: N/A
// =================================================================================
void draw_rect_canvas(int a, int b, int c, int d, byte color)
{
	draw_line_canvas(a, b, c, b, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
	draw_line_canvas(a, b, a, d, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
	draw_line_canvas(a, d, c, d, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
	draw_line_canvas(c, b, c, d, MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, color);
}

// =================================================================================
////////////////////////////////////////////////////////////////////////////////////
//////////////////              SUPPORTING TOOLS               /////////////////////
////////////////////////////////////////////////////////////////////////////////////
// =================================================================================

void fill_all(byte color) 
{
	int dlaststate = 0;
	int laststate = 0;
	int state = 0;
	int tipShape = 0;
	int x = 0;
	int y = 3;
	int up1 = 0;
	int down1 = 0;
	int up2 = 0;
	int down2 = 0;
	
	int a;
	int b;
	
	for (y = 0; y < 200; y++) 
	{
		for (x = 0; x < 320; x++) 
		{	
			if (state == 0)
			{			
				tipShape = 0;					
				if (get_color(x,y) == 10)
				{
					state = 1;
					up1 = (get_color(x-1,y-1) == 10) || (get_color(x,y-1) == 10) || (get_color(x+1,y-1) == 10);
					down1 = (get_color(x-1,y+1) == 10) || (get_color(x,y+1) == 10) || (get_color(x+1,y+1) == 10);
					
					a = (get_color(x,y-1) == 10) && (get_color(x-1,y+1) == 10) && (get_color(x+1,y+1) == 10) && (get_color(x,y+1) != 10) && (get_color(x,y-2) == 0);
					b = (get_color(x,y+1) == 10) && (get_color(x-1,y-1) == 10) && (get_color(x+1,y-1) == 10) && (get_color(x,y+1) != 10) && (get_color(x,y+2) == 0);
					
					if ((up1 != down1) || a || b)
					{
						tipShape = 1;
					}
				}			
				
				dlaststate = 0;
				laststate = 0;
			} 
			else if (state == 1)
			{					
				if (get_color(x,y) == 10)
				{									
					state = 3;
				} 
				else if (get_color(x,y) == 0)
				{
					if (tipShape == 1)
					{
						state = laststate;
					} 
					else 
					{					
						if (laststate == 2)
						{							
							state = 0;
						}
						else 
						{
							draw_pixel(x,y,color);
							state = 2; 
						}
					}
				}
				
				dlaststate = laststate;
				laststate = 1;				
			} 
			else if (state == 2)
			{
				if (get_color(x,y) == 10)
				{
					state = 1;
				} 
				else 
				{
					draw_pixel(x,y,color);
				}
				
				dlaststate = laststate;
				laststate = 2;
			} 
			else if (state == 3)
			{
				if (get_color(x,y) == 10)
				{
					// do nothing
				} 
				else 
				{
					up2 = (get_color(x-2,y-1) == 10) || (get_color(x-1,y-1) == 10) || (get_color(x,y-1) == 10);
					down2 = (get_color(x-2,y+1) == 10) || (get_color(x-1,y+1) == 10) || (get_color(x,y+1) == 10);
										
					if ((up2 != up1) || (down2 != down1))
					{
						if (dlaststate == 0)
						{
							state = 2;
						} 
						else 
						{
							state = 0;
						}
					} 
					else 
					{
						state = dlaststate;
					}
				}
				
				dlaststate = laststate;
				laststate = 3;							
			}
		}
		
		tipShape = 0;		
		state = 0;
		up1 = 0;
		down1 = 0;
		up2 = 0;
		down2 = 0;
		a = 0;
		b = 0;
	}
}

void fill_rect(point p, point q, byte color) 
{
	int dlaststate = 0;
	int laststate = 0;
	int state = 0;
	int tipShape = 0;
	int x = 0;
	int y = 3;
	int up1 = 0;
	int down1 = 0;
	int up2 = 0;
	int down2 = 0;
	
	int a;
	int b;
	
	int px,py,qx,qy;
	if (p.x <= q.x)
	{
		px = p.x;
		qx = q.x;
	} 
	else 
	{
		px = q.x;
		qx = p.x;		
	}
	if (p.y <= q.y)
	{
		py = p.y;
		qy = q.y;
	} 
	else 
	{
		py = q.y;
		qy = p.y;	
	}	
	
	for (y = py; y <= qy; y++) 
	{
		for (x = px; x <= qx; x++) 
		{
			if (state == 0)
			{			
				tipShape = 0;					
				if (get_color(x,y) == 10)
				{
					state = 1;
					up1 = (get_color(x-1,y-1) == 10) || (get_color(x,y-1) == 10) || (get_color(x+1,y-1) == 10);
					down1 = (get_color(x-1,y+1) == 10) || (get_color(x,y+1) == 10) || (get_color(x+1,y+1) == 10);
					
					a = (get_color(x,y-1) == 10) && (get_color(x-1,y+1) == 10) && (get_color(x+1,y+1) == 10) && (get_color(x,y+1) != 10) && (get_color(x,y-2) == 0);
					b = (get_color(x,y+1) == 10) && (get_color(x-1,y-1) == 10) && (get_color(x+1,y-1) == 10) && (get_color(x,y+1) != 10) && (get_color(x,y+2) == 0);
					
					if ((up1 != down1) || a || b)
					{
						tipShape = 1;
					}
				}			
				
				dlaststate = 0;
				laststate = 0;
			} 
			else if (state == 1)
			{
				if (get_color(x,y) == 10)
				{									
					state = 3;
				} 
				else if (get_color(x,y) == 0)
				{
					if (tipShape == 1)
					{
						state = laststate;
					} 
					else 
					{					
						if (laststate == 2)
						{							
							state = 0;
						}
						else 
						{
							draw_pixel(x,y,color);
							state = 2; 
						}
					}
				}
				
				dlaststate = laststate;
				laststate = 1;				
			} 
			else if (state == 2)
			{
				if (get_color(x,y) == 10)
				{
					state = 1;
				} 
				else 
				{
					draw_pixel(x,y,color);
				}
				
				dlaststate = laststate;
				laststate = 2;
			} 
			else if (state == 3)
			{
				if (get_color(x,y) == 10)
				{
					// do nothing					
				} 
				else 
				{
					up2 = (get_color(x-2,y-1) == 10) || (get_color(x-1,y-1) == 10) || (get_color(x,y-1) == 10);
					down2 = (get_color(x-2,y+1) == 10) || (get_color(x-1,y+1) == 10) || (get_color(x,y+1) == 10);
										
					if ((up2 != up1) || (down2 != down1))
					{
						if (dlaststate == 0)
						{
							state = 2;
						} 
						else 
						{
							state = 0;
						}
					} 
					else 
					{
						state = dlaststate;
					}
				}
				
				dlaststate = laststate;
				laststate = 3;							
			}
		}
		
		tipShape = 0;		
		state = 0;
		up1 = 0;
		down1 = 0;
		up2 = 0;
		down2 = 0;
		a = 0;
		b = 0;
	}
}

void floodfill(int x, int y, int c) 
{
	int count = 0;
	flood_fill(x,y,c,&count);
}

int flood_fill(int x, int y, byte color)
{   
	int fx,fy;
	byte colortmp,color1;

	fx = x; fy = y;
	colortmp = get_color(x,y);
	color1 = colortmp;
	
	if ((x>=MIN_WIDTH_CANVAS) && (x<=MAX_WIDTH_CANVAS) && (y>=MIN_HEIGHT_CANVAS) && (y<=MAX_HEIGHT_CANVAS))
	{ 
		if(colortmp == 0) 
		{
			draw_pixel(x,y,color);			 
			flood_fill(x, y-1, color);
			flood_fill(x, y+1, color);
			flood_fill(x+1, y, color);
			flood_fill(x-1, y, color);
		}
	}
	return 0;
}

void draw_screen_background(unsigned char color)
{
	int i;
	unsigned char *fb=(unsigned char *)0xA0000000L;
	memset(fb, color, MAX_WIDTH*MAX_HEIGHT);
}

void clear_all(int shape, Objek *o)
{
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, BLACK);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  BLACK);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  BLACK);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, BLACK);
}

void ZoomIn(int shape, Objek *o)
{
	point p1, p2, centerPoint;
	Matrix M;
	SetMatrix(&M, 1.2, 0, 0, 1.2);
	
	set_point(o->x1, o->y1, &p1);
	set_point(o->x2, o->y2, &p2);
	set_point((MAX_WIDTH_CANVAS-MIN_WIDTH_CANVAS)/2,(MAX_HEIGHT_CANVAS-MIN_HEIGHT_CANVAS)/2, &centerPoint);
	
	TransformPoint(&p1, centerPoint, M);
	o->x1 = p1.x;
	o->y1 = p1.y;
	
	TransformPoint(&p2, centerPoint, M);
	o->x2 = p2.x;
	o->y2 = p2.y;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

void ZoomOut(int shape, Objek *o)
{
	point p1, p2, centerPoint;
	Matrix M;
	SetMatrix(&M, 0.83, 0, 0, 0.83);
	
	set_point(o->x1, o->y1, &p1);
	set_point(o->x2, o->y2, &p2);
	set_point((MAX_WIDTH_CANVAS-MIN_WIDTH_CANVAS)/2,(MAX_HEIGHT_CANVAS-MIN_HEIGHT_CANVAS)/2, &centerPoint);
	
	TransformPoint(&p1, centerPoint, M);
	o->x1 = p1.x;
	o->y1 = p1.y;
	
	TransformPoint(&p2, centerPoint, M);
	o->x2 = p2.x;
	o->y2 = p2.y;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

void RotateClockWise(int shape, Objek *o)
{
	point p1, p2, centerPoint;
	
	set_point(o->x1, o->y1, &p1);
	set_point(o->x2, o->y2, &p2);
	set_point((MAX_WIDTH_CANVAS-MIN_WIDTH_CANVAS)/2,(MAX_HEIGHT_CANVAS-MIN_HEIGHT_CANVAS)/2, &centerPoint);
	
	RotatePointBasedOnGivenPoint(&p1, centerPoint, 30);
	o->x1 = p1.x;
	o->y1 = p1.y;
	
	RotatePointBasedOnGivenPoint(&p2, centerPoint, 30);
	o->x2 = p2.x;
	o->y2 = p2.y;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

void RotateUnClockWise(int shape, Objek *o)
{
	point p1, p2, centerPoint;
	
	set_point(o->x1, o->y1, &p1);
	set_point(o->x2, o->y2, &p2);
	set_point((MAX_WIDTH_CANVAS-MIN_WIDTH_CANVAS)/2,(MAX_HEIGHT_CANVAS-MIN_HEIGHT_CANVAS)/2, &centerPoint);
	
	RotatePointBasedOnGivenPoint(&p1, centerPoint, -30);
	o->x1 = p1.x;
	o->y1 = p1.y;
	
	RotatePointBasedOnGivenPoint(&p2, centerPoint, -30);
	o->x2 = p2.x;
	o->y2 = p2.y;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

void move_right(int shape, Objek *o)
{
	o->x1 = o->x1-5;
	o->x2 = o->x2-5;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

void move_left(int shape, Objek *o)
{
	o->x1 = o->x1+5;
	o->x2 = o->x2+5;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6){
		flood_fill(o->x1, o->y1, o->color);
	}
}

void move_up(int shape, Objek *o)
{
	o->y1 = o->y1+5;
	o->y2 = o->y2+5;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

void move_down(int shape, Objek *o)
{
	o->y1 = o->y1-5;
	o->y2 = o->y2-5;
	
	if (shape == 1)
		draw_line_canvas(o->x1, o->y1, o->x2, o->y2,  MIN_WIDTH_CANVAS, MIN_HEIGHT_CANVAS, MAX_WIDTH_CANVAS, MAX_HEIGHT_CANVAS, o->color);
	else if (shape == 2)
		draw_rect_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 3)
		draw_triangle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 4)
		draw_circle_canvas(o->x1, o->y1, o->x2, o->y2,  o->color);
	else if (shape == 6)
		flood_fill(o->x1, o->y1, o->color);
}

int get_section(int x, int y, int xcanvas1, int ycanvas1, int xcanvas2, int ycanvas2)
{
	if ((x >= xcanvas1) && (x <= xcanvas2) && (y >= ycanvas1) && (y <= ycanvas2))
		return 0;
	else if ((x < xcanvas1) && (y < ycanvas1))
		return 1;
	else if ((x >= xcanvas1) && (x <= xcanvas2) && (y < ycanvas1))
		return 2;
	else if ((x > xcanvas2) && (y < ycanvas1))
		return 3;
	else if ((x < xcanvas1) && (y >= ycanvas1) && (y <= ycanvas2))
		return 4;
	else if ((x > xcanvas2) && (y >= ycanvas1) && (y <= ycanvas2))
		return 5;
	else if ((x < xcanvas1) && (y > ycanvas2))
		return 6;
	else if ((x >= xcanvas1) && (x <= xcanvas2) && (y > ycanvas2))
		return 7;
	else if ((x > xcanvas2) && (y > ycanvas2))
		return 8;
}

