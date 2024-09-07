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
    char last_name[last_name_length] = "\0";
    char phone_number[phone_number_length] = "\0";
    char email[email_length] = "\0";
};

typedef struct company {
    char name[company_name_length] = "\0";
    address address;
    contact_person contact_person;
};

typedef struct student {
    bool is_empty = true;
    char student_number[student_number_length] = "\0";
    char first_name[first_name_length] = "\0";
    char last_name[last_name_length] = "\0";
    char email[email_length] = "\0";
    char enrollment_year[enrollment_year_length] = "\0";
    char course_of_study[course_of_study_length] = "\0";
    address home_address;
    char phone_number[phone_number_length] = "\0";
    company company;
};



typedef struct windowelement {
    Vector2D position;
    Vector2D size;

    char label[windowelement_label_length] = "";
    char text_buffer[query_length] = "";
    int id = -1;
    int type = 0;
    /*
    0: simple text box. not interactable
    1: button. selectable
    2: text input box

    */
    bool highlighted = false;

    char default_color[color_length] = "";
    char highlighted_color[color_length] = "";

};
