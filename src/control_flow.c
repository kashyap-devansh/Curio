#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "control_flow.h"
#include "interpreter.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "error.h"


//------------------------------------------ IF STATEMENTS FUNCTIONS ------------------------------------------

void handle_bool_if(TokenList tokens, FILE *file, int *line_number, bool truth[], int *bool_count) {
    int value = 0;

    if(tokens.count == 6) {
        int v1 = resolve_bool_value(tokens.token[1], truth, *bool_count, line_number);
        int v2 = resolve_bool_value(tokens.token[3], truth, *bool_count, line_number);    

        value = evalute_logical_op(v1, v2, tokens.token[2], line_number);

        if(tokens.token[4].type != TOK_THEN || tokens.token[5].type != TOK_END) {
            error_ez(E_SYNTAX_IF_MISSING_THEN, *line_number, NULL, NULL, '\0');
            exit(1);
        }

        if(!value) {
            int mis_end = skip_until_else_or_endif(file, line_number);
            
            if(mis_end == -1) {
                error_ez(E_SYNTAX_IF_MISSING_THEN, *line_number, NULL, NULL, '\0'); exit(1);
            }
            else if(skip_until_else_or_endif(file, line_number) == TOK_ELSE) return;
        }

        return;
    }

    if(tokens.count == 4) {
        value = resolve_bool_value(tokens.token[1], truth, *bool_count, line_number);

        if(tokens.token[2].type != TOK_THEN || tokens.token[3].type != TOK_END) {
            error_ez(E_SYNTAX_IF_MISSING_THEN, *line_number, "\0", "\0", '\0');
            exit(1);
        }

        if(!value) {
            int mis_end = skip_until_else_or_endif(file, line_number);

            if(mis_end == -1) {
                error_ez(E_SYNTAX_IF_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
            }
            else if(mis_end == TOK_ELSE) return;
        }

        return;
    }

    error_ez(E_SYNTAX_IF_BOOL_INVALID, *line_number, NULL, NULL, '\0');
    exit(1);
}

void handle_comparison_if(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count) {
    double v1 = 0, v2 = 0;
    int found1 = 0, found2 = 0;

    const char *s1 = NULL;
    const char *s2 = NULL;
    int is_string = 0;

    int value = 0;

    resolve_value(tokens.token[1], &v1, &found1, &s1, &is_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);
    resolve_value(tokens.token[3], &v2, &found2, &s2, &is_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);

    if(is_string) {
        if(s1 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, "\0", '\0'); exit(1); }

        if(s2 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, "\0", '\0'); exit(1); }
    }
    else {
        if(!found1) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, "\0", '\0'); exit(1); }

        if(!found2) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, "\0", '\0'); exit(1); }
    }

    if((s1 != NULL && v2) || (s2 != NULL && v1)) {
        error_ez(E_COMPARE_INVALID_OPERANDS, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(is_string) value = evalute_comparison_srting(s1, s2, tokens.token[2].type, line_number);
    else value = evaluate_comparison_numeric(v1, v2, tokens.token[2].type, line_number);

    if(tokens.token[4].type != TOK_THEN || tokens.token[5].type != TOK_END) {
        error_ez(E_SYNTAX_IF_MISSING_THEN, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(!value) {
        int mis_end = skip_until_else_or_endif(file, line_number);

        if(mis_end == -1) {
            error_ez(E_SYNTAX_IF_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
        }
        else if(mis_end == TOK_ELSE) return;
    }

    return;
}

void handle_logical_if(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count) {
    double left_v1 = 0, left_v2 = 0;
    int found_left_v1 = 0, found_left_v2 = 0;

    double right_v1 = 0, right_v2 = 0;
    int found_right_v1 = 0, found_right_v2 = 0;

    const char *left_s1 = NULL;
    const char *left_s2 = NULL;
    int is_left_string = 0;

    const char *right_s1 = NULL;
    const char *right_s2 = NULL;
    int is_right_string = 0;

    int value_left = 0, value_right = 0;

    resolve_value(tokens.token[1], &left_v1, &found_left_v1, &left_s1, &is_left_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);
    resolve_value(tokens.token[3], &left_v2, &found_left_v2, &left_s2, &is_left_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);

    if(is_left_string) {
        if(left_s1 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, NULL, '\0'); exit(1); }

        if(left_s2 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, NULL, '\0'); exit(1); }
    }
    else {
        if(!found_left_v1) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, NULL, '\0'); exit(1); }

        if(!found_left_v2) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, NULL, '\0'); exit(1); }
    }

    if((left_s1 != NULL && found_left_v2) || (left_s2 != NULL && found_left_v1)) {
        error_ez(E_COMPARE_INVALID_OPERANDS, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(is_left_string) value_left = evalute_comparison_srting(left_s1, left_s2, tokens.token[2].type, line_number);
    else value_left = evaluate_comparison_numeric(left_v1, left_v2, tokens.token[2].type, line_number);

    resolve_value(tokens.token[5], &right_v1, &found_right_v1, &right_s1, &is_right_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);
    resolve_value(tokens.token[7], &right_v2, &found_right_v2, &right_s2, &is_right_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);

    if(is_right_string) {
        if(right_s1 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[5].text, NULL, '\0'); exit(1); }

        if(right_s2 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[7].text, NULL, '\0'); exit(1); }
    }
    else {
        if(!found_right_v1) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[5].text, NULL, '\0'); exit(1); }

        if(!found_right_v2) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[7].text, NULL, '\0'); exit(1); }
    }

    if((right_s1 != NULL && found_right_v2) || (right_s2 != NULL && found_right_v1)) {
        error_ez(E_COMPARE_INVALID_OPERANDS, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(is_right_string) value_right = evalute_comparison_srting(right_s1, right_s2, tokens.token[6].type, line_number);
    else value_right = evaluate_comparison_numeric(right_v1, right_v2, tokens.token[6].type, line_number);

    int result = evalute_logical_op(value_left, value_right, tokens.token[4], line_number);

    if(tokens.token[8].type != TOK_THEN || tokens.token[9].type != TOK_END) {
        error_ez(E_SYNTAX_IF_MISSING_THEN, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(!result) {
    int mis_end = skip_until_else_or_endif(file, line_number);

        if(mis_end == -1) {
            error_ez(E_SYNTAX_IF_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
        }
        else if(mis_end == TOK_ELSE) return;
    }

    return;
}

int skip_until_else_or_endif(FILE *file, int *line_number) {
    int depth = 1;
    char line[500];

    while(fgets(line, sizeof(line), file)) {
        (*line_number)++;

        TokenList t = tokenize_line(line);

        if(t.count == 0) continue;

        if(t.token[0].type == TOK_IF) {
            depth++;
        }

        if(t.token[0].type == TOK_END_IF) {
            depth--;
        }

        if(depth == 1 && t.token[0].type == TOK_ELSE) {
            return TOK_ELSE;
        }

        if(depth == 0) {
            return TOK_END_IF;
        }
    }

    return -1;
}

int skip_until_endif(FILE *file, int *line_number) {
    int depth = 1;
    char line[500];

    while (fgets(line, sizeof(line), file)) {
        (*line_number)++;

        TokenList t = tokenize_line(line);
        if(t.count == 0) continue;

        if(t.token[0].type == TOK_IF) depth++;

        if(t.token[0].type == TOK_END_IF) depth--;

        if(depth == 0) return TOK_END_IF;
    }

    return -1;
}


//------------------------------------------ WHILE STATEMENTS FUNCTIONS ------------------------------------------

void handle_bool_while(TokenList tokens, FILE *file, int *line_number, bool truth[], int *bool_count, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count) {
    long while_pos = ftell(file);
    int while_line = *line_number;

    while(1) {
        int value = 0;

        if(tokens.count == 6) {
            int v1 = resolve_bool_value(tokens.token[1], truth, *bool_count, line_number);
            int v2 = resolve_bool_value(tokens.token[3], truth, *bool_count, line_number);
            value = evalute_logical_op(v1, v2, tokens.token[2], line_number);
        }
        else if(tokens.count == 4) {
            value = resolve_bool_value(tokens.token[1], truth, *bool_count, line_number);
        }
        else {
            error_ez(E_SYNTAX_WHILE_INVALID_BOOL_CONDITION, *line_number, NULL, NULL, '\0');
            exit(1);
        }

        if(!value) {
            if(skip_until_endwhile(file, line_number) == -1) {
                error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
                exit(1);
            }
            return;
        }

        char line[500];
        int depth = 1;
        int found_end = 0;
        int found_break = 0;
        int found_continue = 0;

        while(fgets(line, sizeof(line), file)) {
            (*line_number)++;

            TokenList t = tokenize_line(line);
            if(t.count == 0) continue;

            if(t.token[0].type == TOK_BREAK) {
                found_break = 1;
                break;
            }

            if(t.token[0].type == TOK_CONTINUE) {
                found_continue = 1;
                break;
            }

            if(t.token[0].type == TOK_WHILE_LOOP) depth++;

            if(t.token[0].type == TOK_END_WHILE) {
                depth--;

                if (depth == 0) {
                    found_end = 1;
                    break;
                }
                continue;
            }

            interpret(t, line, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count);
        }

        if(found_break) {
            if(!found_end) {
                if(skip_until_endwhile(file, line_number) == -1) {
                    error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
                    exit(1);
                }
            }
            return;
        }

        if(found_continue) {
            if(!found_end) {
                if(skip_until_endwhile(file, line_number) == -1) {
                    error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
                }
            } 

            fseek(file, while_pos, SEEK_SET);
            *line_number = while_line;
            continue;
        }

        if(!found_end) {
            error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
            exit(1);
        }

        fseek(file, while_pos, SEEK_SET);
        *line_number = while_line;
    }
}

void handle_comparsion_while(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count) {
    long while_pos = ftell(file);
    int while_line = *line_number;

    while(1) {
        double v1 = 0, v2 = 0;
        int found1 = 0, found2 = 0;

        const char *s1 = NULL;
        const char *s2 = NULL;
        int is_string = 0;

        int value = 0;

        resolve_value(tokens.token[1], &v1, &found1, &s1, &is_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);
        resolve_value(tokens.token[3], &v2, &found2, &s2, &is_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);

        if(is_string) {
            if(s1 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, "\0", '\0'); exit(1); }

            if(s2 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, "\0", '\0'); exit(1); }
        }
        else {
            if(!found1) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, "\0", '\0'); exit(1); }

            if(!found2) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, "\0", '\0'); exit(1); }
        }

        if((s1 != NULL && v2) || (s2 != NULL && v1)) {
            error_ez(E_COMPARE_INVALID_OPERANDS, *line_number, NULL, NULL, '\0'); exit(1);
        }

        if(is_string) value = evalute_comparison_srting(s1, s2, tokens.token[2].type, line_number);
        else value = evaluate_comparison_numeric(v1, v2, tokens.token[2].type, line_number);

        if(tokens.token[4].type != TOK_DO) { error_ez(E_SYNTAX_WHILE_MISSING_DO, *line_number, NULL, NULL, '\0'); exit(1); }

        if(tokens.token[5].type != TOK_END) { error_ez(E_SYNTAX_WHILE_INVALID_STRUCTURE, *line_number, NULL, NULL, '\0'); exit(1); }

        if(!value) {
            if(skip_until_endwhile(file, line_number) == -1) {
                error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
                exit(1);
            }
            return;
        }

        char line[500];
        int depth = 1;
        int found_end = 0;
        int found_break = 0;
        int found_continue = 0;

        while(fgets(line, sizeof(line), file)) {
            (*line_number)++;

            TokenList t = tokenize_line(line);

            if(t.count == 0) continue;

            if(t.token[0].type == TOK_BREAK) {
                found_break = 1;
                break;
            }

            if(t.token[0].type == TOK_CONTINUE) {
                found_continue = 1;
                break;
            }

            if(t.token[0].type == TOK_WHILE_LOOP) depth++;

            if(t.token[0].type == TOK_END_WHILE) {
                depth--;

                if(depth == 0) {
                    found_end = 1;
                    break;
                }
                continue;
            }

            interpret(t, line, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count);
        }

        if(found_break) {
            if(!found_end) {
                if(skip_until_endwhile(file, line_number) == -1) {
                    error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
                    exit(1);
                }
            }

            return;
        }

        if(found_continue) {
            if(!found_end) {
                if(skip_until_endwhile(file, line_number) == -1) {
                    error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
                }
            }

            fseek(file, while_pos, SEEK_SET);
            *line_number = while_line;
            continue;
        }

        if(!found_end) { error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1); }

        fseek(file, while_pos, SEEK_SET);
        *line_number = while_line;
    }
}

