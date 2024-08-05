#include "datastructures.h"
#include "constants.h"
#include "windowinteractions.h"

#include <ctype.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copy_string(char* destination, char* source){
    unsigned short int dest_ctr = 0;
    unsigned short int src_ctr = 0;
    while(*(destination + dest_ctr) != '\0' && *(source + src_ctr) != '\0'){
        *(destination + dest_ctr) = *(source + src_ctr);
        dest_ctr++;
        src_ctr++;
    }
    *(destination + dest_ctr) = '\0';
}

bool async_scanf(char buffer[async_input_length], char character_to_check){
    bool character_found = false;
    char c = 0;
    unsigned short int terminator_index;
    while(kbhit()){
        terminator_index = strlen(buffer);
        c = getch();
        if(character_to_check == '\n' || character_to_check == '\r'){
            if(c == '\n' || c == '\r'){
                character_found = true;
            }
        }
        else if(c == character_to_check){
            character_found = true;
        }
        if(c == 8 && terminator_index > 0){
            buffer[terminator_index - 1] = '\0';
        }
        else if(c != 8 && terminator_index < async_input_length - 1){
            buff[terminator_index] = c;
            buff[terminator_index + 1] = '\0'
        }
    }
    return character_found;
}



void lowercase_string(char *ptr){
    while (*ptr) {
        *ptr = tolower((unsigned char) *ptr);
        ptr++;
    }
}

bool is_mouse_pressed(){
    return GetAsyncKeyState(VK_LBUTTON) != 0;
}


void print_student(student student){
    printf("%s %s\n", student.first_name, student.last_name);
    printf("(%s, Jahrgang %s)\n", student.course_of_study, student.enrollment_year);
    printf("%s\n", student.email);
    printf("%s\n", student.phone_number);
    printf("%s %s\n", student.home_address.street, student.home_address.house_number);
    printf("%s %s\n", student.home_address.postal_code, student.home_address.city);
    printf("\nPraxispartner: %s\n", student.company.name);
    printf("%s %s\n", student.company.address.street, student.company.address.house_number);
    printf("%s %s\n", student.company.address.postal_code, student.company.address.city);
    printf("Kontaktperson:\n");
    printf("%s %s\n", student.company.contact_person.first_name, student.company.contact_person.last_name);
    printf("%s\n", student.company.contact_person.email);
    printf("%s\n", student.company.contact_person.phone_number);
}


//basic fileio
bool save_file(student list[dataset_size], const char* filename){
    FILE *out;
    out = fopen(filename, "wb");
    if(out == NULL){
        return false;
    }
    fwrite(list, sizeof(student) * dataset_size, 1, out);
    fclose(out);
    return true;
}

bool load_file(student list[dataset_size], const char* filename){
    FILE *in;
    in = fopen(filename, "rb");
    if(in == NULL){
        return false;
    }
    fread(list, sizeof(student) * dataset_size, 1, in);
    fclose(in);
    return true;
}

void add_file_extension(char filename[filename_length]){
    if(filename[0] == '\0'){
        strcpy(filename, "unnamed");
    }
    int len = strlen(filename);
    if(len < filename_length - 3){
        strcat(filename, ".db");
    }
    else{
        filename[filename_length - 4] = '.';
        filename[filename_length - 3] = 'd';
        filename[filename_length - 2] = 'b';
        filename[filename_length - 1] = '\0';
    }
}





void render_something(button buttonlist[button_list_length]){
    Vector2D console_size = get_console_size();
    char background_color[9] = "\033[97;44m";
    char button_color[9] = "\033[30;47m";
    char highlighted_button_color[10] = "\033[30;103m";
    const int frameSize = 20000;
    char frame[frameSize] = "";
    strcpy(frame, background_color);
    int i;
    bool buttonrendered = false;
    for(int y = 0; y < console_size.y - 1; y++){
        for(int x = 0; x < console_size.x; x++){
            i = 0;
            buttonrendered = false;
            while(buttonlist[i].id != -1 && i < button_list_length){
                if(y == buttonlist[i].position.y && x == buttonlist[i].position.x){
                    buttonrendered = true;
                    if(buttonlist[i].highlighted){
                        strcat(frame, highlighted_button_color);
                    }
                    else{
                        strcat(frame, button_color);
                    }
                    for (int j = 0; j < buttonlist[i].size.x; j++) {
                        if (j < strlen(buttonlist[i].label)) {
                            frame[strlen(frame)] = buttonlist[i].label[j];
                        }
                        else{
                            frame[strlen(frame)] = ' ';
                        }
                        x++;
                    }
                    x--;
                    strcat(frame, background_color);
                    break;
                }
                i++;
            }
            if(!buttonrendered){
                strcat(frame, " ");
            }
        }
        if (i < console_size.y - 1) {
            strcat(frame, "\n");
        }
        
    }
    printf("%s%s", "\033[H", frame);
}

