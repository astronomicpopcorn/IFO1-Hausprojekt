#include "utilities.h";
#include "windowinteractions.h"
#include "constants.h"
#include "datastructures.h"

#include <stdio.h>


void render_test() {
	Vector2D console_size = get_console_size();

	char display_string[max_display_string_length] = "\033[H";
	int ctr = 3;

	//skip last row to leave space for cursor
	for (int y = 0; y < console_size.y - 1; y++) {
		for (int x = 0; x < console_size.x; x++) {
			if (ctr % 2 == 0) {
				display_string[ctr] = 'X';
			}
			else {
				display_string[ctr] = ' ';
			}
			ctr++;
		}
		display_string[ctr] = '\n';
		ctr++;
	}
	display_string[ctr] = '\0';

	printf("%s", display_string);
}