void handle_logical_while(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count) {
    long while_pos = ftell(file);
    int while_line = *line_number;

    while(1) {
        double left_v1 = 0, left_v2 = 0;
        int found_left_v1 = 0, found_left_v2 = 0;

        double right_v1 = 0, right_v2 = 0;
        int found_right_v1 = 0, found_right_v2 = 0;

        const char *left_s1 = NULL;
        const char *left_s2 = NULL;
        int is_left_string = 0;

        const char *right_s1 = NULL;
        const char *right_s2 = NULL;
        int is_right_string = 0;

        int value_left = 0, value_right = 0;

        resolve_value(tokens.token[1], &left_v1, &found_left_v1, &left_s1, &is_left_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count,*line_number);
        resolve_value(tokens.token[3], &left_v2, &found_left_v2, &left_s2, &is_left_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);

        if(is_left_string) {
            if(left_s1 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, NULL, '\0'); exit(1); }

            if(left_s2 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, NULL, '\0'); exit(1); }
        }
        else {
            if(!found_left_v1) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[1].text, NULL, '\0'); exit(1); }

            if(!found_left_v2) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[3].text, NULL, '\0'); exit(1); }
        }

        if((left_s1 != NULL && found_left_v2) || (left_s2 != NULL && found_left_v1)) {
            error_ez(E_COMPARE_INVALID_OPERANDS, *line_number, NULL, NULL, '\0'); exit(1);
        }

        if(is_left_string) value_left = evalute_comparison_srting(left_s1, left_s2, tokens.token[2].type, line_number);
        else value_left = evaluate_comparison_numeric(left_v1, left_v2, tokens.token[2].type, line_number);

        resolve_value(tokens.token[5], &right_v1, &found_right_v1, &right_s1, &is_right_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);
        resolve_value(tokens.token[7], &right_v2, &found_right_v2, &right_s2, &is_right_string, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, *line_number);

        if(is_right_string) {
            if(right_s1 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[5].text, NULL, '\0'); exit(1); }

            if(right_s2 == NULL) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[7].text, NULL, '\0'); exit(1); }
        }
        else {
            if(!found_right_v1) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[5].text, NULL, '\0'); exit(1); }

            if(!found_right_v2) { error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, *line_number, tokens.token[7].text, NULL, '\0'); exit(1); }
        }

        if((right_s1 != NULL && found_right_v2) || (right_s2 != NULL && found_right_v1)) {
            error_ez(E_COMPARE_INVALID_OPERANDS, *line_number, NULL, NULL, '\0'); exit(1);
        }

        if(is_right_string) value_right = evalute_comparison_srting(right_s1, right_s2, tokens.token[6].type, line_number);
        else value_right = evaluate_comparison_numeric(right_v1, right_v2, tokens.token[6].type, line_number);

        int result = evalute_logical_op(value_left, value_right, tokens.token[4], line_number);

        if(tokens.token[8].type != TOK_DO) { error_ez(E_SYNTAX_WHILE_MISSING_DO, *line_number, NULL, NULL, '\0'); exit(1); }

        if(tokens.token[9].type != TOK_END) { error_ez(E_SYNTAX_WHILE_INVALID_STRUCTURE, *line_number, NULL, NULL, '\0'); exit(1); }

        if(!result) {
            if(skip_until_endwhile(file, line_number) == -1) {
                error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
                exit(1);
            }
            return;
        }

        char line[500];
        int depth = 1;
        int found_end = 0;
        int found_break = 0;
        int found_continue = 0;

        while(fgets(line, sizeof(line), file)) {
            (*line_number)++;

            TokenList t = tokenize_line(line);

            if(t.count == 0) continue;

            if(t.token[0].type == TOK_BREAK) {
                found_break = 1;
                break;
            }

            if(t.token[0].type == TOK_CONTINUE) {
                found_continue = 1;
                break;
            }
            
            if(t.token[0].type == TOK_WHILE_LOOP) depth++;

            if(t.token[0].type == TOK_END_WHILE) {
                depth--;

                if(depth == 0) {
                    found_end = 1;
                    break;
                }
                continue;
            }

            interpret(t, line, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count);
        }

        if(found_break) {
            if(!found_end) {
                if(skip_until_endwhile(file, line_number) == -1) {
                    error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0');
                    exit(1);
                }
            }

            return;
        }

        if(found_continue) {
            if(!found_end) {
                if(skip_until_endwhile(file, line_number) == -1) {
                    error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
                }
            }

            fseek(file, while_pos, SEEK_SET);
            *line_number = while_line;
            continue;
        }

        if(!found_end) { error_ez(E_SYNTAX_WHILE_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1); }

        fseek(file, while_pos, SEEK_SET);
        *line_number = while_line;
    }
}

