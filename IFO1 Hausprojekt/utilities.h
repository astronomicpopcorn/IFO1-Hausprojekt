#pragma once
#include "datastructures.h"

void lowercase_string(char *ptr);
bool is_mouse_pressed();
void print_student(student student);

bool save_file(student list[dataset_size], const char* filename);
bool load_file(student list[dataset_size], const char* filename);
void add_file_extension(char filename[filename_length]);
