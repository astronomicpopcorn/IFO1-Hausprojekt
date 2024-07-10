#pragma once

#include "constants.h"

typedef struct Vector2D {
    int x;
    int y;
};

typedef struct address {
    char street[street_name_length] = "\0";
    char house_number[house_number_length] = "\0";
    char postal_code[postal_code_length] = "\0";
    char city[city_name_length] = "\0";
};

typedef struct contact_person {
    char first_name[first_name_length] = "\0";
    char surname[surname_length] = "\0";
    char phone_number[phone_number_length] = "\0";
    char email[email_length] = "\0";
};

typedef struct company {
    char name[company_name_length] = "\0";
    struct address address;
    struct contact_person contact_person;
};

typedef struct student {
    bool is_empty = false; //SHOULD BE SET TO TRUE!!!!!
    char student_number[student_number_length] = "\0";
    char first_name[first_name_length] = "\0";
    char surname[surname_length] = "\0";
    char email[email_length] = "\0";
    char enrollment_year[enrollment_year_length] = "\0";
    char course_of_study[course_of_study_length] = "\0";
    struct address home_address;
    char phone_number[phone_number_length] = "\0";
    struct company company;
};
