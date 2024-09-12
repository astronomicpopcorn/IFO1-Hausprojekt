#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#include "datastructures.h"
#include "constants.h"
#include "utilities.h"
#include "datamodification.h"
#include "windowinteractions.h"
#include "searching.h"
#include "rendering.h"
#include "colorcodes.h"

void main() {
    //colors of the console
    char main_color[] = "\033[44m\033[97m";
    char interactable_color[] = "\033[47m\033[30m";
    char highlight_color[] = "\033[103m\033[30m";
    char active_color[] = "\033[102m\033[30m";
    char table_highlighted_color[] = "\033[107m\033[34m";
    char disabled_color[] = "\033[101m\033[30m";

    short int matching_indices[dataset_size]; //used for search function to store indeces of matching entries
    student students[dataset_size]; //main array

    Vector2D console_size;

    //random temporary variables for loops and the like
    int i, j, k, l, m, n;

    //frame counter for autosave
    int frame = 0;

    //variables for table control
    int table_page = 0, table_entry = 0;
    char temp_table_string[72];
    
    char c; //stores recent inputs

    //search query
    char query[query_length] = "";

    //file name for hard disk storage
    char filename[filename_length] = "dataset1";
    char filename_with_extension[filename_length] = "dataset1.db";

    //array that stores all window elements
    windowelement windowelements[windowelement_array_length];

    //index of current active element
    int active_element = -1;

    //stores index into student array based on selected table entry
    int current_selected_entry = -1;

    //search bar
    windowelements[33] = make_window_element(4, 1, 7, "Filter:", 0, 0, main_color, "", "", false, false);
    windowelements[34] = make_window_element(4, 2, 64, query, 1, 2, interactable_color, highlight_color, active_color, true, false);

    initialize_windowelements(windowelements, main_color, interactable_color, highlight_color, active_color);

    windowelements[77] = make_window_element(4, 38, 64, "File Name:", 0, 0, main_color, "", "", false, false);
    windowelements[78] = make_window_element(4, 39, 64, filename, 2, 2, interactable_color, highlight_color, active_color, false, false);
    windowelements[79] = make_window_element(74, 39, 12, "Save", 10, 1, interactable_color, highlight_color, active_color, false, false);
    windowelements[80] = make_window_element(92, 39, 12, "Load", 11, 1, interactable_color, highlight_color, active_color, false, false);
    windowelements[81] = make_window_element(74, 41, 12, "Delete", 12, 1, interactable_color, highlight_color, active_color, false, false);

    windowelements[82] = make_window_element(92, 41, 12, "Quit", 13, 1, interactable_color, highlight_color, active_color, false, false);

    //attempt to load last autosave
    load_file(students, "autosave.db");

    //variable set to false when program should be quit
    bool continue_program = true;

    //main loop
    while(continue_program){

        //check for recent inputs
        while (kbhit()) {
            //get first char from input buffer
            c = getch();

            //Enter Pressed -> switch the active state of the highlighted element and save the index
            if (c == 13) {
                for (i = 0; i < windowelement_array_length; i++) {
                    if (windowelements[i].highlighted) {
                        if(windowelements[i].type == 2) {
                            if (windowelements[i].active) {
                                windowelements[i].active = false;
                                active_element = -1; //deactivate
                            } else {
                                windowelements[i].active = true;
                                active_element = i; //activate
                            }
                        }
                        else if (windowelements[i].type == 1) {
                            //handle button press based on id
                            switch (windowelements[i].id) {
                                case 10: //save file
                                    add_file_extension(filename, filename_with_extension);
                                    save_file(students, filename_with_extension);
                                    break;
                                case 11: //load file
                                    add_file_extension(filename, filename_with_extension);
                                    load_file(students, filename_with_extension);
                                    break;
                                case 12: //delete file
                                    add_file_extension(filename, filename_with_extension);
                                    delete_file(filename_with_extension);
                                    break;

                                case 13: //quit program
                                    save_file(students, "autosave.db");
                                    continue_program = false;
                                    break;
                            }
                        }
                        break;
                    }
                }
            }

            //if any element of type 2 is active
            if (active_element > 0 && windowelements[active_element].type == 2) {
                if (c == -32) {
                    getch(); //remove special characters
                }
                else {
                    //if the active element is the search box, update the search query with the char
                    if (active_element == 34) {
                        update_string(query, query_length, c);
                    }
                    //if the active element is the filename input, update the filename with the char
                    else if (active_element == 78) {
                        update_string(filename, filename_length, c);
                    }
                    //otherwise, a text input for the student data is active. update the data using the char.
                    else {
                        update_student_data(students, current_selected_entry, active_element, c);
                    }
                }
            }
            //no element is active -> update the highlighted element
            else {

                //if it's a special character
                if (c == -32) {
                    //get the next one
                    c = getch();
                    switch (c) {
                        //change c into a char readable by update_highlighted_element
                        case 72: //up arrow
                            c = 'w';
                            break;
                        case 80: //down arrow
                            c = 's';
                            break;
                        case 77: //right arrow
                            c = 'd';
                            break;
                        case 75: //left arrow
                            c = 'a';
                            break;
                        //update the table
                        case 73: //PgUp
                            if (table_entry > 0) {
                                table_entry--; //if possible, go up
                            } else if (table_page > 0) {
                                table_entry = 29; //if page available, switch page
                                table_page--;
                            }
                            break;
                        case 81: //PgDn
                            if (table_entry < 29) {
                                table_entry++; //if possible, go down
                            } else if (table_page < 4) {
                                table_entry = 0; //if page available, switch page
                                table_page++;
                            }
                            break;
                        case 71: //Pos1
                            if (table_page > 0) {
                                table_page--; //decrease one page
                            }
                            break;
                        case 79: //Ende
                            if (table_page < 4) {
                                table_page++; //increase page
                            }
                            break;
                    }
                }
                //if c is w, a, s or d, change highlighted element. only update if there is no active element
                if ((c == 'w' || c == 'W' || c == 'a' || c == 'A' || c == 's' || c == 'S' || c == 'd' || c == 'D') && active_element == -1) {
                    update_highlighted_element(windowelements, windowelement_array_length, c);
                }
            }
     
        }

        //filter entire database with query
        search_dataset(students, query, matching_indices);
        current_selected_entry = matching_indices[table_entry + 30 * table_page];

        //Generate table
        generate_table_ends(temp_table_string, false);
        windowelements[0] = make_window_element(1, 5, 71, temp_table_string, 0, 0, main_color, "", "", false, false);
        //generate 30 elements to hold the table entries.
        for (i = 0; i < 30; i++) {
            n = matching_indices[i + 30 * table_page];
            if (n != -1) {
                sprintf(temp_table_string, "|%3i|%-32s|%-32s|", n, students[n].first_name, students[n].last_name);
            }
            else {
                sprintf(temp_table_string, "| - |%-32s|%-32s|", "", "");
            }
            //                                                                                                              element is set to active if it is selected
            windowelements[i + 1] = make_window_element(1, 6 + i, 71, temp_table_string, 0, 0, main_color, "", table_highlighted_color, false, i == table_entry);
        }
        generate_table_ends(temp_table_string, true);
        windowelements[31] = make_window_element(1, 36, 71, temp_table_string, 0, 0, main_color, "", "", false, false);
        //table control explanation and page counter
        sprintf(temp_table_string, "Bild%c or Bild%c to go up/down. Pos1 or Ende to select page.   Page %i/5", 193, 194, table_page + 1);
        windowelements[32] = make_window_element(2, 4, 69, temp_table_string, 0, 0, main_color, "", "", false, false);

        //copy the query into the search box to be displayed
        strcpy(windowelements[34].label, query);

        //copy the filename into the filename input to be displayed
        strcpy(windowelements[78].label, filename);
        
        //update the labels of all window elements to reflect possibly changed data
        update_windowelements_labels(windowelements, students, current_selected_entry, interactable_color, disabled_color);
        
        //render all elements
        render(windowelements, windowelement_array_length, main_color);
        //count frame
        frame++;
        if (frame > 300) {
            frame = 0;
            save_file(students, "autosave.db");
        }
    }
}
