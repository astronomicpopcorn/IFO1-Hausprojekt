#include "utilities.h";
#include "windowinteractions.h"
#include "constants.h"
#include "datastructures.h"

#include <stdio.h>
#include <string.h>


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

void render_single_element_test(windowelement element) {
	Vector2D console_size = get_console_size();

	char display_string[max_display_string_length] = "\033[H";
	int x, y, offset, i = 0, ctr = 3;

	while (element.default_color[i] != '\0') {
		display_string[ctr] = element.default_color[i];
		ctr++;
		i++;
	}

	//skip last row to leave space for cursor
	for (y = 0; y < console_size.y - 1; y++) {
		for (x = 0; x < console_size.x; x++) {
			if (x >= element.position.x && y == element.position.y) {
				offset = x - element.position.x;
				if (offset < element.width && offset < strlen(element.label)) {
					display_string[ctr] = element.label[offset];
				}
				else {
					display_string[ctr] = ' ';
				}
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

void render(windowelement *element_array, int array_length, const char* background_color) {
	Vector2D console_size = get_console_size();
	
	char display_string[max_display_string_length] = "\033[H";
	int x, y, offset, i, j, ctr = 3;

	//skip last row to leave space for cursor
	for (y = 0; y < console_size.y - 1; y++) {
		for (x = 0; x < console_size.x; x++) {
			display_string[ctr] = ' ';
			for (i = 0; i < array_length; i++) {
				offset = x - element_array[i].position.x;
				if (element_array[i].position.y == y && element_array[i].position.x <= x && offset <= element_array[i].width) {
					if (x == element_array[i].position.x) {
						if (element_array[i].active) {
							for (j = 0; element_array[i].active_color[j] != '\0'; j++) {
								display_string[ctr] = element_array[i].active_color[j];
								ctr++;
							}
						}
						else if (element_array[i].highlighted) {
							for (j = 0; element_array[i].highlighted_color[j] != '\0'; j++) {
								display_string[ctr] = element_array[i].highlighted_color[j];
								ctr++;
							}
						}
						else {
							for (j = 0; element_array[i].default_color[j] != '\0'; j++) {
								display_string[ctr] = element_array[i].default_color[j];
								ctr++;
							}
						}
						
					}
					if (offset < strlen(element_array[i].label)) {
						display_string[ctr] = element_array[i].label[offset];
						
					}
					else if (strlen(element_array[i].label) == 0) {
						display_string[ctr] = ' ';
					}
					if (offset == element_array[i].width) {
						for (j = 0; background_color[j] != '\0'; j++) {
							display_string[ctr] = background_color[j];
							ctr++;
						}
						display_string[ctr] = ' ';
					}
					break;
				}
			}



			ctr++;
		}
		display_string[ctr] = '\n';
		ctr++;
	}
	display_string[ctr] = '\0';

	printf("%s", display_string);
}