#pragma once
#include "constants.h"
#include "datastructures.h"


extern void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char last_name[last_name_length], char company_name[company_name_length]);
extern void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char last_name[last_name_length]);

extern student empty_datapoint();
extern student enter_datapoint();
