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


    getchar();
}
