#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokenizer.h"

void add_token(TokenList *list, TokenType type, const char *text) {
    Token *t = &list->token[list->count++];
    t->type = type;
    strcpy(t->text, text);
};

static const Keyword keyword_table[] = {
    {"print", TOK_PRINT},
    {"take", TOK_TAKE},
    {"make", TOK_MAKE},
    {"set", TOK_SET},

    {"whole", TOK_WHOLE},
    {"real", TOK_REAL},
    {"symbol", TOK_SYMBOL},
    {"string", TOK_STRING_TYPE},
    {"bool", TOK_BOOL},

    {"true", TOK_TRUE},
    {"false", TOK_FALSE},

    {"if", TOK_IF},
    {"then", TOK_THEN},
    {"else", TOK_ELSE},
    {"elseif", TOK_ELSE_IF},
    {"endif", TOK_END_IF},

    {"while", TOK_WHILE_LOOP},
    {"do", TOK_DO},
    {"endwhile", TOK_END_WHILE},

    {"repeat", TOK_REPEAT_LOOP},
    {"times", TOK_TIMES},
    {"endrepeat", TOK_END_REPEAT},

    {"break", TOK_BREAK},
    {"continue", TOK_CONTINUE},
};

int is_keyword(const char *word, TokenType *out) {
    int size = sizeof(keyword_table) / sizeof(keyword_table[0]);

    for(int i = 0; i < size; i++) {
        if(strcmp(word, keyword_table[i].word) == 0) {
            *out = keyword_table[i].token;
            return 1;
        }
    }

    return 0;
}

TokenList tokenize_line(const char *line) {
    TokenList list;
    list.count = 0;

    int i = 0;
    int len = strlen(line);

    while(i < len) {
        if(isspace(line[i])) {
            i++;
            continue;
        }
 
        if(line[i] == '\"') {       // Tokenize strings
            i++;
            
            char str[300];
            int j = 0;

            while(line[i] != '\"' && line[i] != '\0') {
                str[j++] = line[i++];
            }
            str[j] = '\0';

            if(line[i] == '\"') {
                i++;
            }

            add_token(&list, TOK_STRING, str);
            continue;
        }

        if(line[i] == '\'') {       // TOkenize char
            i++;

            char ch[2];
            ch[0] = line[i];
            ch[1] = '\0';
            i++;

            if(line[i] == '\'') {
                i++;
            }

            add_token(&list, TOK_CHAR, ch);
            continue;
        }

        if(isdigit(line[i]) || (line[i] == '-' && isdigit(line[i + 1]))) {      // Temp fix for -ve but need to change later
            char num[100];
            int j = 0;

            if(line[i] == '-') {
                num[j++] = line[i++];
            }

            while(isdigit(line[i])) {
                num[j++] = line[i++];
            }

            if(line[i] == '.') {
                num[j++] = line[i++];
                if(!isdigit(line[i])) {
                    i -= 1;
                    num[--j] = '\0';
                    add_token(&list, TOK_NUMBER, num);
                    continue;
                }

                while(isdigit(line[i])) {
                    num[j++] = line[i++];
                }
            }
            num[j] = '\0';

            add_token(&list, TOK_NUMBER, num);
            continue;
        }

        if(isalpha(line[i]) || line[i] == '_') {        // Tokenize Identifier name
            char word[100];
            int j = 0;

            while(isalnum(line[i]) || line[i] == '_') {
                word[j++] = line[i++];
            }
            word[j] = '\0';

            TokenType t;
            if(is_keyword(word, &t)) {
                add_token(&list, t, word);
            }
            else {
                add_token(&list, TOK_IDENTIFIER, word);
            }

            continue;
        }

        if(line[i] == '=' && line[i + 1] == '=') {      // Tokenize ==
            add_token(&list, TOK_EQUAL_EQUAL, "==");
            i += 2;
            continue;
        }

        if(line[i] == '!' && line[i + 1] == '=') {      // Tokenize !=
            add_token(&list, TOK_NOT_EQUAL, "!=");
            i += 2;
            continue;
        }

        if(line[i] == '>' && line[i + 1] == '=') {      // Tokenize >=
            add_token(&list, TOK_GREATER_EQUAL, ">=");
            i += 2;
            continue;
        }

        if(line[i] == '<' && line[i + 1] == '=') {      // Tokenize <=
            add_token(&list, TOK_LESS_EQUAL, "<=");
            i += 2;
            continue;
        }

        if(line[i] == '&' && line[i + 1] == '&') {      // Tokenize &&
            add_token(&list, TOK_AND, "&&");
            i += 2;
            continue;
        }

        if(line[i] == '|' && line[i + 1] == '|') {      // Tokenize ||
            add_token(&list, TOK_OR, "||");
            i += 2;
            continue;
        }

        if(line[i] == '!') {      // Tokenize !
            add_token(&list, TOK_NOT, "!");
            i++;
            continue;
        }

        switch(line[i]) {
            case '=': add_token(&list, TOK_EQUAL, "="); break;
            case '+': add_token(&list, TOK_PLUS, "+"); break;
            case '-': add_token(&list, TOK_MINUS, "-"); break;
            case '*': add_token(&list, TOK_STAR, "*"); break;
            case '/': add_token(&list, TOK_SLASH, "/"); break;
            case '%': add_token(&list, TOK_MODULO, "%"); break;
            case '>': add_token(&list, TOK_GREATER, ">"); break;
            case '<': add_token(&list, TOK_LESS, "<"); break;
            case '{': add_token(&list, TOK_LBRACE, "{"); break;
            case '}': add_token(&list, TOK_RBRACE, "}"); break;
            //default : printf("Unknown character: %c\n", line[i]);
        }
        i++;
    }

    add_token(&list, TOK_END, "");
    return list;
}