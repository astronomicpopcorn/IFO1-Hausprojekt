#pragma once
#include "constants.h"
#include "datastructures.h"


void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char last_name[last_name_length], char company_name[company_name_length]);
void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char last_name[last_name_length]);

student empty_datapoint();
student enter_datapoint();
