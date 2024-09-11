#include "utilities.h";
#include "windowinteractions.h"
#include "constants.h"
#include "datastructures.h"

#include <stdio.h>
#include <string.h>


//this is where the magic happens

//explanation:
//to eliminate flickering, the screen is not cleared.
//instead, a string is created that, when printed, fills the whole screen.
//this string is printed starting from the top left corner, overwriting the last one.



//test render. fills the screen with X
//unused in actual code
void render_test() {
	Vector2D console_size = get_console_size();

	//initialize string to ansi code that sets the cursor to 1,1 (top left)
	char display_string[max_display_string_length] = "\033[H";
	//initialize display string counter to account for ansi code
	int ctr = 3;

	//loop through all possible x and y values
	//skip last row to leave space for cursor
	for (int y = 0; y < console_size.y - 1; y++) {
		for (int x = 0; x < console_size.x; x++) {
			//if counter is even, add X. otherwise add space
			if (ctr % 2 == 0) {
				display_string[ctr] = 'X';
			}
			else {
				display_string[ctr] = ' ';
			}
			ctr++;
		}
		//at the end of a line, add line break
		display_string[ctr] = '\n';
		ctr++;
	}
	//terminate
	display_string[ctr] = '\0';

	//print the entire string
	printf("%s", display_string);
}


//testing function. draws a single window element.
//not used in program.
void render_single_element_test(windowelement element) {
	//retrieve the size of the console in chars
	Vector2D console_size = get_console_size();

	//initialize string to ansi code that sets the cursor to 1,1 (top left)
	char display_string[max_display_string_length] = "\033[H";
	//create counters and other ints. the display string counter initialization to three is because of the ansi code.
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






//this function takes in all windowelements and prints the result directly to the console.

void render(windowelement *element_array, int array_length, const char* background_color) {
	//retrieve the size of the console in chars
	Vector2D console_size = get_console_size();

	//create the massive display string
	//the length is due to the console being resizeable to very large dimensions
	char display_string[max_display_string_length] = "\033[H";
	//create counters and other ints. the display string counter initialization to three is because of the ansi code.
	int x, y, offset, i, j, ctr = 3;

	//loop through all x and y values
	//skip last row to leave space for cursor
	for (y = 0; y < console_size.y - 1; y++) {
		for (x = 0; x < console_size.x; x++) {
			//set the default char to space. my be overwritten later.
			display_string[ctr] = ' ';
			//loop through all display elements
			for (i = 0; i < array_length; i++) {
				//calculate the x-offset between the currently drawn char and the element's origin
				offset = x - element_array[i].position.x;
				//if currently drawn char is inside the element
				if (element_array[i].position.y == y && element_array[i].position.x <= x && offset <= element_array[i].width) {
					//if its the leftmost char of the element
					if (x == element_array[i].position.x) {
						//if the element is active, set the color to the element's active color
						if (element_array[i].active) {
							for (j = 0; element_array[i].active_color[j] != '\0'; j++) {
								display_string[ctr] = element_array[i].active_color[j];
								ctr++;
							}
						}
						//if the element is highlighted, set the color to the element's highlight color
						else if (element_array[i].highlighted) {
							for (j = 0; element_array[i].highlighted_color[j] != '\0'; j++) {
								display_string[ctr] = element_array[i].highlighted_color[j];
								ctr++;
							}
						}
						//otherwise, set the elements default color.
						else {
							for (j = 0; element_array[i].default_color[j] != '\0'; j++) {
								display_string[ctr] = element_array[i].default_color[j];
								ctr++;
							}
						}
						
					}
					//if text is available at the current char, add it into the display string
					if (offset < strlen(element_array[i].label)) {
						display_string[ctr] = element_array[i].label[offset];
						
					}
					//if the string is empty, draw a space
					else if (strlen(element_array[i].label) == 0) {
						display_string[ctr] = ' ';
					}
					//if it's the rightmost char of the element, set color to the default background.
					if (offset == element_array[i].width) {
						for (j = 0; background_color[j] != '\0'; j++) {
							display_string[ctr] = background_color[j];
							ctr++;
						}
						display_string[ctr] = ' ';
					}
					//something from an element has been drawn, no need to look through other elements
					break;
				}
			}
			ctr++;
		}
		//add linebreak when the edge of the screen is reached
		display_string[ctr] = '\n';
		ctr++;
	}

	//terminate and print
	display_string[ctr] = '\0';

	printf("%s", display_string);
}