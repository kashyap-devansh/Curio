#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assignment.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "error.h"
#include "interpreter.h"

assign_check_list is_literal_assignment(TokenList tokens) {
    
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    if(tokens.token[4].type != TOK_END) {
        return ASSIGN_NOT;
    }

    TokenType t = tokens.token[3].type;

    if(t == TOK_NUMBER || t == TOK_STRING || t == TOK_CHAR || t == TOK_TRUE || t == TOK_FALSE) {
        return ASSIGN_OK;
    }

    return ASSIGN_NOT;
}

assign_check_list is_variable_copy(TokenList tokens) {
    
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    if(tokens.token[4].type != TOK_END) {
        return ASSIGN_NOT;
    }

    TokenType t = tokens.token[3].type;

    if(t == TOK_IDENTIFIER) {
        return ASSIGN_OK;
    }

    return ASSIGN_NOT;
}

assign_check_list is_literal_arithmetic_exp(TokenList tokens) {
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    TokenType left = tokens.token[3].type;
    TokenType op = tokens.token[4].type;
    TokenType right = tokens.token[5].type;

    if( !(op == TOK_PLUS || op == TOK_MINUS || op == TOK_STAR || op == TOK_SLASH || op == TOK_MODULO)) {
        return ASSIGN_NOT;
    }

    if(left != right) {
        return ASSIGN_NOT;
    }

    switch(left) {
        case TOK_NUMBER : return ASSIGN_OK;
        case TOK_STRING : return ASSIGN_OK;
        case TOK_CHAR : return ASSIGN_OK;
        default : return ASSIGN_NOT;
    }

    return ASSIGN_NOT;
}

assign_check_list is_arithmetic_exp_copy(TokenList tokens) {
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    TokenType left = tokens.token[3].type;
    TokenType op = tokens.token[4].type;
    TokenType right = tokens.token[5].type;

    if( !(op == TOK_PLUS || op == TOK_MINUS || op == TOK_STAR || op == TOK_SLASH || op == TOK_MODULO)) {
        return ASSIGN_NOT;
    }

    if(left == TOK_IDENTIFIER && right == TOK_IDENTIFIER) {
        return ASSIGN_OK;
    }

    return ASSIGN_NOT;
}

assign_check_list is_mixed_arthmetic_exp(TokenList tokens) {
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    TokenType left = tokens.token[3].type;
    TokenType op = tokens.token[4].type;
    TokenType right = tokens.token[5].type;

    if( !(op == TOK_PLUS || op == TOK_MINUS || op == TOK_STAR || op == TOK_SLASH || op == TOK_MODULO)) {
        return ASSIGN_NOT;
    }

    int left_ok = (left == TOK_IDENTIFIER || left == TOK_NUMBER || left == TOK_STRING || left == TOK_CHAR);
    int right_ok = (right == TOK_IDENTIFIER || right == TOK_NUMBER || left == TOK_STRING || right == TOK_CHAR);

    if(left_ok && right_ok) {
        return ASSIGN_OK;
    }
    else {
        return ASSIGN_NOT;
    }
}

assign_check_list is_variable_comparison_exp(TokenList tokens) {
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    TokenType left = tokens.token[3].type;
    TokenType op = tokens.token[4].type;
    TokenType right = tokens.token[5].type;

    if( !(op == TOK_EQUAL_EQUAL || op == TOK_NOT_EQUAL || op == TOK_GREATER || op == TOK_LESS || op == TOK_GREATER_EQUAL || op == TOK_LESS_EQUAL)) {
        return ASSIGN_NOT;
    }

    int left_ok = (left == TOK_IDENTIFIER || left == TOK_NUMBER || left == TOK_STRING || left == TOK_CHAR);
    int right_ok = (right == TOK_IDENTIFIER || right == TOK_NUMBER || right == TOK_STRING || right == TOK_CHAR);
    
    if(left_ok && right_ok) {
        return ASSIGN_OK;
    }
    else {
        return ASSIGN_NOT;
    }
}