int skip_until_endwhile(FILE *file, int *line_number) {
    int depth = 1;
    char line[500];
    long pos;

    while (1) {
        pos = ftell(file);

        if (!fgets(line, sizeof(line), file))
            return -1;

        (*line_number)++;

        TokenList t = tokenize_line(line);
        if (t.count == 0) continue;

        if (t.token[0].type == TOK_WHILE_LOOP)
            depth++;

        if (t.token[0].type == TOK_END_WHILE) {
            depth--;

            if (depth == 0) {
                fseek(file, pos, SEEK_SET);
                (*line_number)--;
                return TOK_END_WHILE;
            }
        }
    }
}


//------------------------------------------ REPEAT STATEMENTS FUNCTIONS ------------------------------------------

void handle_simple_repeat(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count) {
    long repeat_pos = ftell(file);
    int repeat_line = *line_number;
    int found_break = 0;
    
    int value = get_repeat_value(tokens.token[1], num, whole_count, *line_number);

    if(tokens.token[2].type != TOK_TIMES) {
        error_ez(E_SYNTAX_REPEAT_MISSING_TIMES, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(tokens.token[3].type != TOK_END) {
        error_ez(E_SYNTAX_REPEAT_INVALID_STRUCTURE, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(value <= 0) { 
        int mis_end = skip_until_endrepeat(file, line_number);

        if(mis_end == -1) {
            error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
        }
        else if(mis_end == TOK_END_REPEAT) return;
    }

    for(int iteration = 0; iteration < value; iteration++) {

        fseek(file, repeat_pos, SEEK_SET);
        *line_number = repeat_line;

        char line[500];
        int found_end = 0;
        int found_continue = 0;

        while(fgets(line, sizeof(line), file)) {
            (*line_number)++;

            TokenList t = tokenize_line(line);
            if(t.count == 0) continue;

            if(t.token[0].type == TOK_BREAK) {
                found_break = 1;
                break;
            }

            if(t.token[0].type == TOK_CONTINUE) {
                found_continue = 1;
                break;
            }

            if(t.token[0].type == TOK_END_REPEAT) {
                found_end = 1;
                break;
            }

            interpret(t, line, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count);
        }

        if(found_break) break;

        if(found_continue) {
            int mis_end = control_loop(file, line_number, TOK_REPEAT_LOOP);

            if(mis_end == -1) {
                error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
            }
            else if(mis_end == TOK_END_REPEAT)
            continue;
        }

        if(!found_end) { error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1); }
    }

    if(found_break) {
        int mis_end = control_loop(file, line_number, TOK_REPEAT_LOOP);

        if(mis_end == -1) {
            error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
        }
        else if(mis_end == TOK_END_REPEAT) return;
    }
}

void handle_arthmetic_repeat(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count) {
    long repeat_pos = ftell(file);
    int repeat_line = *line_number;
    int found_break = 0;
    
    int v1 = get_repeat_value(tokens.token[1], num, whole_count, *line_number);
    int v2 = get_repeat_value(tokens.token[3], num, whole_count, *line_number);

    int value = 0;

    switch(tokens.token[2].type) {
        case TOK_PLUS : value = v1 + v2; break;
        case TOK_MINUS : value = v1 - v2; break;
        case TOK_STAR : value = v1 * v2; break;
        case TOK_SLASH : value = v1 / v2; break;
        case TOK_MODULO : {
            if (v2 == 0) { error_ez(E_RUNTIME_DIV_BY_ZERO, *line_number, NULL, NULL, '\0'); exit(1); }
            
            value = v1 % v2;
            break;
        }
        default : error_ez(E_SYNTAX_REPEAT_INVALID_EXPRESSION, *line_number, NULL, NULL, '\0'); exit(1);
    }

    if(tokens.token[4].type != TOK_TIMES) { error_ez(E_SYNTAX_REPEAT_MISSING_TIMES, *line_number, NULL, NULL, '\0'); exit(1); }

    if(tokens.token[5].type != TOK_END) { error_ez(E_SYNTAX_REPEAT_INVALID_STRUCTURE, *line_number, NULL, NULL, '\0'); exit(1); }
    
    if(value <= 0) {
        int mis_end = skip_until_endrepeat(file, line_number);

        if(mis_end == -1) {
            error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
        }
        else if(mis_end == TOK_END_REPEAT) return;
    }

    for(int iteration = 0; iteration < value; iteration++) {

        fseek(file, repeat_pos, SEEK_SET);
        *line_number = repeat_line;

        char line[500];
        int found_end = 0;
        int found_continue = 0;

        while(fgets(line, sizeof(line), file)) {
            (*line_number)++;

            TokenList t = tokenize_line(line);
            if(t.count == 0) continue;

            if(t.token[0].type == TOK_BREAK) {
                found_break = 1;
                break;
            }

            if(t.token[0].type == TOK_CONTINUE) {
                found_continue = 1;
                break;
            }

            if(t.token[0].type == TOK_END_REPEAT) {
                found_end = 1;
                break;
            }

            interpret(t, line, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count);
        }

        if(found_break) break;

        if(found_continue) {
            int mis_end = control_loop(file, line_number, TOK_REPEAT_LOOP);

            if(mis_end == -1) {
                error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
            }
            else if(mis_end == TOK_END_REPEAT)
            continue;
        }

        if(!found_end) { error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1); }
    }

    if(found_break) {
        int mis_end = control_loop(file, line_number, TOK_REPEAT_LOOP);

        if(mis_end == -1) {
            error_ez(E_SYNTAX_REPEAT_MISSING_END, *line_number, NULL, NULL, '\0'); exit(1);
        }
        else if(mis_end == TOK_END_REPEAT) return;
    }
}

int skip_until_endrepeat(FILE *file, int *line_number) {
    int depth = 1;
    char line[500];

    while(fgets(line, sizeof(line), file)) {
        (*line_number)++;

        TokenList t = tokenize_line(line);

        if(t.count == 0) continue;;

        if(t.token[0].type == TOK_REPEAT_LOOP) depth++;

        if(t.token[0].type == TOK_END_REPEAT) depth--;

        if(depth == 0) return TOK_END_REPEAT;
    }

    return -1;
}

int get_repeat_value(Token value, whole num[], int *whole_count, int line_number) {
    if(value.type == TOK_NUMBER) return atoi(value.text);
    
    if(value.type == TOK_IDENTIFIER) {
        for(int i = 0; i < *whole_count; i++) {
            if(strcmp(num[i].name, value.text) == 0) {
                return num[i].value;
            }
        }

        error_ez(E_NAME_NOT_DEFINED, line_number, value.text, NULL, '\0'); exit(1);
    }

    error_ez(E_TYPE_REPEAT_NON_NUMERIC, line_number, NULL, NULL, '\0'); exit(1);
}

int control_loop(FILE *file, int *line_number, TokenType loop) {
    char line[500];

    while(fgets(line, sizeof(line), file)) {
        (*line_number)++;

        TokenList t = tokenize_line(line);

        if(t.count == 0) continue;

        if(t.token[0].type == TOK_END_REPEAT && loop == TOK_REPEAT_LOOP) return TOK_END_REPEAT;

        if(t.token[0].type == TOK_END_WHILE && loop == TOK_WHILE_LOOP) return TOK_END_WHILE;
    }

    return -1;
}


//------------------------------------------ VALUES AND EVALUATION FUNCTIONS ------------------------------------------

int resolve_bool_value(Token token, bool truth[], int bool_count, int *line_number) {
    int value = 0;
    int found = 0;

    if(token.type == TOK_NUMBER) {
        value = atof(token.text);

        if(!(value == 0 || value == 1)) {
            error_ez(E_TYPE_INVALID_NUMERIC_BOOL, *line_number, "\0", "\0", '\0');
            exit(1);
        }

        return value;
    }

    if(token.type == TOK_IDENTIFIER) {
        for(int i = 0; i < bool_count; i++) {
            if(strcmp(truth[i].name, token.text) == 0) {
                return truth[i].value;
            }
        }

        error_ez(E_LOGICAL_BOOL_NOT_DECLARED, *line_number, token.text, NULL, '\0'); exit(1);
    }

    error_ez(E_LOGICAL_INVALID_OPERAND, *line_number, NULL, NULL, '\0'); exit(1);
}

int evaluate_comparison_numeric(double v1, double v2, TokenType op, int *line_number) {
    switch(op) {
        case TOK_EQUAL_EQUAL : return (v1 == v2);
        case TOK_NOT_EQUAL : return (v1 != v2);
        case TOK_GREATER : return (v1 > v2);
        case TOK_LESS : return (v1 < v2);
        case TOK_GREATER_EQUAL : return (v1 >= v2);
        case TOK_LESS_EQUAL : return (v1 <= v2);
        default : error_ez(E_COMPARE_INVALID_OPERATION, *line_number, "\0", "\0", '\0'); exit(1);
    }

    return 0;
}

int evalute_comparison_srting(const char *v1, const char *v2, TokenType op, int *line_number) {
    switch(op) {
        case TOK_EQUAL_EQUAL : return (strcmp(v1, v2) == 0);
        case TOK_NOT_EQUAL : return (strcmp(v1, v2) != 0);
        case TOK_GREATER : return (strcmp(v1, v2) > 0);
        case TOK_LESS : return (strcmp(v1, v2) < 0);
        case TOK_GREATER_EQUAL : return (strcmp(v1, v2) >= 0);
        case TOK_LESS_EQUAL : return (strcmp(v1, v2) <= 0);
        default : error_ez(E_COMPARE_INVALID_OPERATION, *line_number, "\0", "\0", '\0'); exit(1);
    }

    return 0;
}

int evalute_logical_op(int left, int right, Token op, int *line_number) {
    switch(op.type) {
        case TOK_AND : return (left && right);
        case TOK_OR : return (left || right);
        default : error_ez(E_LOGICAL_INVALID_OPERATOR, *line_number, op.text, "\0", '\0'); exit(1);
    }

    return 0;
}

void resolve_value(Token token, double *out_num, int *found_num, const char **out_str, int *is_string, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count,int line_number) {

    *out_str = NULL;
    *found_num = 0;
    *is_string = 0;

    if(token.type == TOK_STRING) {
        *out_str = token.text;
        *is_string = 1;
        return;
    }
    else if(token.type == TOK_NUMBER) {
        *out_num = atof(token.text);
        *found_num = 1;
        return;
    }
    else if(token.type == TOK_CHAR) {
        *out_num = (double)token.text[0];
        *found_num = 1;
        return;
    }
    else if(token.type == TOK_TRUE) {
        *out_num = 1.0;
        *found_num = 1;
        return;
    }
    else if(token.type == TOK_FALSE) {
        *out_num = 0.0;
        *found_num = 1;
        return;
    }
    else if(token.type == TOK_IDENTIFIER) {

        for(int i = 0; i < *string_count; i++) {
            if(strcmp(str[i].name, token.text) == 0) {
                *out_str = str[i].value;
                *is_string = 1;
                return;
            }
        }

        for(int i = 0; i < *whole_count; i++) {
            if(strcmp(num[i].name, token.text) == 0) {
                *out_num = num[i].value;
                *found_num = 1;
                return;
            }
        }

        for(int i = 0; i < *real_count; i++) {
            if(strcmp(decimal[i].name, token.text) == 0) {
                *out_num = decimal[i].value;
                *found_num = 1;
                return;
            }
        }

        for(int i = 0; i < *symbol_count; i++) {
            if(strcmp(chara[i].name, token.text) == 0) {
                *out_num = (double)chara[i].value;
                *found_num = 1;
                return;
            }
        }

        for(int i = 0; i < *bool_count; i++) {
            if(strcmp(truth[i].name, token.text) == 0) {
                *out_num = truth[i].value;
                *found_num = 1;
                return;
            }
        }

        error_ez(E_NAME_NOT_DEFINED, line_number, token.text, NULL, '\0'); exit(1);
    }

    error_ez(E_LOGICAL_INVALID_OPERAND, line_number, NULL, NULL, '\0'); exit(1);
}