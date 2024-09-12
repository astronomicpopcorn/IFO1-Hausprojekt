#include "datastructures.h"
#include "constants.h"
#include "windowinteractions.h"
#include "datamodification.h"

#include <ctype.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


//deprecated. use strcpy instead.
void copy_string(char* destination, char* source){
    unsigned short int dest_ctr = 0;
    unsigned short int src_ctr = 0;
    while(*(destination + dest_ctr) != '\0' && *(source + src_ctr) != '\0'){
        *(destination + dest_ctr) = *(source + src_ctr);
        dest_ctr++;
        src_ctr++;
    }
    *(destination + dest_ctr) = '\0';
}

//loops through all chars in a string and converts to lowercase.
void lowercase_string(char *ptr){
    while (*ptr) {
        *ptr = tolower((unsigned char) *ptr);
        ptr++;
    }
}

//returns true if any mouse buton is pressed. feature discontinued.
bool is_mouse_pressed(){
    return GetAsyncKeyState(VK_LBUTTON) != 0;
}

//testing function. prints one student to the screen. not used due to custom print system.
void print_student(student student){
    printf("%s %s\n", student.first_name, student.last_name);
    printf("(%s, Jahrgang %s)\n", student.course_of_study, student.enrollment_year);
    printf("%s\n", student.email);
    printf("%s\n", student.phone_number);
    printf("%s %s\n", student.home_address.street, student.home_address.house_number);
    printf("%s %s\n", student.home_address.postal_code, student.home_address.city);
    printf("\nPraxispartner: %s\n", student.company.name);
    printf("%s %s\n", student.company.address.street, student.company.address.house_number);
    printf("%s %s\n", student.company.address.postal_code, student.company.address.city);
    printf("Kontaktperson:\n");
    printf("%s %s\n", student.company.contact_person.first_name, student.company.contact_person.last_name);
    printf("%s\n", student.company.contact_person.email);
    printf("%s\n", student.company.contact_person.phone_number);
}


//basic fileio
//saves the dataset as a file with a given name. returns true if successful.
bool save_file(student list[dataset_size], const char* filename){
    FILE *out;
    out = fopen(filename, "wb");
    if(out == NULL){
        return false;
    }
    fwrite(list, sizeof(student) * dataset_size, 1, out);
    fclose(out);
    return true;
}

//loads a dataset from a given filename. returns true if successful.
bool load_file(student list[dataset_size], const char* filename){
    FILE *in;
    in = fopen(filename, "rb");
    if(in == NULL){
        return false;
    }
    fread(list, sizeof(student) * dataset_size, 1, in);
    fclose(in);
    return true;
}

//deletes specified file. returns true if successful.
bool delete_file(const char *filename) {
    FILE *in;
    in = fopen(filename, "rb");
    if (in == NULL) {
        return false;
    }
    fclose(in);
    remove(filename);
    return true;
}

//adds .db to the end of a string.
void add_file_extension(char source[filename_length], char target[filename_length]) {
    int len = strlen(source);
    //copy source into target
    strcpy(target, source);
    //if string is empty, name the file "unnamed"
    if(len == 0){
        strcpy(target, "unnamed");
    }
    //if space is available, add extension.
    if(len < filename_length - 3){
        strcat(target, ".db");
    }
    //if space is occupied, overwrite the last 3 chars.
    else{
        target[filename_length - 4] = '.';
        target[filename_length - 3] = 'd';
        target[filename_length - 2] = 'b';
        target[filename_length - 1] = '\0';
    }
}

//replaces all spaces in a string with a given char.
void replace_whitespace(char* string_to_change, char replacement){
    for(int i = 0; string_to_change[i] != '\0'; i++){
        if(string_to_change[i] == ' '){
            string_to_change[i] = replacement;
        }
    }
}

//replaces all special chars. for example: ä -> ae
//writes the edited version into the provided buffer
void replace_umlaute(char mystring[32], char buffer[64]){
    //set pseudo pointers for striung indices
    int buffer_pointer = 0;
    int string_pointer = 0;
    //loop through string until the end
    while(mystring[string_pointer] != '\0'){
        //if a special character is found, write the replacement to the buffer
        if(mystring[string_pointer] == 'ä'){
            buffer[buffer_pointer] = 'a';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'Ä'){
            buffer[buffer_pointer] = 'A';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'ü'){
            buffer[buffer_pointer] = 'u';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'Ü'){
            buffer[buffer_pointer] = 'U';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'ö'){
            buffer[buffer_pointer] = 'o';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'Ö'){
            buffer[buffer_pointer] = 'O';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'ß'){
            buffer[buffer_pointer] = 's';
            buffer_pointer++;
            buffer[buffer_pointer] = 's';
        }
        //no special char -> justr copy to the buffer
        else{
            buffer[buffer_pointer] = mystring[string_pointer];
        }
        buffer_pointer++;
    }
}


