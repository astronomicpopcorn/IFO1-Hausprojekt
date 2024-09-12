#pragma once

#include "constants.h"

//simple Vector made from integers
typedef struct Vector2D {
    int x;
    int y;
};

//reusable address
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

//student data is divided into multiple structs for organizational purposes
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


//a windowelement is what the rendering function uses to display text anywhere on the screen.
typedef struct windowelement {
    Vector2D position; //position of the leftmost char
    int width;         //can only be one char tall

    char label[windowelement_label_length] = ""; //the text displayed on the element
    int id = -1;    //an optional identifier (mostly for button types)
    int type = 0;   //determines behaviour
    /*
    type 0: simple text display
    type 1: button (enter to activate)
    type 2: text input (enter to start and stop writing)
    */
    bool highlighted = false;
    bool active = false;    //used to determine color

    //space for three different color strings
    char default_color[color_length] = "";
    char highlighted_color[color_length] = "";
    char active_color[color_length] = "";

};
