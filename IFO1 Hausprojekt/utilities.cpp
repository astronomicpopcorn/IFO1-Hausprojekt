#include "datastructures.h"
#include "constants.h"
#include "windowinteractions.h"

#include <ctype.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

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


void lowercase_string(char *ptr){
    while (*ptr) {
        *ptr = tolower((unsigned char) *ptr);
        ptr++;
    }
}

bool is_mouse_pressed(){
    return GetAsyncKeyState(VK_LBUTTON) != 0;
}


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

void add_file_extension(char filename[filename_length]){
    if(filename[0] == '\0'){
        strcpy(filename, "unnamed");
    }
    int len = strlen(filename);
    if(len < filename_length - 3){
        strcat(filename, ".db");
    }
    else{
        filename[filename_length - 4] = '.';
        filename[filename_length - 3] = 'd';
        filename[filename_length - 2] = 'b';
        filename[filename_length - 1] = '\0';
    }
}


void replace_whitespace(char* string_to_change, char replacement){
    for(int i = 0; string_to_change[i] != '\0'; i++){
        if(string_to_change[i] == ' '){
            string_to_change[i] = replacement;
        }
    }
}

void replace_umlaute(char mystring[32], char buffer[64]){
    int buffer_pointer = 0;
    int string_pointer = 0;
    while(mystring[string_pointer] != '\0'){
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
        else{
            buffer[buffer_pointer] = mystring[string_pointer];
        }
        buffer_pointer++;
    }
}


//builds an element. type is 0 for plain text, 1 for button, and 2 for text input.
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