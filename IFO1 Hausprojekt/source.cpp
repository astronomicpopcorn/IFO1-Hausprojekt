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

    //variables for table control
    int table_page = 0, table_entry = 0;
    char temp_table_string[72];
    
    char c; //stores recent inputs

    //search query
    char query[query_length] = "";




    //set some random students

    strcpy(students[0].first_name, "Nick");
    strcpy(students[0].last_name, "Winter");
    strcpy(students[0].course_of_study, "Mechatronik");
    strcpy(students[0].phone_number, "4915151727981");
    strcpy(students[0].enrollment_year, "2023");
    strcpy(students[0].student_number, "202050");
    strcpy(students[0].home_address.city, "Buxtehude");
    strcpy(students[0].home_address.street, "Estebrügger Straße");
    strcpy(students[0].home_address.house_number, "31A");
    strcpy(students[0].home_address.postal_code, "21614");
    strcpy(students[0].company.contact_person.first_name, "Rafael");
    strcpy(students[0].company.contact_person.last_name, "Götzen");
    strcpy(students[0].company.name, "Airbus");
    
    generate_company_email(students[0].company.contact_person.email, students[0].company.contact_person.first_name, students[0].company.contact_person.last_name, students[0].company.name);
    generate_hs21_email(students[0].email, students[0].first_name, students[0].last_name);
    
    strcpy(students[0].company.contact_person.phone_number, "1234567890");
    strcpy(students[0].company.address.city, "Hamburg");
    strcpy(students[0].company.address.street, "Kreetslag");
    strcpy(students[0].company.address.house_number, "10");
    strcpy(students[0].company.address.postal_code, "21129");
    
    
    
    strcpy(students[1].first_name, "Ole");
    strcpy(students[1].last_name, "Spindelndreher");
    strcpy(students[1].course_of_study, "Mechatronik");
    strcpy(students[1].phone_number, "4915151727981");
    strcpy(students[1].enrollment_year, "2023");
    strcpy(students[1].student_number, "02050");
    strcpy(students[1].home_address.city, "Estebrügge");
    strcpy(students[1].home_address.street, "Bahnhofsstraße");
    strcpy(students[1].home_address.house_number, "76");
    strcpy(students[1].home_address.postal_code, "21614");
    strcpy(students[1].company.contact_person.first_name, "Martin");
    strcpy(students[1].company.contact_person.last_name, "Möhre");
    strcpy(students[1].company.name, "Airbus");
    
    generate_company_email(students[1].company.contact_person.email, students[1].company.contact_person.first_name, students[1].company.contact_person.last_name, students[1].company.name);
    generate_hs21_email(students[1].email, students[1].first_name, students[1].last_name);
    
    strcpy(students[1].company.contact_person.phone_number, "739246248");
    strcpy(students[1].company.address.city, "Hamburg");
    strcpy(students[1].company.address.street, "Kreetslag");
    strcpy(students[1].company.address.house_number, "10");
    strcpy(students[1].company.address.postal_code, "21129");
    
    
    
    strcpy(students[2].first_name, "Jill Kendra");
    strcpy(students[2].last_name, "Hermann");
    strcpy(students[2].course_of_study, "Logistik");
    strcpy(students[2].phone_number, "4915151727981");
    strcpy(students[2].enrollment_year, "2023");
    strcpy(students[2].student_number, "202050");
    strcpy(students[2].home_address.city, "Hamburg");
    strcpy(students[2].home_address.street, "Linker Weg");
    strcpy(students[2].home_address.house_number, "12");
    strcpy(students[2].home_address.postal_code, "21614");
    strcpy(students[2].company.contact_person.first_name, "Hans");
    strcpy(students[2].company.contact_person.last_name, "Heinrich");
    strcpy(students[2].company.name, "Lufthansa");
    
    generate_company_email(students[2].company.contact_person.email, students[2].company.contact_person.first_name, students[2].company.contact_person.last_name, students[2].company.name);
    generate_hs21_email(students[2].email, students[2].first_name, students[2].last_name);
    
    strcpy(students[2].company.contact_person.phone_number, "8597243543");
    strcpy(students[2].company.address.city, "Hamburg");
    strcpy(students[2].company.address.street, "Flughafenstraße");
    strcpy(students[2].company.address.house_number, "335");
    strcpy(students[2].company.address.postal_code, "74239");
    
    
    
    strcpy(students[3].first_name, "Max");
    strcpy(students[3].last_name, "Mustermann");
    strcpy(students[4].first_name, "Timon");
    strcpy(students[4].last_name, "Trompete");
    strcpy(students[5].first_name, "Alexander");
    strcpy(students[5].last_name, "Müller");
    strcpy(students[6].first_name, "Jean Jaques");
    strcpy(students[6].last_name, "Mustermann");
    strcpy(students[7].first_name, "Florian");
    strcpy(students[7].last_name, "Flöte");
    strcpy(students[8].first_name, "Martin");
    strcpy(students[8].last_name, "von Margarine");
    strcpy(students[9].first_name, "Max");
    strcpy(students[9].last_name, "Krombacher");
    
    for (i = 0; i < 10; i++) {
        students[i].is_empty = false;
    }



    //ACTUAL CODE HERE


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

    //main loop
    while(true){
        /*verify console size
        console_size = get_console_size();
        if (console_size.x < 150 || console_size.y < 40) {
            printf("%s%s%sPlease resize your console window to at least 150x40 characters.\nThe console size is currently %ix%i", ansiResetCursor, ansiRed, ansiBlackBackground, console_size.x, console_size.y);
            continue;
        }
        */

        //check recent inputs
        if (kbhit()) {
            //reset values
            //get first char from input buffer
            c = getch();

            //if any element of type 2 is active
            if (active_element > 0 && windowelements[active_element].type == 2) {
                if (c == -32) {
                    getch(); //remove special characters
                }
                else {
                    if (active_element == 34) {
                        update_string(query, query_length, c);
                    }
                    else {
                        update_student_data(students, current_selected_entry, active_element, c);
                    }
                }
            }
            else {

                //if it's a special character
                if (c == -32) {
                    //get the next one
                    c = getch();
                    switch (c) {
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
            //Enter Pressed
            if (c == 13) {
                for (i = 0; i < windowelement_array_length; i++) {
                    if (windowelements[i].highlighted) {
                        if (windowelements[i].active) {
                            windowelements[i].active = false;
                            active_element = -1; //deactivate
                        } else {
                            windowelements[i].active = true;
                            active_element = i; //activate
                        }
                        break;
                    }
                }
            }
        }

        //filter entire database with query
        search_dataset(students, query, matching_indices);
        current_selected_entry = matching_indices[table_entry + 30 * table_page];

        //Generate table
        generate_table_ends(temp_table_string, false);
        windowelements[0] = make_window_element(1, 5, 71, temp_table_string, 0, 0, main_color, "", "", false, false);
        for (i = 0; i < 30; i++) {
            n = matching_indices[i + 30 * table_page];
            if (n != -1) {
                sprintf(temp_table_string, "|%3i|%-32s|%-32s|", n, students[n].first_name, students[n].last_name);
            }
            else {
                sprintf(temp_table_string, "| - |%-32s|%-32s|", "", "");
            }
            
            windowelements[i + 1] = make_window_element(1, 6 + i, 71, temp_table_string, 0, 0, main_color, "", table_highlighted_color, false, i == table_entry);
        }
        generate_table_ends(temp_table_string, true);
        windowelements[31] = make_window_element(1, 36, 71, temp_table_string, 0, 0, main_color, "", "", false, false);
        sprintf(temp_table_string, "Bild%c or Bild%c to go up/down. Pos1 or Ende to select page.   Page %i/5", 193, 194, table_page + 1);
        windowelements[32] = make_window_element(2, 4, 69, temp_table_string, 0, 0, main_color, "", "", false, false);

        strcpy(windowelements[34].label, query);
        
        update_windowelements_labels(windowelements, students, current_selected_entry, interactable_color, disabled_color);
        
        render(windowelements, windowelement_array_length, main_color);
    }
    
    
    





    //END OF ACTUAL CODE

    //test non-waiting typing - WORKS!
    //char c = 0;
    //char buff[100] = "\0";
    //int ptr = 0;
    //int ctr = 0;
    //while(c != '\n' && c != '\r'){
    //    while(kbhit()){
    //        c = getch();
    //        if(c == 8 && ptr > 0){
    //            ptr--;
    //            buff[ptr] = '\0';
    //        }
    //        else if(c != 8){
    //            buff[ptr] = c;
    //            ptr++;
    //            buff[ptr] = '\0';
    //        }
    //    }
    //    printf("\033[2J\033[H%s\n%i", buff, ctr);
    //    ctr++;
    //    Sleep(500);
    //}

    //DYNAMIC SEARCHING. 

    char t = '\0';
    char buffer[100] = "\0";
    int buffer_length = 0;
    int num_results;
    printf("> %s|\n", buffer);
    do {
        t = getch();
        if (t == 8 && buffer_length > 0) {
            buffer[buffer_length - 1] = '\0';
            buffer_length--;
        }
        else if (t != 8 && t != '\r' && t != '\n') {
            buffer[buffer_length] = t;
            buffer[buffer_length + 1] = '\0';
            buffer_length++;
        }
        printf("%s", "\033[2J\033[H");
        printf("> %s|\n", buffer);
        num_results = search_dataset(students, buffer, matching_indices);
        for(int i = 0; i < num_results; i++){
            printf("%3i: %s %s\n", i, students[matching_indices[i]].first_name, students[matching_indices[i]].last_name);
        }
    } while (t != '\r');
    printf("%s", "\033[2J\033[H");
    for (int i = 0; i < num_results; i++) {
        printf("%s", "\n--------------------------------------------------------\n\n");
        print_student(students[matching_indices[i]]);
    }
    getchar();


}
