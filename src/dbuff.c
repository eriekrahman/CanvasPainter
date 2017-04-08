#include "dbuff.h"

void save_double_buffer(unsigned char *double_buffer, int x1, int y1, int x2, int y2){
	unsigned char *fb=(unsigned char *)0xA0000000L;
	int offset, min_x, max_x, min_y, max_y, y, dx;
	if (x1 <= x2){
		min_x = x1;
		max_x = x2;
	} else {
		min_x = x2;
		max_x = x1;
	}
	if (y1 <= y2){
		min_y = y1;
		max_y = y2;
	} else {
		min_y = y2;
		max_y = y1;
	}
	dx = max_x - min_x + 1;
	for (y = min_y; y <= max_y; y++){
		offset = (y<<8) + (y<<6) + min_x;
		memcpy(&double_buffer[offset], &fb[offset], dx);
	}
}

void draw_double_buffer(unsigned char *double_buffer, int x1, int y1, int x2, int y2){
	unsigned char *fb=(unsigned char *)0xA0000000L;
	int offset, min_x, max_x, min_y, max_y, y, dx;
	if (x1 <= x2){
		min_x = x1;
		max_x = x2;
	} else {
		min_x = x2;
		max_x = x1;
	}
	if (y1 <= y2){
		min_y = y1;
		max_y = y2;
	} else {
		min_y = y2;
		max_y = y1;
	}
	dx = max_x - min_x + 1;
	for (y = min_y; y <= max_y; y++){
		offset = (y<<8) + (y<<6) + min_x;
		memcpy(&fb[offset], &double_buffer[offset], dx);
	}
}
