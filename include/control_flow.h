#ifndef CONTROL_FLOW_H
#define CONTROL_FLOW_H

#include <stdio.h>
#include "symbol_table.h"
#include "tokenizer.h"

void handle_bool_if(TokenList tokens, FILE *file, int *line_number, bool truth[], int *bool_count);

void handle_comparison_if(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count);

void handle_logical_if(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count);

int skip_until_else_or_endif(FILE *file, int *line_number);

int skip_until_endif(FILE *file, int *line_number);

int skip_until_endwhile(FILE *file, int *line_number);

void handle_bool_while(TokenList tokens, FILE *file, int *line_number, bool truth[], int *bool_count, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count);

void handle_comparsion_while(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count);

void handle_logical_while(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count);

void handle_simple_repeat(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count);

void handle_arthmetic_repeat(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count);

int skip_until_endrepeat(FILE *file, int *line_number);

int control_loop(FILE *file, int *line_number, TokenType loop);

int get_repeat_value(Token value, whole num[], int *whole_count, int line_number);

int resolve_bool_value(Token token, bool truth[], int bool_count, int *line_number);

int evaluate_comparison_numeric(double v1, double v2, TokenType op, int *line_number);

int evalute_comparison_srting(const char *v1, const char *v2, TokenType op, int *line_number);

int evalute_logical_op(int left, int right, Token op, int *line_number);

void resolve_value(Token token, double *out_num, int *found_num, const char **out_str, int *is_string, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count,int line_number);

#endif