#pragma once

const unsigned short int dataset_size = 150;

const unsigned short int first_name_length = 32;
const unsigned short int last_name_length = 32;
const unsigned short int company_name_length = 32;

const unsigned short int street_name_length = 32;
const unsigned short int city_name_length = 32;
const unsigned short int house_number_length = 8;
const unsigned short int postal_code_length = 8;

const unsigned short int course_of_study_length = 32;
const unsigned short int phone_number_length = 32;
const unsigned short int student_number_length = 8;
const unsigned short int enrollment_year_length = 8;

const unsigned short int email_length = first_name_length + last_name_length + company_name_length + 32;



const unsigned short int query_length = 64;
const unsigned short int filename_length = 64;

const unsigned short int async_input_length = 128;

const unsigned short int windowelement_list_length = 32;

const unsigned short int color_length = 14;
const unsigned short int windowelement_label_length = 128;
const unsigned short int windowelement_array_length = 256;


//on my large screen, maximum console size is 280x75. 
const unsigned long int max_display_string_length = 280 * 75 * color_length;

