#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#include "datastructures.h"
#include "constants.h"
#include "utilities.h"
#include "datamodification.h"
#include "windowinteractions.h"
#include "searching.h"

void main() {

    short int matching_indices[dataset_size]; //used for search function
    student students[dataset_size]; //main array
    
    strcpy(students[0].first_name, "Nick");
    strcpy(students[0].surname, "Winter");
    strcpy(students[0].course_of_study, "Mechatronik");
    strcpy(students[0].phone_number, "4915151727981");
    strcpy(students[0].enrollment_year, "2023");
    strcpy(students[0].student_number, "202050");
    strcpy(students[0].home_address.city, "Buxtehude");
    strcpy(students[0].home_address.street, "Estebrügger Straße");
    strcpy(students[0].home_address.house_number, "31A");
    strcpy(students[0].home_address.postal_code, "21614");
    strcpy(students[0].company.contact_person.first_name, "Rafael");
    strcpy(students[0].company.contact_person.surname, "Götzen");
    strcpy(students[0].company.name, "Airbus");

    generate_company_email(students[0].company.contact_person.email, students[0].company.contact_person.first_name, students[0].company.contact_person.surname, students[0].company.name);
    generate_hs21_email(students[0].email, students[0].first_name, students[0].surname);

    strcpy(students[0].company.contact_person.phone_number, "1234567890");
    strcpy(students[0].company.address.city, "Hamburg");
    strcpy(students[0].company.address.street, "Kreetslag");
    strcpy(students[0].company.address.house_number, "10");
    strcpy(students[0].company.address.postal_code, "21129");



    strcpy(students[1].first_name, "Ole");
    strcpy(students[1].surname, "Spindelndreher");
    strcpy(students[1].course_of_study, "Mechatronik");
    strcpy(students[1].phone_number, "4915151727981");
    strcpy(students[1].enrollment_year, "2023");
    strcpy(students[1].student_number, "02050");
    strcpy(students[1].home_address.city, "Estebrügge");
    strcpy(students[1].home_address.street, "Bahnhofsstraße");
    strcpy(students[1].home_address.house_number, "76");
    strcpy(students[1].home_address.postal_code, "21614");
    strcpy(students[1].company.contact_person.first_name, "Martin");
    strcpy(students[1].company.contact_person.surname, "Möhre");
    strcpy(students[1].company.name, "Airbus");

    generate_company_email(students[1].company.contact_person.email, students[1].company.contact_person.first_name, students[1].company.contact_person.surname, students[1].company.name);
    generate_hs21_email(students[1].email, students[1].first_name, students[1].surname);

    strcpy(students[1].company.contact_person.phone_number, "739246248");
    strcpy(students[1].company.address.city, "Hamburg");
    strcpy(students[1].company.address.street, "Kreetslag");
    strcpy(students[1].company.address.house_number, "10");
    strcpy(students[1].company.address.postal_code, "21129");



    strcpy(students[2].first_name, "Jill Kendra");
    strcpy(students[2].surname, "Hermann");
    strcpy(students[2].course_of_study, "Logistik");
    strcpy(students[2].phone_number, "4915151727981");
    strcpy(students[2].enrollment_year, "2023");
    strcpy(students[2].student_number, "202050");
    strcpy(students[2].home_address.city, "Hamburg");
    strcpy(students[2].home_address.street, "Linker Weg");
    strcpy(students[2].home_address.house_number, "12");
    strcpy(students[2].home_address.postal_code, "21614");
    strcpy(students[2].company.contact_person.first_name, "Hans");
    strcpy(students[2].company.contact_person.surname, "Heinrich");
    strcpy(students[2].company.name, "Lufthansa");

    generate_company_email(students[2].company.contact_person.email, students[2].company.contact_person.first_name, students[2].company.contact_person.surname, students[2].company.name);
    generate_hs21_email(students[2].email, students[2].first_name, students[2].surname);

    strcpy(students[2].company.contact_person.phone_number, "8597243543");
    strcpy(students[2].company.address.city, "Hamburg");
    strcpy(students[2].company.address.street, "Flughafenstraße");
    strcpy(students[2].company.address.house_number, "335");
    strcpy(students[2].company.address.postal_code, "74239");



    strcpy(students[3].first_name, "Max");
    strcpy(students[3].surname, "Mustermann");
    strcpy(students[4].first_name, "Timon");
    strcpy(students[4].surname, "Trompete");
    strcpy(students[5].first_name, "Alexander");
    strcpy(students[5].surname, "Müller");
    strcpy(students[6].first_name, "Jean Jaques");
    strcpy(students[6].surname, "Mustermann");
    strcpy(students[7].first_name, "Florian");
    strcpy(students[7].surname, "Flöte");
    strcpy(students[8].first_name, "Martin");
    strcpy(students[8].surname, "von Margarine");
    strcpy(students[9].first_name, "Max");
    strcpy(students[9].surname, "Krombacher");
    
    for (int i = 0; i < 10; i++) {
        students[i].is_empty = false;
    }

    students[12] = enter_datapoint();

    //test non-waiting typing - WORKS!
    //char c = 0;
    //char buff[100] = "\0";
    //int ptr = 0;
    //int ctr = 0;
    //while(c != '\n' && c != '\r'){
    //    while(kbhit()){
    //        c = getch();
    //        if(c == 8 && ptr > 0){
    //            ptr--;
    //            buff[ptr] = '\0';
    //        }
    //        else if(c != 8){
    //            buff[ptr] = c;
    //            ptr++;
    //            buff[ptr] = '\0';
    //        }
    //    }
    //    printf("\033[2J\033[H%s\n%i", buff, ctr);
    //    ctr++;
    //    Sleep(500);
    //}


    //mouse interactions: getAsyncKeyState(somethin' magic); - WORKS!
    //while (true) {
    //    if (GetAsyncKeyState(VK_LBUTTON)) {
    //        printf("%s", "\033[H:)");
    //    }
    //    else {
    //        printf("%s", "\033[H  ");
    //    }
    //}





    //DYNAMIC SEARCHING. 
    //Put into function that returns array of indexes

    char t = '\0';
    char buffer[100] = "\0";
    int buffer_length = 0;
    while (t != '\r') {
        t = getch();
        if (t == 8 && buffer_length > 0) {
            buffer[buffer_length - 1] = '\0';
            buffer_length--;
        }
        else if (t != 8){
            buffer[buffer_length] = t;
            buffer[buffer_length + 1] = '\0';
            buffer_length++;
        }
        printf("%s", "\033[2J\033[H");
        printf("> %s|\n", buffer);
        for(int i = 0; i < dataset_size; i++){
            if(search_datapoint(&students[i], buffer)){
                printf("%3i: %s %s\n", i, students[i].first_name, students[i].surname);
            }
        }
    }



    // THIS PUTS THE CURSOR ON DA GODDAMN SCREEN
    // put it into a function. please.

    //while (true) {
    //    Vector2D pos = get_mouse_on_window();
    //    Vector2D consolesize = get_console_size();
    //    Vector2D topleft, size;
    //    get_window_position(&topleft, &size);
    //    consolesize.y += 2;
    //    pos.y += 10;
    //    pos.x = pos.x / (size.x / consolesize.x) - 1;
    //    pos.y = pos.y / (size.y / consolesize.y) - 2;
    //    char screenbuffer[200*200];
    //    int count = 0;
    //    for (int y = 0; y < consolesize.y; y++) {
    //        for (int x = 0; x < consolesize.x; x++) {
    //            if (y == pos.y && x == pos.x) {
    //                screenbuffer[count] = 'O';
    //            }
    //            else {
    //                screenbuffer[count] = ' ';
    //            }
    //            count++;
    //        }
    //    }
    //    screenbuffer[count] = '\0';
    //    printf("\033[H%s", screenbuffer);
    //    //printf("\033[H%4i %4i", pos.x, pos.y);
    //}


    //getchar();
}
