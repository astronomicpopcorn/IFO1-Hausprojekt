#include "datastructures.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

void generate_company_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length], char company_name[company_name_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, surname);
    strcat(email_destination, "@");
    strcat(email_destination, company_name);
    strcat(email_destination, ".de");
}

void generate_hs21_email(char email_destination[email_length], char first_name[first_name_length], char surname[surname_length]) {
    strcpy(email_destination, "");
    strcat(email_destination, first_name);
    strcat(email_destination, ".");
    strcat(email_destination, surname);
    strcat(email_destination, "@stud.hs21.de");
}

//search a single datapoint for any match with a query. query will be split by whitespace and punctuation (Will return true if query is "Nick Heinz Olaf" and searched student contains "Nick" anywhere)
//TODO: Make case insensitive
bool search_datapoint(struct student *student, char _query[query_length]){
    if(student->is_empty){
        return false;
    }
    char query[query_length];
    strcpy(query, _query); //to not modify original query string
    bool match = false;
    char stringified_number[stringified_number_length];
    char *token;
    token = strtok(query, " ,.");      //split query into tokens
    while(token != NULL && !match){    //loop over all tokens while no match has been found
        //*student base data
        sprintf(stringified_number, "%i", student->student_number);
        match = match || strstr(stringified_number, token) != NULL;
        match = match || strstr(student->first_name, token) != NULL;
        match = match || strstr(student->surname, token) != NULL;
        match = match || strstr(student->email, token) != NULL;
        sprintf(stringified_number, "%i", student->enrollment_year);
        match = match || strstr(stringified_number, token) != NULL;
        match = match || strstr(student->course_of_study, token) != NULL;
        sprintf(stringified_number, "%i", student->phone_number);
        match = match || strstr(stringified_number, token) != NULL;
        //*student address
        match = match || strstr(student->home_address.street, token) != NULL;
        match = match || strstr(student->home_address.house_number, token) != NULL;
        match = match || strstr(student->home_address.city, token) != NULL;
        sprintf(stringified_number, "%i", student->home_address.postal_code);
        match = match || strstr(stringified_number, token) != NULL;
        //*student company
        match = match || strstr(student->company.name, token) != NULL;
        //company address
        match = match || strstr(student->company.address.street, token) != NULL;
        match = match || strstr(student->company.address.house_number, token) != NULL;
        match = match || strstr(student->company.address.city, token) != NULL;
        sprintf(stringified_number, "%i", student->company.address.postal_code);
        match = match || strstr(stringified_number, token) != NULL;
        //company contact_person
        match = match || strstr(student->company.contact_person.first_name, token) != NULL;
        match = match || strstr(student->company.contact_person.surname, token) != NULL;
        match = match || strstr(student->company.contact_person.email, token) != NULL;
        sprintf(stringified_number, "%i", student->company.contact_person.phone_number);
        match = match || strstr(stringified_number, token) != NULL;

        //Update Token
        token = strtok(NULL, " ,.");
    }
    return match;
    //strstr() != NULL;
}


int search_dataset(student students[dataset_size], char query[query_length], list_of_matching_indices[dataset_size]){
    int num_of_matches = 0;
    int p = 0; //points to position in list_of_matching_indices
    for(int i = 0; i < dataset_size; i++){
        if(search_datapoint(&students[i], query){
            list_of_matching_indices[p] = i;
            p++;
            num_of_matches++;
        }
    }
    while(p < dataste_size){
        list_of_matching_indices[p] = -1;
        p++;
    }
    return num_of_matches;
}













bool get_window_position(Vector2D *topleft, Vector2D *size){
    HWND console_window = GetForegroundWindow();
    if(console_window == NULL){
        return false;
    }
    RECT window_rect;
    if(GetWindowRect(console_window, &window_rect)){
        topleft->x = window_rect.left;
        topleft->y = window_rect.top;
        size->x = window_rect.right - window_rect.left;
        size->y = window_rect.bottom - window_rect.top;
        return true;
    }
    return false;
}

Vector2D get_console_size() {
    Vector2D consolesize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consolesize.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consolesize.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return consolesize;
}

Vector2D get_mouse_position(){
    Vector2D result;
    result.x = -1;
    result.y = -1;
    POINT curser_position;
    if(GetCursorPos(&curser_position)){
        result.x = curser_position.x;
        result.y = curser_position.y;
    }
    return result;
}

Vector2D get_mouse_on_window(){
    Vector2D result;
    Vector2D window_position, window_size, mouse_position;
    mouse_position = get_mouse_position();
    if(!get_window_position(&window_position, &window_size) || (mouse_position.x == -1 && mouse_position.y == -1)){
        result.x = -1;
        result.y = -1;
        return result;
    }
    result.x = mouse_position.x - window_position.x;
    result.y = mouse_position.y - window_position.y;
    if(result.x < 0 || result.x >= window_size.x){
        result.x = -1;
    }
    if(result.y < 0 || result.y >= window_size.y){
        result.y = -1;
    }
    return result;
}

Vector2D get_mouse_on_console(){
    Vector2D pos = get_mouse_on_window();
    Vector2D consolesize = get_console_size();
    Vector2D topleft, size;
    get_window_position(&topleft, &size);
    pos.x = pos.x / (size.x / consolesize.x);
    pos.y = pos.y / (size.y / consolesize.y);
    return pos;
}





