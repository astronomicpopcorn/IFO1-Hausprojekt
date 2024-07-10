#include "datastructures.h"
#include "constants.h"

#include <ctype.h>


void lowercase_string(char *ptr){
    while (*ptr) {
        *ptr = tolower((unsigned char) *ptr);
        ptr++;
    }
}

