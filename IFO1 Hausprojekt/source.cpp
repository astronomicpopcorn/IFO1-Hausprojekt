#include <stdio.h>
#include <string.h>

#include "datastructures.h"
#include "constants.h"
#include "utilities.h"


void main() {
    student student1;
    strcpy(student1.first_name, "Nick");
    strcpy(student1.surname, "Winter");
    strcpy(student1.course_of_study, "Mechatronik");
    student1.phone_number = 4915151727981;
    student1.enrollment_year = 2023;
    student1.student_number = 202050;
    strcpy(student1.home_address.city, "Buxtehude");
    strcpy(student1.home_address.street, "Estebrügger Straße");
    student1.home_address.house_number = 31;
    student1.home_address.postal_code = 21614;
    strcpy(student1.company.contact_person.first_name, "Rafael");
    strcpy(student1.company.contact_person.surname, "Götzen");
    strcpy(student1.company.name, "Airbus");

    generate_company_email(student1.company.contact_person.email, student1.company.contact_person.first_name, student1.company.contact_person.surname, student1.company.name);
    generate_hs21_email(student1.email, student1.first_name, student1.surname);

    student1.company.contact_person.phone_number = 1234567890;
    strcpy(student1.company.address.city, "Hamburg");
    strcpy(student1.company.address.street, "Kreetslag");
    student1.company.address.house_number = 10;
    student1.company.address.postal_code = 21129;

    printf("%s", student1.company.contact_person.email);


    getchar();
}
