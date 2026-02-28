#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "symbol_table.h"
#include "tokenizer.h"
#include "assignment.h"
#include "control_flow.h"

// Function to dispatch execution based on the first token
void interpret(TokenList tokens, const char *line, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to Make [declare] the variable
void make_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to SET [assign] the value for variable
void set_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to print [ printf -----> print ]
void print_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to take input from user [ scanf -----> take]
void take_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count); 

// Function to Dispatch different If statements
void if_ez(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to Dispatch different While statements
void while_ez(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to Dispatch different Repeat statements
void repeat_ez(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count);

// Function to get the value of variable for SET [assign]
double get_value(char *token, whole num[], int whole_count, real decimal[], int real_count, bool truht[], int bool_count, int line_number);

char get_char_value(Token character, symbol chara[], int *symbol_couunt, int line_number);

char *get_string_value(Token value, string str[], int *string_count, int line_number);

#endif