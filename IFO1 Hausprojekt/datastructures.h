#pragma once
#include "constants.h"

typedef struct address {
    char street[street_name_length];
    int house_number;
    int postal_code;
    char city[city_name_length];
};

typedef struct contact_person {
    char first_name[first_name_length];
    char surname[surname_length];
    unsigned long long int phone_number;
    char email[email_length];
};

typedef struct company {
    char name[company_name_length];
    struct address address;
    struct contact_person contact_person;
};

typedef struct student {
    bool is_empty = true;
    unsigned int student_number;
    char first_name[first_name_length];
    char surname[surname_length];
    unsigned short int enrollment_year;
    char course_of_study[course_of_study_length];
    struct home_address;
    unsigned long int phone_number;
    struct company company;
};
