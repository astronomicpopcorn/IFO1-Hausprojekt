#pragma once

#include "constants.h"

typedef struct Vector2D {
    int x;
    int y;
};

typedef struct address {
    char street[street_name_length] = "\0";
    char house_number[house_number_length] = "\0";
    int postal_code;
    char city[city_name_length] = "\0";
};

typedef struct contact_person {
    char first_name[first_name_length] = "\0";
    char surname[surname_length] = "\0";
    unsigned long long int phone_number;
    char email[email_length] = "\0";
};

typedef struct company {
    char name[company_name_length] = "\0";
    struct address address;
    struct contact_person contact_person;
};

typedef struct student {
    bool is_empty = false;
    unsigned int student_number;
    char first_name[first_name_length] = "\0";
    char surname[surname_length] = "\0";
    char email[email_length] = "\0";
    unsigned short int enrollment_year;
    char course_of_study[course_of_study_length] = "\0";
    struct address home_address;
    unsigned long long int phone_number;
    struct company company;
};
