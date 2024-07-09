#pragma once

#include "constants.h"

void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length], char company_name[company_name_length]);
void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length]);

bool search_datapoint(struct student *student, char _query[query_length]);