//windowelement constructor. returns a windowelement struct with the specified values. 
//type is 0 for plain text, 1 for button, and 2 for text input.
//id is an optional identifier.
windowelement make_window_element(int column, int row, int width, const char *label, int id, int type, const char *def_col, const char *highlight_col, const char *active_col, bool is_highlighted, bool is_active) {
    windowelement element;
    Vector2D pos = { column, row };
    element.position = pos;
    element.width = width;
    strcpy(element.label, label);
    strcpy(element.default_color, def_col);
    strcpy(element.highlighted_color, highlight_col);
    strcpy(element.active_color, active_col);
    element.id = id;
    element.type = type;
    element.highlighted = is_highlighted;
    element.active = is_active;

    return element;
}


//expects w, a, s or d as char input. case insensitive
void update_highlighted_element(windowelement *element_array, int array_length, char c) {
    int i, original_index = -1, next_index = -1, temp_value = 1000;
    //loop through all elements and save first that is highlighted
    for (i = 0; i < array_length; i++) {
        if (element_array[i].highlighted) {
            original_index = i;
            break;
        }
    }
    //no highlighted found -> exit without changing anything
    if (original_index == -1) {
        return;
    }
    //any key for up pressed?
    if (c == 'w' || c == 'W') {
        //loop through all elements
        for (i = 0; i < array_length; i++) {
            //if x matches and y is less than original
            if (element_array[i].type != 0 &&
                element_array[i].position.x == element_array[original_index].position.x &&
                element_array[i].position.y < element_array[original_index].position.y &&
                element_array[original_index].position.y - element_array[i].position.y < temp_value) {
                //update candidate index and value for comparison
                next_index = i;
                temp_value = element_array[original_index].position.y - element_array[i].position.y;
            }
        }
        //if a candidate has been found
        if (next_index != -1) {
            //switch highlight from old to new element
            element_array[next_index].highlighted = true;
            element_array[original_index].highlighted = false;
        }
    }
    //any key for down pressed?
    else if (c == 's' || c == 'S') {
        //loop through all elements
        for (i = 0; i < array_length; i++) {
            //if x matches and y is greater than original
            if (element_array[i].type != 0 &&
                element_array[i].position.x == element_array[original_index].position.x &&
                element_array[i].position.y > element_array[original_index].position.y &&
                element_array[i].position.y - element_array[original_index].position.y < temp_value) {
                //update candidate index and value for comparison
                next_index = i;
                temp_value = element_array[i].position.y - element_array[original_index].position.y;
            }
        }
        //if a candidate has been found
        if (next_index != -1) {
            //switch highlight from old to new element
            element_array[next_index].highlighted = true;
            element_array[original_index].highlighted = false;
        }
    }
    //any key for left pressed?
    else if (c == 'a' || c == 'A') {
        //loop through all elements
        for (i = 0; i < array_length; i++) {
            //if y matches and x is less than original
            if (element_array[i].type != 0 &&
                element_array[i].position.y == element_array[original_index].position.y &&
                element_array[i].position.x < element_array[original_index].position.x &&
                element_array[original_index].position.x - element_array[i].position.x < temp_value) {
                //update candidate index and value for comparison
                next_index = i;
                temp_value = element_array[original_index].position.x - element_array[i].position.x;
            }
        }
        //if a candidate has been found
        if (next_index != -1) {
            //switch highlight from old to new element
            element_array[next_index].highlighted = true;
            element_array[original_index].highlighted = false;
        }
    }
    //any key for right pressed?
    else if (c == 'd' || c == 'D') {
        //loop through all elements
        for (i = 0; i < array_length; i++) {
            //if y matches and x is greater than original
            if (element_array[i].type != 0 &&
                element_array[i].position.y == element_array[original_index].position.y &&
                element_array[i].position.x > element_array[original_index].position.x &&
                element_array[i].position.x - element_array[original_index].position.x < temp_value) {
                //update candidate index and value for comparison
                next_index = i;
                temp_value = element_array[i].position.x - element_array[original_index].position.x;
            }
        }
        //if a candidate has been found
        if (next_index != -1) {
            //switch highlight from old to new element
            element_array[next_index].highlighted = true;
            element_array[original_index].highlighted = false;
        }
    }
}

