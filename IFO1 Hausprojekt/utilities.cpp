#include "datastructures.h"
#include "constants.h"

#include <ctype.h>
#include <windows.h>
#include <stdio.h>

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
