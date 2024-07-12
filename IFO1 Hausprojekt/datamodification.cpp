#include "datastructures.h"
#include "constants.h"

#include <stdio.h>
#include <string.h>

void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char last_name[last_name_length], char company_name[company_name_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, last_name);
    strcat(email_destination, "@");
    strcat(email_destination, company_name);
    strcat(email_destination, ".de");
}

void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char last_name[last_name_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, last_name);
    strcat(email_destination, "@stud.hs21.de");
}


student empty_datapoint(){
    student student;
    return student;
}

// very simple function to get a single datapoint. no fancy UI.
//quick and dirty: max string length not fixed!!!
student enter_datapoint() {
    student student;

    printf("%s", "Entering new student.\nE-Mail addresses will be automatically generated.\nFirst name: ");
    scanf("%[^\n]s", &student.first_name);
    getchar();
    printf("%s", "Last name: ");
    scanf("%[^\n]s", &student.last_name);
    getchar();
    printf("%s", "Student number: ");
    scanf("%[^\n]s", &student.student_number);
    getchar();
    printf("%s", "Course of Study: ");
    scanf("%[^\n]s", &student.course_of_study);
    getchar();
    printf("%s", "Enrollment year: ");
    scanf("%[^\n]s", &student.enrollment_year);
    getchar();
    printf("%s", "Phone number: ");
    scanf("%[^\n]s", &student.phone_number);
    getchar();

    printf("\n%s", "\nAddress of student\nCity: ");
    scanf("%[^\n]s", &student.home_address.city);
    getchar();
    printf("%s", "Postal code: ");
    scanf("%[^\n]s", &student.home_address.postal_code);
    getchar();
    printf("%s", "Street: ");
    scanf("%[^\n]s", &student.home_address.street);
    getchar();
    printf("%s", "House number: ");
    scanf("%[^\n]s", &student.home_address.house_number);
    getchar();

    printf("\n%s", "\nCompany name: ");
    scanf("%[^\n]s", &student.company.name);
    getchar();
    printf("%s", "Address of company\nCity: ");
    scanf("%[^\n]s", &student.company.address.city);
    getchar();
    printf("%s", "Postal code: ");
    scanf("%[^\n]s", &student.company.address.postal_code);
    getchar();
    printf("%s", "Street: ");
    scanf("%[^\n]s", &student.company.address.street);
    getchar();
    printf("%s", "House number: ");
    scanf("%[^\n]s", &student.company.address.house_number);
    getchar();

    printf("\n%s", "\nContact person information\nFirst name: ");
    scanf("%[^\n]s", &student.company.contact_person.first_name);
    getchar();
    printf("%s", "Last Name: ");
    scanf("%[^\n]s", &student.company.contact_person.last_name);
    getchar();
    printf("%s", "Phone number: ");
    scanf("%[^\n]s", &student.company.contact_person.phone_number);
    getchar();

    generate_hs21_email(student.email, student.first_name, student.last_name);
    generate_company_email(student.company.contact_person.email, student.company.contact_person.first_name, student.company.contact_person.last_name, student.company.name);

    student.is_empty = false;

    return student;
}
