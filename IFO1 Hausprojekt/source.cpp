#include <stdio.h>
#include <string.h>

#include "datastructures.h"
#include "constants.h"
#include "utilities.h"


void main() {
    student students[dataset_size];
    
    strcpy(students[0].first_name, "Nick");
    strcpy(students[0].surname, "Winter");
    strcpy(students[0].course_of_study, "Mechatronik");
    students[0].phone_number = 4915151727981;
    students[0].enrollment_year = 2023;
    students[0].student_number = 202050;
    strcpy(students[0].home_address.city, "Buxtehude");
    strcpy(students[0].home_address.street, "Estebrügger Straße");
    students[0].home_address.house_number = 31;
    students[0].home_address.postal_code = 21614;
    strcpy(students[0].company.contact_person.first_name, "Rafael");
    strcpy(students[0].company.contact_person.surname, "Götzen");
    strcpy(students[0].company.name, "Airbus");

    generate_company_email(students[0].company.contact_person.email, students[0].company.contact_person.first_name, students[0].company.contact_person.surname, students[0].company.name);
    generate_hs21_email(students[0].email, students[0].first_name, students[0].surname);

    students[0].company.contact_person.phone_number = 1234567890;
    strcpy(students[0].company.address.city, "Hamburg");
    strcpy(students[0].company.address.street, "Kreetslag");
    students[0].company.address.house_number = 10;
    students[0].company.address.postal_code = 21129;

    printf("%s", students[0].company.contact_person.email);

    strcpy(students[1].first_name, "Ole");
    strcpy(students[1].surname, "Spindelndreher");
    strcpy(students[2].first_name, "Jill Kendra");
    strcpy(students[2].surname, "Hermann");
    strcpy(students[3].first_name, "Max");
    strcpy(students[3].surname, "Mustermann");
    strcpy(students[4].first_name, "Timon");
    strcpy(students[4].surname, "Trompete");
    strcpy(students[5].first_name, "Alexander");
    strcpy(students[5].surname, "Müller");
    strcpy(students[6].first_name, "Jean Jaques");
    strcpy(students[6].surname, "Jodelmeister");
    strcpy(students[7].first_name, "Florian");
    strcpy(students[7].surname, "Flöte");
    strcpy(students[8].first_name, "Martin");
    strcpy(students[8].surname, "von Margarine");
    strcpy(students[9].first_name, "Gerald");
    strcpy(students[9].surname, "Gulasch");
    
    //test search:
    char temp_query[64];
    scanf("%[^\n]s", temp_query);
    getchar();
    for(int i = 0; i < dataset_size; i++){
        if(search_datapoint(students[i], temp_query)){
            printf("%3i: %s %s\n", i, students[i].first_name, students[i].surname);
        }
    }
    getchar();
    while(true){
        Vector2D pos = get_mouse-on_window();
        printf("\033[H%4i %4i", pos.x, pos.y);
    }


    getchar();
}