void replace_whitespace(char* string_to_change, char replacement){
    for(int i = 0; string_to_change[i] != '\0'; i++){
        if(string_to_change[i] == ' '){
            string_to_change[i] = replacement;
        }
    }
}

void replace_umlaute(char mystring[32], char buffer[64]){
    int buffer_pointer = 0;
    int string_pointer = 0;
    while(mystring[string_pointer] != '\0'){
        if(mystring[string_pointer] == 'ä'){
            buffer[buffer_pointer] = 'a';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'Ä'){
            buffer[buffer_pointer] = 'A';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'ü'){
            buffer[buffer_pointer] = 'u';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'Ü'){
            buffer[buffer_pointer] = 'U';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'ö'){
            buffer[buffer_pointer] = 'o';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'Ö'){
            buffer[buffer_pointer] = 'O';
            buffer_pointer++;
            buffer[buffer_pointer] = 'e';
        }
        else if(mystring[string_pointer] == 'ß'){
            buffer[buffer_pointer] = 's';
            buffer_pointer++;
            buffer[buffer_pointer] = 's';
        }
        else{
            buffer[buffer_pointer] = mystring[string_pointer];
        }
        buffer_pointer++;
    }
}

//accepts 'u', 'd', 'l' and 'r' for up, down, left and right respectively
//returns false if no button is selected or direction is invalid. Otherwise true
bool select_next_button(button buttonlist[button_list_length], char direction){
    int current_selected = -1;
    int candidate_index = -1;
    int i;
    for(i = 0; i < button_list_length; i++){
        if(buttonlist[i].highlighted && buttonlist[i].id != -1){
            current_selected = i;
            break;
        }
    }
    if(current_selected == -1){
        return false;
    }

    switch(direction){
        case 'u':
            for(i = 0; i < button_list_length; i++){
                if(buttonlist[i].position.x == buttonlist[current_selected].position.x && buttonlist[i].position.y < buttonlist[current_selected].position.y && buttonlist[i].id != -1){
                    if(candidate_index == -1){
                        candidate_index = i;
                    }
                    else if(buttonlist[i].position.y > buttonlist[candidate_index].position.y){
                        candidate_index = i;
                    }
                }
            }
            break;
        case 'd':
            for(i = 0; i < button_list_length; i++){
                if(buttonlist[i].position.x == buttonlist[current_selected].position.x && buttonlist[i].position.y > buttonlist[current_selected].position.y && buttonlist[i].id != -1){
                    if(candidate_index == -1){
                        candidate_index = i;
                    }
                    else if(buttonlist[i].position.y < buttonlist[candidate_index].position.y){
                        candidate_index = i;
                    }
                }
            }
            break;
        case 'l':
            for(i = 0; i < button_list_length; i++){
                if(buttonlist[i].position.y == buttonlist[current_selected].position.y && buttonlist[i].position.x < buttonlist[current_selected].position.x && buttonlist[i].id != -1){
                    if(candidate_index == -1){
                        candidate_index = i;
                    }
                    else if(buttonlist[i].position.x > buttonlist[candidate_index].position.x){
                        candidate_index = i;
                    }
                }
            }
            break;
        case 'r':
            for(i = 0; i < button_list_length; i++){
                if(buttonlist[i].position.y == buttonlist[current_selected].position.y && buttonlist[i].position.x > buttonlist[current_selected].position.x && buttonlist[i].id != -1){
                    if(candidate_index == -1){
                        candidate_index = i;
                    }
                    else if(buttonlist[i].position.x < buttonlist[candidate_index].position.x){
                        candidate_index = i;
                    }
                }
            }
            break;
        default:
            return false;
            break;
    }
    if(candidate_index != -1){
        buttonlist[current_selected].highlighted = false;
        buttonlist[candidate_index].highlighted = true;
    }
}




