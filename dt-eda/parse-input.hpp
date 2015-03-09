/**
   \file parse-input.hpp
   \brief Header file for parse-input.cpp.
*/

#include <stdio.h>

#include "eda.hpp"

void parse_input_file(FILE *f, Parameters *params);
void param_help();
int get_new_identifier(FILE *f, char *s);
int get_int_value(FILE *f, int &val);
int print_parameters(Parameters *params);