//generates a string made from special line characters. for example: ┌ ─ ┬
//not a string literal because VS encodes chars differently and they don't translate properly
//string is flipped vertically based on provided bool.
void generate_table_ends(char* table_string, bool is_bottom) {
    int i;
    if (!is_bottom) {
        table_string[0] = 218;
        for (i = 1; i <= 3; i++) {
            table_string[i] = 196;
        }
        table_string[4] = 194;
        for (i = 5; i <= 36; i++) {
            table_string[i] = 196;
        }
        table_string[37] = 194;
        for (i = 38; i <= 69; i++) {
            table_string[i] = 196;
        }
        table_string[70] = 191;
        table_string[71] = '\0';
    }
    else {
        table_string[0] = 192;
        for (i = 1; i <= 3; i++) {
            table_string[i] = 196;
        }
        table_string[4] = 193;
        for (i = 5; i <= 36; i++) {
            table_string[i] = 196;
        }
        table_string[37] = 193;
        for (i = 38; i <= 69; i++) {
            table_string[i] = 196;
        }
        table_string[70] = 217;
        table_string[71] = '\0';
    }
}

//adds a char to the end of a string. unless it is backspace, then it makes the string shorter.
//returns true if string is empty
bool update_string(char *target_string, int target_string_max_length, char c) {
    bool is_empty;
    int current_length = strlen(target_string);
    //initialize is_empty
    if (current_length > 0) {
        is_empty = false;
    }
    else {
        is_empty = true;
    }
    //if char is backspace
    if (c == 8) {
        //if string has at least one char, replace last char with \0
        if (current_length > 0) {
            target_string[current_length - 1] = '\0';
            //if new length is 0, string is empty
            if (current_length - 1 == 0) {
                is_empty = true;
            }
        }
    }
    //if char is printable character (excludes ä, ö, ü and ß to avoid unwanted behavior elsewhere)
    else if ((c >= 32 && c <= 90) || (c >= 97 && c <= 122)) {
        //if space is available
        if (current_length < target_string_max_length - 1) {
            //add char to the end and terminate string again
            target_string[current_length] = c;
            target_string[current_length + 1] = '\0';
            //string is now guaranteed to have at least one char
            is_empty = false;
        }
    }
    return is_empty;
}

//checks whether all strings in a given student are empty
bool is_student_empty(student checked_student) {
    return
        checked_student.company.address.city[0] == '\0' &&
        checked_student.company.address.house_number[0] == '\0' &&
        checked_student.company.address.postal_code[0] == '\0' &&
        checked_student.company.address.street[0] == '\0' &&
        //checked_student.company.contact_person.email[0] == '\0' &&          email doesn't matter
        checked_student.company.contact_person.first_name[0] == '\0' &&
        checked_student.company.contact_person.last_name[0] == '\0' &&
        checked_student.company.contact_person.phone_number[0] == '\0' &&
        checked_student.company.name[0] == '\0' &&
        checked_student.course_of_study[0] == '\0' &&
        //checked_student.email[0] == '\0' &&                                 email doesn't matter
        checked_student.enrollment_year[0] == '\0' &&
        checked_student.first_name[0] == '\0' &&
        checked_student.home_address.city[0] == '\0' &&
        checked_student.home_address.house_number[0] == '\0' &&
        checked_student.home_address.postal_code[0] == '\0' &&
        checked_student.home_address.street[0] == '\0' &&
        checked_student.last_name[0] == '\0' &&
        checked_student.phone_number[0] == '\0' &&
        checked_student.student_number[0] == '\0';
}

