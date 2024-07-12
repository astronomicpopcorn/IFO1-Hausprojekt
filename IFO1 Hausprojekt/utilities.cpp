#include "datastructures.h"
#include "constants.h"

#include <ctype.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

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
    FILE out = fopen(filename, "wb");
    if(out == NULL){
        return false;
    }
    fwrite(list, sizeof(student) * dataset_size, 1, out);
    fclose(out);
    return true;
}

bool load_file(student list[dataset_size], const char* filename){
    FILE in = fopen(filename, "rb");
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
