#include "datastructures.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>

void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length], char company_name[company_name_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, surname);
    strcat(email_destination, "@");
    strcat(email_destination, company_name);
    strcat(email_destination, ".de");
}

void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, surname);
    strcat(email_destination, "@stud.hs21.de");
}

bool search_datapoint(struct student *student, char query[query_length]){
    if(student.is_empty){
        return false;
    }
    bool match = false;
    char stringified_number[stringified_number_length];
    char *token;
    token = strtok(query, " ,.");
    while(token != NULL && !match){
        //student base data
        sprintf(stringified_number, "%i", student.student_number);
        match = match || strstr(stringified_number, token) != NULL;
        match = match || strstr(student.first_name, token) != NULL;
        match = match || strstr(student.surname, token) != NULL;
        match = match || strstr(student.email, token) != NULL;
        sprintf(stringified_number, "%i", student.enrollment_year);
        match = match || strstr(stringified_number, token) != NULL;
        match = match || strstr(student.course_of_study, token) != NULL;
        sprintf(stringified_number, "%i", student.phone_number);
        match = match || strstr(stringified_number, token) != NULL;
        //student address
        match = match || strstr(student.home_address.street, token) != NULL;
        match = match || strstr(student.home_address.house_number, token) != NULL;
        match = match || strstr(student.home_address.city, token) != NULL;
        sprintf(stringified_number, "%i", student.home_address.postal_code);
        match = match || strstr(stringified_number, token) != NULL;
        //student company
        match = match || strstr(student.company.name, token) != NULL;
        //company address
        match = match || strstr(student.company.address.street, token) != NULL;
        match = match || strstr(student.company.address.house_number, token) != NULL;
        match = match || strstr(student.company.address.city, token) != NULL;
        sprintf(stringified_number, "%i", student.company.address.postal_code);
        match = match || strstr(stringified_number, token) != NULL;
        //company contact_person
        match = match || strstr(student.company.contact_person.first_name, token) != NULL;
        match = match || strstr(student.company.contact_person.surname, token) != NULL;
        match = match || strstr(student.company.contact_person.email, token) != NULL;
        sprintf(stringified_number, "%i", student.company.contact_person.phone_number);
        match = match || strstr(stringified_number, token) != NULL;

        //Update Token
        token = strtok(NULL, " ,.")
    }
    
    //strstr() != NULL;
}









