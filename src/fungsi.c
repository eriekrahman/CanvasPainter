#include "fungsi.h"

// =================================================================================
// Methode 		: swap
// Purpose		: To swap 2 objects
// Input		: a, b
// Output		: N/A
// =================================================================================
void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// =================================================================================
// Methode 		: wait
// Purpose		: To delay for certain ticks
// Input		: ticks
// Output		: N/A
// =================================================================================
void wait(int ticks) {
	word *my_clock = (word *) 0x0000046C;
	word start = *my_clock;
	while (*my_clock-start < ticks);
}

// =================================================================================
// Methode 		: char2int
// Purpose		: To convert character to integer
// Input		: Char
// Output		: Integer
// =================================================================================
int char2int(char C) {
	int result;
	
	if( C>='0' && C<='9' ) {
		result = C - '0';
	} else if ( C>='a' && C<='f' ) {
		result = C - 'a' + 10;
	} else if ( C>='A' && C<='F' ) {
		result = C - 'A' + 10;
	} else {
		result = 0;
	}
	return result;
}

// =================================================================================
// Methode 		: int2char
// Purpose		: To convert integer to character
// Input		: Integer
// Output		: Char
// =================================================================================
char int2char(int C) {
	return (C + '0');
}

