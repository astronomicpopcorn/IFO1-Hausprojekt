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

extern windowelement make_window_element(int column, int row, int width, const char *label, int id, int type, const char *def_col, const char *highlight_col, const char *active_col, bool is_highlighted, bool is_active);
extern void update_highlighted_element(windowelement *element_array, int array_length, char c);

extern void generate_table_ends(char *table_string, bool is_bottom);

extern void update_string(char *target_string, int target_string_max_length, char c);
extern void update_student_data(student *student_array, int student_index, int element_index, char c);

extern void update_windowelements_labels(windowelement *element_array, student *student_array, int student_index, char *on_color, char *off_color);
extern void initialize_windowelements(windowelement *element_array, char* main_color, char* interactable_color, char* highlight_color, char* active_color);