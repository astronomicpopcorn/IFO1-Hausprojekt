#pragma once

#include "constants.h"

void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length], char company_name[company_name_length]);
void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length]);

bool search_datapoint(struct student *student, char _query[query_length]);
int search_dataset(student students[dataset_size], char query[query_length], list_of_matching_indices[dataset_size]);

bool get_window_position(Vector2D *topleft, Vector2D *size);
Vector2D get_console_size();
Vector2D get_mouse_position();
Vector2D get_mouse_on_window();
