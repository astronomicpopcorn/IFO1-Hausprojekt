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


    
    short int matching_indices[dataset_size]; //used for search function to store indeces of matching entries
    student students[dataset_size]; //main array
    
    //set some random students
    strcpy(students[0].first_name, "Nick");
    strcpy(students[0].last_name, "Winter");
    strcpy(students[0].course_of_study, "Mechatronik");
    strcpy(students[0].phone_number, "4915151727981");
    strcpy(students[0].enrollment_year, "2023");
    strcpy(students[0].student_number, "202050");
    strcpy(students[0].home_address.city, "Buxtehude");
    strcpy(students[0].home_address.street, "Estebrügger Straße");
    strcpy(students[0].home_address.house_number, "31A");
    strcpy(students[0].home_address.postal_code, "21614");
    strcpy(students[0].company.contact_person.first_name, "Rafael");
    strcpy(students[0].company.contact_person.last_name, "Götzen");
    strcpy(students[0].company.name, "Airbus");

    generate_company_email(students[0].company.contact_person.email, students[0].company.contact_person.first_name, students[0].company.contact_person.last_name, students[0].company.name);
    generate_hs21_email(students[0].email, students[0].first_name, students[0].last_name);

    strcpy(students[0].company.contact_person.phone_number, "1234567890");
    strcpy(students[0].company.address.city, "Hamburg");
    strcpy(students[0].company.address.street, "Kreetslag");
    strcpy(students[0].company.address.house_number, "10");
    strcpy(students[0].company.address.postal_code, "21129");



    strcpy(students[1].first_name, "Ole");
    strcpy(students[1].last_name, "Spindelndreher");
    strcpy(students[1].course_of_study, "Mechatronik");
    strcpy(students[1].phone_number, "4915151727981");
    strcpy(students[1].enrollment_year, "2023");
    strcpy(students[1].student_number, "02050");
    strcpy(students[1].home_address.city, "Estebrügge");
    strcpy(students[1].home_address.street, "Bahnhofsstraße");
    strcpy(students[1].home_address.house_number, "76");
    strcpy(students[1].home_address.postal_code, "21614");
    strcpy(students[1].company.contact_person.first_name, "Martin");
    strcpy(students[1].company.contact_person.last_name, "Möhre");
    strcpy(students[1].company.name, "Airbus");

    generate_company_email(students[1].company.contact_person.email, students[1].company.contact_person.first_name, students[1].company.contact_person.last_name, students[1].company.name);
    generate_hs21_email(students[1].email, students[1].first_name, students[1].last_name);

    strcpy(students[1].company.contact_person.phone_number, "739246248");
    strcpy(students[1].company.address.city, "Hamburg");
    strcpy(students[1].company.address.street, "Kreetslag");
    strcpy(students[1].company.address.house_number, "10");
    strcpy(students[1].company.address.postal_code, "21129");



    strcpy(students[2].first_name, "Jill Kendra");
    strcpy(students[2].last_name, "Hermann");
    strcpy(students[2].course_of_study, "Logistik");
    strcpy(students[2].phone_number, "4915151727981");
    strcpy(students[2].enrollment_year, "2023");
    strcpy(students[2].student_number, "202050");
    strcpy(students[2].home_address.city, "Hamburg");
    strcpy(students[2].home_address.street, "Linker Weg");
    strcpy(students[2].home_address.house_number, "12");
    strcpy(students[2].home_address.postal_code, "21614");
    strcpy(students[2].company.contact_person.first_name, "Hans");
    strcpy(students[2].company.contact_person.last_name, "Heinrich");
    strcpy(students[2].company.name, "Lufthansa");

    generate_company_email(students[2].company.contact_person.email, students[2].company.contact_person.first_name, students[2].company.contact_person.last_name, students[2].company.name);
    generate_hs21_email(students[2].email, students[2].first_name, students[2].last_name);

    strcpy(students[2].company.contact_person.phone_number, "8597243543");
    strcpy(students[2].company.address.city, "Hamburg");
    strcpy(students[2].company.address.street, "Flughafenstraße");
    strcpy(students[2].company.address.house_number, "335");
    strcpy(students[2].company.address.postal_code, "74239");



    strcpy(students[3].first_name, "Max");
    strcpy(students[3].last_name, "Mustermann");
    strcpy(students[4].first_name, "Timon");
    strcpy(students[4].last_name, "Trompete");
    strcpy(students[5].first_name, "Alexander");
    strcpy(students[5].last_name, "Müller");
    strcpy(students[6].first_name, "Jean Jaques");
    strcpy(students[6].last_name, "Mustermann");
    strcpy(students[7].first_name, "Florian");
    strcpy(students[7].last_name, "Flöte");
    strcpy(students[8].first_name, "Martin");
    strcpy(students[8].last_name, "von Margarine");
    strcpy(students[9].first_name, "Max");
    strcpy(students[9].last_name, "Krombacher");
    
    for (int i = 0; i < 10; i++) {
        students[i].is_empty = false;
    }

    //students[10] = enter_datapoint();

    //int k = 0;
    //while (!students[k].is_empty) {
    //    print_student(students[k]);
    //    printf("\n\nIndex %i:\n\n", k);
    //    k++;
    //}

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
    int num_results;
    printf("> %s|\n", buffer);
    do {
        t = getch();
        if (t == 8 && buffer_length > 0) {
            buffer[buffer_length - 1] = '\0';
            buffer_length--;
        }
        else if (t != 8 && t != '\r' && t != '\n') {
            buffer[buffer_length] = t;
            buffer[buffer_length + 1] = '\0';
            buffer_length++;
        }
        printf("%s", "\033[2J\033[H");
        printf("> %s|\n", buffer);
        num_results = search_dataset(students, buffer, matching_indices);
        for(int i = 0; i < num_results; i++){
            printf("%3i: %s %s\n", i, students[matching_indices[i]].first_name, students[matching_indices[i]].last_name);
        }
    } while (t != '\r');
    printf("%s", "\033[2J\033[H");
    for (int i = 0; i < num_results; i++) {
        printf("%s", "\n--------------------------------------------------------\n\n");
        print_student(students[matching_indices[i]]);
    }
    getchar();


}