//updates the selected student's entries based on table selector and selected input box
void update_student_data(student *student_array, int student_index, int element_index, char c) {
    //switch which string to update based on selected input
    switch (element_index) {
        case 36:
            update_string(student_array[student_index].first_name, first_name_length, c);
            break;
        case 38:
            update_string(student_array[student_index].student_number, student_number_length, c);
            break;
        case 40:
            update_string(student_array[student_index].phone_number, phone_number_length, c);
            break;
        case 42:
            update_string(student_array[student_index].home_address.street, street_name_length, c);
            break;
        case 44:
            update_string(student_array[student_index].home_address.postal_code, postal_code_length, c);
            break;

        case 48:
            update_string(student_array[student_index].company.name, company_name_length, c);
            break;
        case 50:
            update_string(student_array[student_index].company.address.street, street_name_length, c);
            break;
        case 52:
            update_string(student_array[student_index].company.address.postal_code, postal_code_length, c);
            break;
        case 54:
            update_string(student_array[student_index].company.contact_person.first_name, first_name_length, c);
            break;

        case 58:
            update_string(student_array[student_index].company.contact_person.phone_number, phone_number_length, c);
            break;
        case 60:
            update_string(student_array[student_index].last_name, last_name_length, c);
            break;
        case 62:
            update_string(student_array[student_index].course_of_study, course_of_study_length, c);
            break;
        case 64:
            update_string(student_array[student_index].enrollment_year, enrollment_year_length, c);
            break;
        case 66:
            update_string(student_array[student_index].home_address.house_number, house_number_length, c);
            break;
        case 68:
            update_string(student_array[student_index].home_address.city, city_name_length, c);
            break;
        case 70:
            update_string(student_array[student_index].company.address.house_number, house_number_length, c);
            break;
        case 72:
            update_string(student_array[student_index].company.address.city, city_name_length, c);
            break;
        case 74:
            update_string(student_array[student_index].company.contact_person.last_name, last_name_length, c);
            break;
    }
    //regenerate emails and set empty flag correctly
    generate_hs21_email(student_array[student_index].email, student_array[student_index].first_name, student_array[student_index].last_name);
    generate_company_email(student_array[student_index].company.contact_person.email, student_array[student_index].company.contact_person.first_name, student_array[student_index].company.contact_person.last_name, student_array[student_index].company.name);
    student_array[student_index].is_empty = is_student_empty(student_array[student_index]);
}

//disables input boxes when table selector is on invalid entry
//updates labels of all windowelement input boxes to match selected student
void update_windowelements_labels(windowelement *element_array, student *student_array, int student_index, char *on_color, char *off_color) {
    int i;
    //invalid student selected (table selector on entry without associated index)
    if (student_index == -1) {
        //loop through all relevant input boxes
        for (i = 36; i <= 74; i += 2) {
            //clear label
            strcpy(element_array[i].label, "");
            //exclude email boxes
            if (i != 46 && i != 56) {
                //set color to red and type to non-interactable
                strcpy(element_array[i].default_color, off_color);
                element_array[i].type = 0;
            }
        }
        //quit. elements no longer need updating
        return;
    }
    //check if elements are disabled (all elements will be disabled together)
    if (element_array[36].type == 0) {
        for (i = 36; i <= 74; i += 2) {
            //exclude email elements
            if (i != 46 && i != 56) {
                //set color to normal and type to text input
                strcpy(element_array[i].default_color, on_color);
                element_array[i].type = 2;
            }
        }
    }


    student selected_student = student_array[student_index];
    
    //set all labels
    strcpy(element_array[36].label, selected_student.first_name);
    strcpy(element_array[38].label, selected_student.student_number);
    strcpy(element_array[40].label, selected_student.phone_number);
    strcpy(element_array[42].label, selected_student.home_address.street);
    strcpy(element_array[44].label, selected_student.home_address.postal_code);
    strcpy(element_array[46].label, selected_student.email);
    strcpy(element_array[48].label, selected_student.company.name);
    strcpy(element_array[50].label, selected_student.company.address.street);
    strcpy(element_array[52].label, selected_student.company.address.postal_code);
    strcpy(element_array[54].label, selected_student.company.contact_person.first_name);
    strcpy(element_array[56].label, selected_student.company.contact_person.email);
    strcpy(element_array[58].label, selected_student.company.contact_person.phone_number);

    strcpy(element_array[60].label, selected_student.last_name);
    strcpy(element_array[62].label, selected_student.course_of_study);
    strcpy(element_array[64].label, selected_student.enrollment_year);
    strcpy(element_array[66].label, selected_student.home_address.house_number);
    strcpy(element_array[68].label, selected_student.home_address.city);
    strcpy(element_array[70].label, selected_student.company.address.house_number);
    strcpy(element_array[72].label, selected_student.company.address.city);
    strcpy(element_array[74].label, selected_student.company.contact_person.last_name);
}

