#include "datastructures.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>

void generate_company_email (char email_destination[email_length], char first_name[first_name_length], char surname[surname_length], char company_name[company_name_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, surname);
    strcat(email_destination, "@");
    strcat(email_destination, company_name);
    strcat(email_destination, ".de");
}

void generate_hs21_email (char email_destination[email_length], char first_name[first_name_length], char surname[surname_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, surname);
    strcat(email_destination, "@stud.hs21.de");
}
