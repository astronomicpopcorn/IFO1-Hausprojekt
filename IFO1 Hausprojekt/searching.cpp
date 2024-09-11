#include "datastructures.h"
#include "constants.h"
#include "utilities.h"

#include <string.h>

//checks for substring in string, but converts main string to lowercase. expects query to already be lowercase
bool strstr_insensitive(char *string_to_search, char *query_string) {
    char temp_search_string[email_length]; // to not modify original input
    strcpy(temp_search_string, string_to_search);
    lowercase_string(temp_search_string);
    return strstr(temp_search_string, query_string) != NULL;
}


//search a single datapoint for any match with a query. query will be split by whitespace and punctuation (Will return true if query is "Nick Heinz Olaf" and searched student contains "Nick" anywhere)
//TODO: Make case insensitive
bool search_datapoint(struct student *student, char _query[query_length]) {
    if (student->is_empty) {
        return false;
    }
    char query[query_length];
    bool match = false;
    bool all_match = true;
    char *token;
    

    strcpy(query, _query); //to not modify original query string
    lowercase_string(query);

    token = strtok(query, " ,.");      //split query into tokens
    while (token != NULL) {    //loop over all tokens
        match = false;
        //*student base data
        
        
        match = match || strstr_insensitive(student->student_number, token);
        match = match || strstr_insensitive(student->first_name, token);
        match = match || strstr_insensitive(student->last_name, token);
        match = match || strstr_insensitive(student->email, token);
        match = match || strstr_insensitive(student->enrollment_year, token);
        match = match || strstr_insensitive(student->course_of_study, token);
        match = match || strstr_insensitive(student->phone_number, token);
        //*student address
        match = match || strstr_insensitive(student->home_address.street, token);
        match = match || strstr_insensitive(student->home_address.house_number, token);
        match = match || strstr_insensitive(student->home_address.city, token);
        match = match || strstr_insensitive(student->home_address.postal_code, token);
        //*student company
        match = match || strstr_insensitive(student->company.name, token);
        //company address
        match = match || strstr_insensitive(student->company.address.street, token);
        match = match || strstr_insensitive(student->company.address.house_number, token);
        match = match || strstr_insensitive(student->company.address.city, token);
        match = match || strstr_insensitive(student->company.address.postal_code, token);
        //company contact_person
        match = match || strstr_insensitive(student->company.contact_person.first_name, token);
        match = match || strstr_insensitive(student->company.contact_person.last_name, token);
        match = match || strstr_insensitive(student->company.contact_person.email, token);
        match = match || strstr_insensitive(student->company.contact_person.phone_number, token);

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
    if (strlen(query) == 0) {
        for (p = 0; p < dataset_size; p++) {
            list_of_matching_indices[p] = p;
        }
        return 150;
    }

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
