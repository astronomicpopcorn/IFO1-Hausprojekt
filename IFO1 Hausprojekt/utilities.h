#pragma once
#include "datastructures.h"

extern void copy_string(char* destination, char* source);
extern void lowercase_string(char *ptr);
extern bool is_mouse_pressed();
extern void print_student(student student);

extern bool save_file(student list[dataset_size], const char* filename);
extern bool load_file(student list[dataset_size], const char* filename);
extern void add_file_extension(char filename[filename_length]);

extern void replace_whitespace(char* string_to_change, char replacement);