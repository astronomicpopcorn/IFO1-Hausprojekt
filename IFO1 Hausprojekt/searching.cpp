#include "datastructures.h"
#include "constants.h"

#include <string.h>





//search a single datapoint for any match with a query. query will be split by whitespace and punctuation (Will return true if query is "Nick Heinz Olaf" and searched student contains "Nick" anywhere)
//TODO: Make case insensitive
// should use AND logic for tokens instead of OR (untested)
bool search_datapoint(struct student *student, char _query[query_length]) {
    if (student->is_empty) {
        return false;
    }
    char query[query_length];
    strcpy(query, _query); //to not modify original query string
    bool match = false;
    bool all_match = true;
    char *token;
    token = strtok(query, " ,.");      //split query into tokens
    while (token != NULL) {    //loop over all tokens
        match = false;
        //*student base data
        match = match || strstr(student->student_number, token) != NULL;
        match = match || strstr(student->first_name, token) != NULL;
        match = match || strstr(student->surname, token) != NULL;
        match = match || strstr(student->email, token) != NULL;
        match = match || strstr(student->enrollment_year, token) != NULL;
        match = match || strstr(student->course_of_study, token) != NULL;
        match = match || strstr(student->phone_number, token) != NULL;
        //*student address
        match = match || strstr(student->home_address.street, token) != NULL;
        match = match || strstr(student->home_address.house_number, token) != NULL;
        match = match || strstr(student->home_address.city, token) != NULL;
        match = match || strstr(student->home_address.postal_code, token) != NULL;
        //*student company
        match = match || strstr(student->company.name, token) != NULL;
        //company address
        match = match || strstr(student->company.address.street, token) != NULL;
        match = match || strstr(student->company.address.house_number, token) != NULL;
        match = match || strstr(student->company.address.city, token) != NULL;
        match = match || strstr(student->company.address.postal_code, token) != NULL;
        //company contact_person
        match = match || strstr(student->company.contact_person.first_name, token) != NULL;
        match = match || strstr(student->company.contact_person.surname, token) != NULL;
        match = match || strstr(student->company.contact_person.email, token) != NULL;
        match = match || strstr(student->company.contact_person.phone_number, token) != NULL;

        //Update Token
        token = strtok(NULL, " ,.");
        all_match = all_match && match;
    }
    return all_match;
    //strstr() != NULL;
}


int search_dataset(student students[dataset_size], char query[query_length], short int list_of_matching_indices[dataset_size]) {
    int num_of_matches = 0;
    int p = 0; //points to position in list_of_matching_indices
    for (int i = 0; i < dataset_size; i++) {
        if (search_datapoint(&students[i], query)) {
            list_of_matching_indices[p] = i;
            p++;
            num_of_matches++;
        }
    }
    while (p < dataset_size) {
        list_of_matching_indices[p] = -1;
        p++;
    }
    return num_of_matches;
}