assign_check_list is_logical_exp(TokenList tokens) {
    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    TokenType left = tokens.token[3].type;
    TokenType op = tokens.token[4].type;
    TokenType right = tokens.token[5].type;

    if( !(op == TOK_AND || op == TOK_OR)) {
        return ASSIGN_NOT;
    }

    int left_ok = (left == TOK_IDENTIFIER || left == TOK_NUMBER || left == TOK_STRING || left == TOK_CHAR);
    int right_ok = (right == TOK_IDENTIFIER || right == TOK_NUMBER || right == TOK_STRING || right == TOK_CHAR);
    
    if(left_ok && right_ok) {
        return ASSIGN_OK;
    }
    else {
        return ASSIGN_NOT;
    }
}

assign_check_list is_not_exp(TokenList tokens) {

    if(tokens.count != 6) {
        return ASSIGN_NOT;
    }

    if(tokens.token[2].type != TOK_EQUAL) {
        return EQUAL_NOT;
    }

    if(tokens.token[5].type != TOK_END) {
        return ASSIGN_NOT;
    }

    TokenType t = tokens.token[3].type;
    TokenType test = tokens.token[4].type;

    if(t != TOK_NOT) {
        return ASSIGN_NOT;
    }

    if(test == TOK_IDENTIFIER || test == TOK_NUMBER || test == TOK_CHAR || test == TOK_STRING) {
        return ASSIGN_OK;
    } 

    return ASSIGN_NOT;
}