//creates part of the initial windowelements array.
//specifically all elements for editing and viewing a student
void initialize_windowelements(windowelement *element_array, char *main_color, char *interactable_color, char *highlight_color, char *active_color) {
    //info display column 1
    element_array[35] = make_window_element(75, 2, 16, "    First Name:", 0, 0, main_color, "", "", false, false);
    element_array[36] = make_window_element(92, 2, first_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[37] = make_window_element(75, 4, 16, "Student number:", 0, 0, main_color, "", "", false, false);
    element_array[38] = make_window_element(92, 4, student_number_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[39] = make_window_element(75, 6, 16, "     Telephone:", 0, 0, main_color, "", "", false, false);
    element_array[40] = make_window_element(92, 6, phone_number_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[41] = make_window_element(75, 8, 16, "        Street:", 0, 0, main_color, "", "", false, false);
    element_array[42] = make_window_element(92, 8, street_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[43] = make_window_element(75, 10, 16, "   Postal code:", 0, 0, main_color, "", "", false, false);
    element_array[44] = make_window_element(92, 10, postal_code_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[45] = make_window_element(75, 12, 16, "        E-Mail:", 0, 0, main_color, "", "", false, false);
    element_array[46] = make_window_element(92, 12, email_length, "", 0, 0, main_color, "", "", false, false);

    element_array[47] = make_window_element(75, 16, 16, "       Company:", 0, 0, main_color, "", "", false, false);
    element_array[48] = make_window_element(92, 16, company_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[49] = make_window_element(75, 18, 16, "        Street:", 0, 0, main_color, "", "", false, false);
    element_array[50] = make_window_element(92, 18, street_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[51] = make_window_element(75, 20, 16, "   Postal Code:", 0, 0, main_color, "", "", false, false);
    element_array[52] = make_window_element(92, 20, postal_code_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[53] = make_window_element(75, 24, 16, "    First Name:", 0, 0, main_color, "", "", false, false);
    element_array[54] = make_window_element(92, 24, first_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[55] = make_window_element(75, 26, 16, "        E-Mail:", 0, 0, main_color, "", "", false, false);
    element_array[56] = make_window_element(92, 26, email_length, "", 0, 0, main_color, "", "", false, false);

    element_array[57] = make_window_element(75, 28, 16, "    Telephone:", 0, 0, main_color, "", "", false, false);
    element_array[58] = make_window_element(92, 28, phone_number_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);


    //info display column 2

    element_array[59] = make_window_element(126, 2, 16, "     Last Name:", 0, 0, main_color, "", "", false, false);
    element_array[60] = make_window_element(143, 2, last_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[61] = make_window_element(126, 4, 16, "        Course:", 0, 0, main_color, "", "", false, false);
    element_array[62] = make_window_element(143, 4, course_of_study_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[63] = make_window_element(126, 6, 16, "          Year:", 0, 0, main_color, "", "", false, false);
    element_array[64] = make_window_element(143, 6, enrollment_year_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[65] = make_window_element(126, 8, 16, "  House Number:", 0, 0, main_color, "", "", false, false);
    element_array[66] = make_window_element(143, 8, house_number_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[67] = make_window_element(126, 10, 16, "          City:", 0, 0, main_color, "", "", false, false);
    element_array[68] = make_window_element(143, 10, city_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[69] = make_window_element(126, 18, 16, "  House Number:", 0, 0, main_color, "", "", false, false);
    element_array[70] = make_window_element(143, 18, house_number_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[71] = make_window_element(126, 20, 16, "          City:", 0, 0, main_color, "", "", false, false);
    element_array[72] = make_window_element(143, 20, city_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    element_array[73] = make_window_element(126, 24, 16, "     Last Name:", 0, 0, main_color, "", "", false, false);
    element_array[74] = make_window_element(143, 24, last_name_length, "", 0, 2, interactable_color, highlight_color, active_color, false, false);

    //info display dividers

    element_array[75] = make_window_element(76, 14, 100, "--------------------------------------- Company Information ---------------------------------------", 0, 0, main_color, "", "", false, false);
    element_array[76] = make_window_element(76, 22, 100, "-------------------------------- Company Contact Person Information -------------------------------", 0, 0, main_color, "", "", false, false);

}