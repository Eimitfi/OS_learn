#include "util.h"

void clear_screen(void){
	const char *CLEAR_SCREEN_ANSI = "\x1B[1;1H\x1B[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}