void assign_literal(Token varToken, Token valueToken, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {
    
    if(!variable_exists(varToken.text, num, *whole_count, chara, *symbol_count, decimal, *real_count, str, *string_count, truth, *bool_count)) {
        error_ez(E_NAME_NOT_DEFINED, line_number, varToken.text, "\0", '\0');
        exit(1);
    }

    for(int i = 0; i < *whole_count; i++) {
        if(strcmp(num[i].name, varToken.text) == 0) {
            if(valueToken.type == TOK_NUMBER) { num[i].value = atoi(valueToken.text); return; }
            if(valueToken.type == TOK_CHAR) { num[i].value = (int)valueToken.text[0]; return; }

            error_ez(E_TYPE_ASSIGN_WHOLE, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *real_count; i++) {
        if(strcmp(decimal[i].name, varToken.text) == 0) {
            if(valueToken.type == TOK_NUMBER) { decimal[i].value = atof(valueToken.text); return; }
            if(valueToken.type == TOK_CHAR) { decimal[i].value = (double)valueToken.text[0]; return; }

            error_ez(E_TYPE_ASSIGN_REAL, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *symbol_count; i++) {
        if(strcmp(chara[i].name, varToken.text) == 0) {
            if(valueToken.type == TOK_CHAR) { chara[i].value = valueToken.text[0]; return; }
            if(valueToken.type == TOK_NUMBER) { chara[i].value = (char)atoi(valueToken.text); return; }

            error_ez(E_TYPE_ASSIGN_SYMBOL, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *string_count; i++) {
        if(strcmp(str[i].name, varToken.text) == 0) {

            if(valueToken.type == TOK_STRING) {
                strcpy(str[i].value, valueToken.text);
                return;
            }

            error_ez(E_TYPE_ASSIGN_STRING, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *bool_count; i++) {
        if(strcmp(truth[i].name, varToken.text) == 0) {

            if(valueToken.type == TOK_TRUE) {
                truth[i].value = 1;
                return;
            }
            
            if(valueToken.type == TOK_FALSE) {
                truth[i].value = 0;
                return;
            }

            error_ez(E_TYPE_ASSIGN_BOOL, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }
}

void assign_copy(Token varToken, Token valueToken, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {

    if(!variable_exists(varToken.text, num, *whole_count, chara, *symbol_count, decimal, *real_count, str, *string_count, truth, *bool_count)) {
        error_ez(E_NAME_NOT_DEFINED, line_number, varToken.text, "\0", '\0');
        exit(1);
    }

    if(!variable_exists(valueToken.text, num, *whole_count, chara, *symbol_count, decimal, *real_count, str, *string_count, truth, *bool_count)) {
        error_ez(E_NAME_NOT_FOUND_VALUE, line_number, valueToken.text, "\0", '\0');
        exit(1);
    }

    int whole_found = 0, real_found = 0, symbol_found = 0, string_found = 0, bool_found = 0;

    for(int i = 0; i < *whole_count; i++) {
        if(strcmp(num[i].name, varToken.text) == 0) {

            for(int j = 0; j < *whole_count; j++) {
                if(strcmp(num[j].name, valueToken.text) == 0) {
                    num[i].value = num[j].value;
                    return;
                }
            }

            for(int j = 0; j < *real_count; j++) {
                if(strcmp(decimal[j].name, valueToken.text) == 0) {
                    num[i].value = (int)decimal[j].value;
                    return;
                }
            }

            error_ez(E_TYPE_ASSIGN_WHOLE, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *real_count; i++) {
        if(strcmp(decimal[i].name, varToken.text) == 0) {

            for(int j = 0; j < *real_count; j++) {
                if(strcmp(decimal[j].name, valueToken.text) == 0) {
                    decimal[i].value = decimal[j].value;
                    return;
                }
            }

            for(int j = 0; j < *whole_count; j++) {
                if(strcmp(num[j].name, valueToken.text) == 0) {
                    decimal[i].value = (double)num[j].value;
                    return;
                }
            }

            error_ez(E_TYPE_ASSIGN_REAL, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *symbol_count; i++) {
        if(strcmp(chara[i].name, varToken.text) == 0) {
            
            for(int j = 0; j < *symbol_count; j++) {
                if(strcmp(chara[j].name, valueToken.text) == 0) {
                    chara[i].value = chara[j].value;
                    return;
                }
            }

            error_ez(E_TYPE_ASSIGN_SYMBOL, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *string_count; i++) {
        if(strcmp(str[i].name, varToken.text) == 0) {

            for(int j = 0; j < *string_count; j++) {
                if(strcmp(str[j].name, valueToken.text) == 0) {
                    strcpy(str[i].value, str[j].value);
                    return;
                }
            }

            error_ez(E_TYPE_ASSIGN_STRING, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }

    for(int i = 0; i < *bool_count; i++) {
        if(strcmp(truth[i].name, varToken.text) == 0) {

            for(int j = 0; j < *bool_count; j++) {
                if(strcmp(truth[j].name, valueToken.text) == 0) {
                    truth[i].value = truth[j].value;
                    return;
                }
            }

            error_ez(E_TYPE_ASSIGN_BOOL, line_number, valueToken.text, varToken.text, '\0');
            exit(1);
        }
    }
}

void assign_literal_arithemitic_exp(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {

    for(int i = 0; i < *whole_count; i++) {
        if(strcmp(num[i].name, varToken.text) == 0) {
            int v1 = 0, v2 = 0;

            if(left.type == TOK_NUMBER) v1 = atoi(left.text);
            else if(left.type == TOK_CHAR) v1 = (int)left.text[0];

            if(right.type == TOK_NUMBER) v2 = atoi(right.text);
            else if(right.type == TOK_CHAR) v2 = (int)right.text[0];

            switch(op.type) {
                case TOK_PLUS : num[i].value = v1 + v2; return;
                case TOK_MINUS : num[i].value = v1 - v2; return;
                case TOK_STAR : num[i].value = v1 * v2; return;
                case TOK_SLASH : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    num[i].value = v1 / v2;
                    return;
                }
                case TOK_MODULO : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    num[i].value = v1 % v2;
                    return;
                }
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            return;
        }
    }
    for(int i = 0; i < *real_count; i++) {
        if(strcmp(decimal[i].name, varToken.text) == 0) {
            double v1 = 0.0, v2 = 0.0;

            if(left.type == TOK_NUMBER) v1 = atof(left.text);
            else if(left.type == TOK_CHAR) v1 = (double)left.text[0];

            if(right.type == TOK_NUMBER) v2 = atof(right.text);
            else if(right.type == TOK_CHAR) v2 = (double)right.text[0];

            switch(op.type) {
                case TOK_PLUS : decimal[i].value = v1 + v2; return;
                case TOK_MINUS : decimal[i].value = v1 - v2; return;
                case TOK_STAR : decimal[i].value = v1 * v2; return;
                case TOK_SLASH : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    decimal[i].value = v1 / v2;
                    return;
                }
                case TOK_MODULO : error_ez(E_TYPE_REAL_MODULO, line_number, "\0", "\0", '\0'); exit(1);
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            return;
        }
    }
    for(int i = 0; i < *symbol_count; i++) {
        if(strcmp(chara[i].name, varToken.text) == 0) {
            int v1 = 0, v2 = 0;

            if(left.type == TOK_CHAR) v1 = (unsigned char)left.text[0];
            else if(left.type == TOK_NUMBER) v1 = (unsigned char)atoi(left.text);

            if(right.type == TOK_CHAR) v2 = (unsigned char)right.text[0];
            else if(right.type == TOK_NUMBER) v2 = (unsigned char)atoi(right.text);

            unsigned char result;

            switch(op.type) {
                case TOK_PLUS : result = (unsigned char)(v1 + v2); break;
                case TOK_MINUS : result = (unsigned char)(v1 - v2); break;
                case TOK_STAR : result = (unsigned char)(v1 * v2); break;
                case TOK_SLASH : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    result = (unsigned char)(v1 / v2);
                    break;
                }
                case TOK_MODULO : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    } 

                    result = (unsigned char)(v1 % v2);
                    break;
                }
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            chara[i].value = (char)result;

            return;
        }
    }

    for(int i = 0; i < *string_count; i++) {
        if(strcmp(str[i].name, varToken.text) == 0) {
            
            switch(op.type) {
                case TOK_PLUS : {

                    if(strlen(left.text) + strlen(right.text) + 1 > sizeof(str[0].value)) {
                        error_ez(E_RUNTIME_STRING_OVERFLOW, line_number, "\0", "\0", '\0');
                        exit(1);
                    }
                    
                    strcpy(str[i].value, left.text);
                    strcat(str[i].value, right.text);
                    return;
                }
                case TOK_MINUS : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                case TOK_STAR : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                case TOK_SLASH : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                case TOK_MODULO : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            return;
        }
    }
    error_ez(E_TYPE_INVALID_BOOL_OPERATION, line_number, "\0", "\0", '\0');
    exit(1);
}

void assign_variable_arithemitic_exp(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {

    if( is_bool_variable(left.text, truth, *bool_count) || is_bool_variable(right.text, truth, *bool_count)) {
        error_ez(E_TYPE_INVALID_BOOL_OPERATION, line_number, "\0", "\0", '\0');
        exit(1);
    }

    for(int i = 0; i < *whole_count; i++) {
        if(strcmp(num[i].name, varToken.text) == 0) {

            double v1 = 0.0, v2 = 0.0;

            if(left.type == TOK_NUMBER) {
                v1 = atof(left.text);
            }
            else {
                v1 = get_value(left.text, num, *whole_count, decimal, *real_count, truth, *bool_count, line_number);
            }

            if(right.type == TOK_NUMBER) {
                v2 = atof(right.text);
            }
            else {
                v2 = get_value(right.text, num, *whole_count, decimal, *real_count, truth, *bool_count, line_number);
            }

            switch (op.type) {
                case TOK_PLUS : num[i].value = (int)(v1 + v2); break;
                case TOK_MINUS : num[i].value = (int)(v1 - v2); break;
                case TOK_STAR : num[i].value = (int)(v1 * v2); break;
                case TOK_SLASH : {
                    if(v2 == 0.0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    num[i].value = (int)(v1 / v2); 
                    break;}
                case TOK_MODULO : {
                    if(v2 == 0.0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    int a = (int)v1;
                    int b = (int)v2;

                    num[i].value = a % b;
                    break;
                }
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            return;
        }
    }

    for(int i = 0; i < *real_count; i++) {
        if(strcmp(decimal[i].name, varToken.text) == 0) {

            double v1 = 0.0, v2 = 0.0;

            if(left.type == TOK_NUMBER) {
                v1 = atof(left.text);
            }
            else {
                v1 = get_value(left.text, num, *whole_count, decimal, *real_count, truth, *bool_count, line_number);
            }

            if(right.type == TOK_NUMBER) {
                v2 = atof(right.text);
            }
            else {
                v2 = get_value(right.text, num, *whole_count, decimal, *real_count, truth, *bool_count, line_number);
            }

            switch (op.type) {
                case TOK_PLUS : decimal[i].value = v1 + v2; break;
                case TOK_MINUS : decimal[i].value = v1 - v2; break;
                case TOK_STAR : decimal[i].value = v1 * v2; break;
                case TOK_SLASH : {
                    if(v2 == 0.0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    decimal[i].value = v1 / v2; 
                    break;
                }
                case TOK_MODULO : error_ez(E_TYPE_REAL_MODULO, line_number, "\0", "\0", '\0'); exit(1);
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            return;
        }
    }

    for(int i = 0; i < *symbol_count; i++) {
        if(strcmp(chara[i].name, varToken.text) == 0) {
            int v1 = 0, v2 = 0;

            if(left.type == TOK_CHAR) {
                v1 = (unsigned char)left.text[0];
            }
            else {
                v1 = (unsigned char)get_char_value(left, chara, symbol_count, line_number);
            }

            if(right.type == TOK_CHAR) {
                v2 = (unsigned char)right.text[0];
            }
            else {
                v2 = (unsigned char)get_char_value(right, chara, symbol_count, line_number);
            }

            unsigned char result;

            switch(op.type) {
                case TOK_PLUS : result = (unsigned char)(v1 + v2); break;
                case TOK_MINUS : result = (unsigned char)(v1 - v2); break;
                case TOK_STAR : result = (unsigned char)(v1 * v2); break;
                case TOK_SLASH : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    }

                    result = (unsigned char)(v1 / v2);
                    break;
                }
                case TOK_MODULO : {
                    if(v2 == 0) {
                        error_ez(E_RUNTIME_DIV_BY_ZERO, line_number, "\0", "\0", '\0');
                        exit(1);
                    } 

                    result = (unsigned char)(v1 % v2);
                    break;
                }
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            chara[i].value = (char)result;

            return;
        }
    }

    char *v1 = NULL;
    char *v2 = NULL;

    if(left.type == TOK_STRING) {
        v1 = left.text;
    }
    else {
        v1 = get_string_value(left, str, string_count, line_number);
    }

    if(right.type == TOK_STRING) {
        v2 = right.text;
    }
    else {
        v2 = get_string_value(right, str, string_count, line_number);
    }

    if(strlen(v1) + strlen(v2) + 1 > sizeof(str[0].value)) {
        error_ez(E_RUNTIME_STRING_OVERFLOW, line_number, "\0", "\0", '\0');
        exit(1);
    } 
    
    for(int i = 0; i < *string_count; i++) {
        if(strcmp(str[i].name, varToken.text) == 0) {

            switch(op.type) {
                case TOK_PLUS : {
                    strcpy(str[i].value, v1);
                    strcat(str[i].value, v2);
                    return;
                }
                case TOK_MINUS : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                case TOK_STAR : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                case TOK_SLASH : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                case TOK_MODULO : error_ez(E_TYPE_INVALID_STRING_OPERATION, line_number, "\0", "\0", '\0'); exit(1);
                default : {
                    error_ez(E_RUNTIME_UNKNOWN_OPERATOR, line_number, op.text, "\0", '\0');
                    exit(1);
                }
            }

            return;
        }
    }
}

void assign_variable_comparison(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int*symbol_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {

    double v1 = 0.0, v2 = 0.0;
    char *s1 = NULL, *s2 = NULL;

    get_variable_value(left, right, &v1, &v2, &s1, &s2, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, line_number);

    for(int i = 0; i < *bool_count; i++) {
        if(strcmp(truth[i].name, varToken.text) == 0) {

            if(s1 && s2) {
                int cmp = strcmp(s1, s2);

                switch(op.type) {
                    case TOK_EQUAL_EQUAL : truth[i].value = (cmp == 0); return;
                    case TOK_NOT_EQUAL : truth[i].value = (cmp != 0); return;
                    case TOK_GREATER : truth[i].value = (cmp > 0);  return;
                    case TOK_LESS : truth[i].value = (cmp < 0);  return;
                    case TOK_GREATER_EQUAL : truth[i].value = (cmp >= 0); return;
                    case TOK_LESS_EQUAL : truth[i].value = (cmp <= 0); return;
                    default: error_ez(E_COMPARE_INVALID_OPERATION, line_number,op.text, "\0", '\0'); exit(1);
                }
            }

            if(left.type == TOK_NUMBER || left.type == TOK_CHAR || left.type == TOK_IDENTIFIER) {

                switch(op.type) {
                    case TOK_EQUAL_EQUAL : truth[i].value = (v1 == v2); return;
                    case TOK_NOT_EQUAL : truth[i].value = (v1 != v2); return;
                    case TOK_GREATER : truth[i].value = (v1 > v2); return;
                    case TOK_LESS : truth[i].value = (v1 < v2); return;
                    case TOK_GREATER_EQUAL : truth[i].value = (v1 >= v2); return;
                    case TOK_LESS_EQUAL : truth[i].value = (v1 <= v2); return;
                    default : error_ez(E_COMPARE_INVALID_OPERATION, line_number, op.text, "\0", '\0'); exit(1);
                }
            }
        }
    }

    error_ez(E_COMPARE_NON_BOOL_ASSIGN, line_number, "\0", "\0", '\0');
    exit(1);
}

void assign_logical_exp(Token varToken, Token left, Token op, Token right, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int*symbol_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {

    double v1 = 0.0, v2 = 0.0;

    get_variable_value(left, right, &v1, &v2, NULL, NULL, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, line_number);

    for(int i = 0; i < *bool_count; i++) {
        if(strcmp(truth[i].name, varToken.text) == 0) {

            if(left.type == TOK_NUMBER || left.type == TOK_CHAR || left.type == TOK_IDENTIFIER) {
                
                switch(op.type) {
                    case TOK_AND : truth[i].value = (v1 && v2); return;
                    case TOK_OR : truth[i].value = (v1 || v2); return;
                    default : error_ez(E_LOGICAL_INVALID_OPERATOR, line_number, op.text, NULL, '\0'); exit(1);
                }
            }
            else {
                error_ez(E_LOGICAL_INVALID_OPERAND, line_number, NULL, NULL, '\0');
                exit(1);
            }
        }
    }

    error_ez(E_LOGICAL_BOOL_NOT_DECLARED, line_number, varToken.text, NULL, '\0');
    exit(1);
}

void assign_not(Token varToken, Token right, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, bool truth[], int *bool_count, int line_number) {

    double v1 = 0.0;
    Token fake = {0};
    int found = 0;

    get_variable_value(right, fake, &v1, NULL, NULL, NULL, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, line_number);

    for(int i = 0; i < *bool_count; i++) {
        if(strcmp(truth[i].name, varToken.text) == 0) {

            found = 1;

            for(int j = 0; j < *string_count; j++) {
                if(strcmp(str[j].name, right.text) == 0) {
                    truth[i].value = !(strlen(str[j].value) > 0);
                    return;
                }
            }

            if(right.type == TOK_STRING) {
                truth[i].value = !(strlen(right.text) > 0);
                return;
            }

            if(right.type == TOK_NUMBER || right.type == TOK_CHAR || right.type == TOK_IDENTIFIER) {
                truth[i].value = !(v1 != 0);
                return;
            }

            error_ez(E_TYPE_ASSIGN_BOOL, line_number, right.text, varToken.text, '\0');
            exit(1);
            
        }
    }

    if(!found) {
        error_ez(E_NAME_NOT_DEFINED, line_number, varToken.text, NULL, '\0');
        exit(1);
    }
}

void get_variable_value(Token left, Token right, double *v1, double *v2, char **s1, char **s2, whole num[], int *whole_count, real decimal[], int *real_count, symbol chara[], int *symbol_count, string str[], int *string_count, int line_number) {
    TokenType left_type = left.type;
    TokenType right_type = right.type;

    if(left_type == TOK_NUMBER) {
        *v1 = atof(left.text);
        *s1 = NULL;
    }

    if(left_type == TOK_CHAR) {
        *v1 = (double)left.text[0];
        *s1 = NULL;
    }

    if(left_type == TOK_STRING) {
        *s1 = left.text;
    }

    if(left_type == TOK_IDENTIFIER) {
        
        for(int i = 0; i < *whole_count; i++) {
            if(strcmp(num[i].name, left.text) == 0) {
                *v1 = num[i].value;
                *s1 = NULL;
                break;
            }
        }

        for(int i = 0; i < *real_count; i++) {
            if(strcmp(decimal[i].name, left.text) == 0) {
                *v1 = decimal[i].value;
                *s1 = NULL;
                break;
            }
        }

        for(int i = 0; i < *symbol_count; i++) {
            if(strcmp(chara[i].name, left.text) == 0) {
                *v1 = chara[i].value;
                *s1 = NULL;
                break;
            }
        }

        for(int i = 0; i < *string_count; i++) {
            if(strcmp(str[i].name, left.text) == 0) {
                *s1 = str[i].value;
                break;
            }
        }

        // error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, line_number, left.text, "\0", '\0');
        // exit(1);
    }

    if(right_type == TOK_NUMBER) {
        *v2 = atof(right.text);
        *s2 = NULL;
    }

    if(right_type == TOK_CHAR) {
        *v2 = (double)right.text[0];
        *s2 = NULL;
    }

    if(right_type == TOK_STRING) {
        *s2 = right.text;
    }
    
    if(right_type == TOK_IDENTIFIER) {

        for(int i = 0; i < *whole_count; i++) {
            if(strcmp(num[i].name, right.text) == 0) {
                *v2 = num[i].value;
                *s2 = NULL;
                break;
            }
        }

        for(int i = 0; i < *real_count; i++) {
            if(strcmp(decimal[i].name, right.text) == 0) {
                *v2 = decimal[i].value;
                *s2 = NULL;
                break;
            }
        }

        for(int i = 0; i < *symbol_count; i++) {
            if(strcmp(chara[i].name, right.text) == 0) {
                *v2 = chara[i].value;
                *s2 = NULL;
                break;
            }
        }

        for(int i = 0; i < *string_count; i++) {
            if(strcmp(str[i].name, right.text) == 0) {
                *s2 = str[i].value;
                break;
            }
        }

        // error_ez(E_COMPARE_UNDEFINED_IDENTIFIER, line_number, right.text, "\0", '\0');
        // exit(1);
    }
}

int is_bool_variable(char *name, bool truth[], int bool_count) {
    for(int i = 0; i < bool_count; i++) {
        if(strcmp(truth[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}