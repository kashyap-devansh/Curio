#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interpreter.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "assignment.h"
#include "error.h"
#include "control_flow.h"

typedef struct Escape {
    char *token;
    char *replace;
    int toklen;
} escape;

escape esc[] = {
    {"<nl>", "\n", 4},
    {"<tab>", "\t", 5},
    {"<qt>", "\"", 4},
    {"<lb>", "{", 4},
    {"<rb>", "}", 4},
    {"<sqt>", "'", 5},
    {"<bs>", "\\", 4}
};

int ESC_COUNT = sizeof(esc) / sizeof(esc[0]);

escape esc_literal[] = {
    {"<nl>", "<nl>", 4},
    {"<tab>", "<tab>", 5},
    {"<qt>", "<qt>", 4},
    {"<lb>", "<lb>", 4},
    {"<rb>", "<rb>", 4},
    {"<sqt>", "<sqt>", 5},
    {"<bs>", "<bs>", 4}
};

int ESC_LITERAL_COUNT = sizeof(esc_literal) / sizeof(esc_literal[0]);

char *operators[] = {"+", "-", "*", "/", "%", "="}; 

//------------------------------------------ CORE STATEMENTS FUNCTIONS ------------------------------------------

// Function to Dispatch execution based on the first token
void interpret(TokenList tokens, const char *line, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {
    TokenType first = tokens.token[0].type;

    switch(tokens.token[0].type) {
        case TOK_MAKE : make_ez(tokens, *line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
        case TOK_SET : set_ez(tokens, *line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
        case TOK_TAKE : take_ez(tokens, *line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
        case TOK_PRINT : print_ez(tokens, *line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
        case TOK_IF : if_ez(tokens, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
        case TOK_ELSE : skip_until_endif(file, line_number); return;
        case TOK_WHILE_LOOP : while_ez(tokens, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
        case TOK_REPEAT_LOOP : repeat_ez(tokens, file, line_number, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count); return;
    }
}

// Function to Make [declare] the variables
void make_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {

    if(tokens.count < 3) {
        error_ez(E_SYNTAX_MAKE_INCOMPLETE, line_number, "\0", "\0", '\0');
        exit(1);
    }

    Token data_type = tokens.token[1];
    Token name = tokens.token[2];

    if(variable_exists(name.text, num, *whole_count, chara, *symbol_count, decimal, *real_count, str, *string_count, truth, *bool_count)) {
        error_ez(E_NAME_ALREADY_EXISTS, line_number, name.text, "\0", '\0');
        exit(1);
    }


    // Declare the variable for type whole [int]
    if(data_type.type == TOK_WHOLE) {
        strcpy(num[*whole_count].name, name.text);
        num[*whole_count].value = 0;
        (*whole_count)++;
    }
    // Declare the variable for type real [double]
    else if(data_type.type == TOK_REAL) {
        strcpy(decimal[*real_count].name, name.text);
        decimal[*real_count].value = 0.0;
        (*real_count)++;
    }
    // Declare the variable for type symbol [char]
    else if(data_type.type == TOK_SYMBOL) {
        strcpy(chara[*symbol_count].name, name.text);
        chara[*symbol_count].value = '\0';
        (*symbol_count)++;
    }
    // Declare the variable for type string [char str[]]
    else if(data_type.type == TOK_STRING_TYPE) {
        strcpy(str[*string_count].name, name.text);
        str[*string_count].value[0] = '\0';
        (*string_count)++;
    } 
    // Declare the variable for type for bool [1|0]
    else if(data_type.type == TOK_BOOL) {
        strcpy(truth[*bool_count].name, name.text);
        truth[*bool_count].value = 0;
        (*bool_count)++;
    }   
    else {
        error_ez(E_SYNTAX_UNKNOWN_TYPE, line_number, data_type.text, "\0", '\0');
        exit(1);
    }
}

// Function to Set [assign] the value for variables
void set_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {

    if (tokens.token[2].type != TOK_EQUAL) {
        error_ez(E_SYNTAX_MISSING_EQUAL, line_number, tokens.token[1].text, "\0", '\0');
        exit(1);
    }

    if(tokens.count < 5) {
        error_ez(E_SYNTAX_SET_INCOMPLETE, line_number, "\0", "\0", '\0');
        exit(1);
    }
    
    if(is_variable_copy(tokens) == ASSIGN_OK) {
        assign_copy(tokens.token[1], tokens.token[3], num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count, line_number);
        return;
    }
    
    if(is_literal_assignment(tokens) == ASSIGN_OK) {
        assign_literal(tokens.token[1], tokens.token[3], num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count, line_number);
        return;
    }

    if(tokens.count == 6 && tokens.token[5].type == TOK_END) {
        if(is_not_exp(tokens) == ASSIGN_OK) {
            assign_not(tokens.token[1], tokens.token[4], num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, line_number);
            return;
        }
    }

    if(tokens.count == 7 && tokens.token[6].type == TOK_END) {

        if(is_arithmetic_exp_copy(tokens) == ASSIGN_OK) {
            assign_variable_arithemitic_exp(tokens.token[1], tokens.token[3], tokens.token[4], tokens.token[5], num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count, line_number);
            return;
        }

        if(is_literal_arithmetic_exp(tokens) == ASSIGN_OK) {
            assign_literal_arithemitic_exp(tokens.token[1], tokens.token[3], tokens.token[4], tokens.token[5], num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count, line_number);
            return;
        }

        if(is_mixed_arthmetic_exp(tokens) == ASSIGN_OK) {
            assign_variable_arithemitic_exp(tokens.token[1], tokens.token[3], tokens.token[4], tokens.token[5], num, whole_count, chara, symbol_count, decimal, real_count, str, string_count, truth, bool_count, line_number);
            return;
        }

        if(is_variable_comparison_exp(tokens) == ASSIGN_OK) {
            assign_variable_comparison(tokens.token[1], tokens.token[3], tokens.token[4], tokens.token[5], num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, line_number);
            return;
        }

        if(is_logical_exp(tokens) == ASSIGN_OK) {
            assign_logical_exp(tokens.token[1], tokens.token[3], tokens.token[4], tokens.token[5], num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count, line_number);
            return;
        }
    }

    error_ez(E_SYNTAX_COMPLEX_EXPRESSION, line_number, "\0", "\0", '\0');
    exit(1);
} 

// Functions to Take [Input] from the user [scanf -----> take]
void take_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {

    if(tokens.count < 3) {
        error_ez(E_SYNTAX_TAKE_INCOMPLETE, line_number, "\0", "\0", '\0');
        exit(1);
    }

    Token data_type = tokens.token[1];
    Token name = tokens.token[2];

    if(!variable_exists(name.text, num, *whole_count, chara, *symbol_count, decimal, *real_count, str, *string_count, truth, *bool_count)) {
        error_ez(E_NAME_NOT_DEFINED_TAKE, line_number, "\0", "\0", '\0');
        exit(1);
    }

    
    // Store the variable for type whole [int]
    if(data_type.type == TOK_WHOLE) {
        for(int i = 0; i < *whole_count; i++) {
            if(strcmp(num[i].name, name.text) == 0) {
                scanf("%d", &num[i].value);
                return;
            }
        }
    }
    // Store the variable for type symbol [char]
    if(data_type.type == TOK_SYMBOL) {
        for(int i = 0; i < *symbol_count; i++) {
            if(strcmp(chara[i].name, name.text) == 0) {
                scanf(" %c", &chara[i].value);
                return;
            }
        }
    }
    // Store the variable for type real [double]
    if(data_type.type == TOK_REAL) {
        for(int i = 0; i < *real_count; i++) {
            if(strcmp(decimal[i].name, name.text) == 0) {
                scanf("%lf", &decimal[i].value);
                return;
            }
        }
    }
    // Store the variable for type string [char str[]]
    if(data_type.type == TOK_STRING_TYPE) {
        int c = getchar();
        if(c != '\n' && c != EOF) {
            ungetc(c, stdin);
        }

        for(int i = 0; i < *string_count; i++) {
            if(strcmp(str[i].name, name.text) == 0) {
                fgets(str[i].value, 400, stdin);
                str[i].value[strcspn(str[i].value, "\n")] = '\0';
                return;
            }
        }
    }
    // Store the variable for type bool [0|1]
    if(data_type.type == TOK_BOOL) {
        for(int i = 0; i < *bool_count; i++) {
            if(strcmp(truth[i].name, name.text) == 0) {
                scanf("%d", &truth[i].value);
                return;
            }
        }
    }

    error_ez(E_TYPE_INVALID_TAKE, line_number ,"\0", "\0", '\0');
}

// Function to Print [printf -----> print]
void print_ez(TokenList tokens, int line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {
    if(tokens.count < 2) {
        error_ez(E_SYNTAX_PRINT_MISSING_ARG, line_number, "\0", "\0", '\0');
        exit(1);
    }

    Token text_token = tokens.token[1];

    char text[500];
    strcpy(text, text_token.text);


    int i = 0;

    // Parse and print text, replacing {var} with values
    while(text[i] != '\0') {

        if(text[i] == '\\') {
            i++;

            int matched = 0;
            for(int e = 0; e < ESC_LITERAL_COUNT; e++) {
                if(strncmp(&text[i], esc_literal[e].token, esc_literal[e].toklen) == 0) {
                    printf("%s", esc_literal[e].replace);
                    i += esc_literal[e].toklen;
                    matched = 1;
                    break;
                }
            }

            if(matched) {
                continue;
            }

            printf("\\%c", text[i]);
            i++;
            continue;
        }

        if(text[i] == '<') {
            int matched = 0;
            for(int e = 0; e < ESC_COUNT; e++) {
                if(strncmp(&text[i], esc[e].token, esc[e].toklen) == 0) {
                    printf("%s", esc[e].replace);
                    i += esc[e].toklen;
                    matched = 1;
                    break;
                }
            }

            if(matched) {
                continue;
            }
        }

        //----- Extract variable name -----
        if(text[i] == '{') {
            i++;

            char var_name[100];
            int j = 0;

            while(text[i] != '}' && text[i] != '\0') {
                var_name[j++] = text[i++];
            }
            var_name[j] = '\0';

            if(text[i] == '}') {
                i++;
            }

            int found = 0;

            for(int k = 0; k < *whole_count; k++) {       // Print the value of the whole [int] variable
                if(strcmp(num[k].name, var_name) == 0) {
                    printf("%d", num[k].value);
                    found = 1;
                    break;
                }
            }

            for(int k = 0; k < *symbol_count; k++) {      // Print the value of the whole [char] variable
                if(strcmp(chara[k].name, var_name) == 0) {
                    printf("%c", chara[k].value);
                    found = 1;
                    break;
                }
            }

            for(int k = 0; k < *real_count; k++) {        // Print the value of real [float] variable
                if(strcmp(decimal[k].name, var_name) == 0)  {
                    printf("%g", decimal[k].value);
                    found = 1;
                    break;
                }
            }

            for(int k = 0; k < *string_count; k++) {      // Print the value of string [char str[]] variable  
                if(strcmp(str[k].name, var_name) == 0) {
                    printf("%s", str[k].value);
                    found = 1;
                    break;
                }
            }

            for(int k = 0; k < *bool_count; k++) {      // Print the value of bool [True | False] variable       
                if(strcmp(truth[k].name, var_name) == 0) {
                    printf("%s", truth[k].value ? "true" : "false");
                    found = 1;
                    break;
                }
            }

            if(!found) {
                error_ez(E_NAME_NOT_FOUND_PRINT, line_number, var_name, "\0", '\0');
                exit(1);
            }

            continue;
        }

        printf("%c", text[i]);
        i++;
    }   
}


//------------------------------------------ CONTROL FLOW FUNCTIONS ------------------------------------------

// Function to Dispatch different If statements
void if_ez(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {
    if(tokens.count < 3) {
       error_ez(E_SYNTAX_IF_INCOMPLETE, *line_number, NULL, NULL, '\0');
        exit(1);
    }

    if(tokens.count == 4) {
        handle_bool_if(tokens, file, line_number, truth, bool_count);
    }
    else if(tokens.count == 6) {

        if(tokens.token[2].type == TOK_AND || tokens.token[2].type == TOK_OR) {
            handle_bool_if(tokens, file, line_number, truth, bool_count);
        }
        else handle_comparison_if(tokens, file, line_number, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count);
    }
    else if(tokens.count == 10) {
        handle_logical_if(tokens, file, line_number, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count);
    }
    else {
        error_ez(E_SYNTAX_IF_INVALID_STRUCTURE, *line_number, "\0", "\0", '\0');
        exit(1);
    }
}

// Function to Dispatch different While statements
void while_ez(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {
    if(tokens.count < 3) { error_ez(E_SYNTAX_WHILE_INCOMPLETE, *line_number, NULL, NULL, '\0'); exit(1); }

    if(tokens.count == 4) { handle_bool_while(tokens, file, line_number, truth, bool_count, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count); }
    else if(tokens.count == 6) {
        int comparison_op = (tokens.token[2].type == TOK_EQUAL_EQUAL || tokens.token[2].type == TOK_NOT_EQUAL || tokens.token[2].type == TOK_GREATER || tokens.token[2].type == TOK_LESS || tokens.token[2].type == TOK_GREATER_EQUAL || tokens.token[2].type == TOK_LESS_EQUAL);

        if(tokens.token[2].type == TOK_AND || tokens.token[2].type == TOK_OR) {
            handle_bool_while(tokens, file, line_number, truth, bool_count, num, whole_count, chara, symbol_count, decimal, real_count, str, string_count);
        }
        else if(comparison_op) {
            handle_comparsion_while(tokens, file, line_number, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count);
        }
        else { error_ez(E_SYNTAX_WHILE_INVALID_CONDITION, *line_number, NULL, NULL, '\0'); exit(1); }
    }
    else if(tokens.count == 10) {handle_logical_while(tokens, file, line_number, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count); }
    else { error_ez(E_SYNTAX_WHILE_INVALID_STRUCTURE, *line_number, "\0", "\0", '\0'); exit(1); }
}

// Function to Dispatch different Repeat statements
void repeat_ez(TokenList tokens, FILE *file, int *line_number, whole num[], int *whole_count, symbol chara[], int *symbol_count, real decimal[], int *real_count, string str[], int *string_count, bool truth[], int *bool_count) {
    if(tokens.count < 3) { error_ez(E_SYNTAX_REPEAT_INCOMPLETE, *line_number, NULL, NULL, '\0'); exit(1); }

    if(tokens.count == 4) { handle_simple_repeat(tokens, file, line_number, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count); }
    else if(tokens.count == 6) {
        int arthmetic_op = (tokens.token[2].type == TOK_PLUS || tokens.token[2].type == TOK_MINUS || tokens.token[2].type == TOK_STAR || tokens.token[2].type == TOK_SLASH || tokens.token[2].type == TOK_MODULO);

        if(!arthmetic_op) { error_ez(E_SYNTAX_REPEAT_INVALID_EXPRESSION, *line_number, NULL, NULL, '\0'); exit(1); }
        handle_arthmetic_repeat(tokens, file, line_number, num, whole_count, decimal, real_count, chara, symbol_count, str, string_count, truth, bool_count);
    }
    else { error_ez(E_SYNTAX_REPEAT_INVALID_STRUCTURE, *line_number, "\0", "\0", '\0'); exit(1); }
}


//------------------------------------------ HELPER FUNCTIONS ------------------------------------------

double get_value(char *token, whole num[], int whole_count, real decimal[], int real_count, bool truth[], int bool_count, int line_number) {

    for(int i = 0; i < whole_count; i++) {
        if(strcmp(num[i].name, token) == 0) {
            return (double)num[i].value;
        }
    }

    for(int i = 0; i < real_count; i++) {
        if(strcmp(decimal[i].name, token) == 0) {
            return decimal[i].value;
        }
    }

    for(int i = 0; i < bool_count; i++) {
        if(strcmp(truth[i].name, token) == 0) {
            error_ez(E_TYPE_INVALID_BOOL_OPERATION, line_number, "\0", "\0", '\0');
            exit(1);
        }
    }

    error_ez(E_NAME_NOT_FOUND_VALUE, line_number, token, "\0", '\0');
    exit(1);
}

char get_char_value(Token character, symbol chara[], int *symbol_count, int line_number) {
    for(int i = 0; i < *symbol_count; i++) {
        if(strcmp(chara[i].name, character.text) == 0) {
            return chara[i].value;
        }
    }

    error_ez(E_NAME_NOT_DEFINED, line_number, character.text, "\0", '\0');
    exit(1);
}

char *get_string_value(Token value, string str[], int *string_count, int line_number) {
    for(int i = 0; i < *string_count; i++) {
        if(strcmp(str[i].name, value.text) == 0) {
            return str[i].value;
        }
    }

    error_ez(E_NAME_NOT_DEFINED, line_number, value.text, "\0", '\0');
    exit(1);
}
