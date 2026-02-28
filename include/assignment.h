#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "tokenizer.h"
#include "symbol_table.h"
#include "error.h"

typedef enum {
    ASSIGN_OK,
    ASSIGN_NOT,
    EQUAL_NOT
} assign_check_list;

assign_check_list is_literal_assignment(TokenList tokens);

assign_check_list is_variable_copy(TokenList tokens);

assign_check_list is_literal_arithmetic_exp(TokenList tokens);

assign_check_list is_arithmetic_exp_copy(TokenList tokens);

assign_check_list is_mixed_arthmetic_exp(TokenList tokens);

assign_check_list is_variable_comparison_exp(TokenList tokens);

assign_check_list is_logical_exp(TokenList tokens);

assign_check_list is_not_exp(TokenList tokens);

void assign_literal(Token varToken, Token valueToken, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number);

void assign_copy(Token varToken, Token valueToken, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number);

void assign_literal_arithemitic_exp(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *booL_count, int line_number);

void assign_variable_arithemitic_exp(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *booL_count, int line_number);

void assign_variable_comparison(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int*symbol_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number);

void assign_logical_exp(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int*symbol_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number);

void assign_not(Token varToken, Token right, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number);

void assign_numeric_result(Token varToken, double result, whole num[], int *whole_count, real decimal[], int *real_count, int line_number);

int is_bool_variable(char *name, bool truth[], int bool_count);

void get_variable_value(Token left, Token right, double *v1, double *v2, char **s1, char **s2, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, int line_number);

#endif