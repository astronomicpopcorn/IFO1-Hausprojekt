#pragma once
#include "constants.h"
#include "datastructures.h"


extern bool search_datapoint(struct student *student, char _query[query_length]);
extern int search_dataset(student students[dataset_size], char query[query_length], short int list_of_matching_indices[dataset_size]);
