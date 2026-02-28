#ifndef TOKENIZER_H
#define TOKENIZER_H

#define MAX_TOKENS 200

typedef enum {
    //----- Literals & Identifiers -----
    TOK_IDENTIFIER,     // variable names
    TOK_NUMBER,         // 10, 20, -5
    TOK_CHAR,           // 'a'
    TOK_STRING,         // "hello"
    TOK_TRUE,           // true literal
    TOK_FALSE,          // false literal

    //----- Keywords (Reserved Words) -----
    TOK_PRINT,          // print [printf]
    TOK_TAKE,           // take  [scanf]
    TOK_MAKE,           // make  [declare]
    TOK_SET,            // set   [assign]

    //----- Data Types -----
    TOK_WHOLE,          // whole   [int] 
    TOK_REAL,           // real    [float]
    TOK_SYMBOL,         // symbol  [char]
    TOK_STRING_TYPE,    // strings [char str[]]
    TOK_BOOL,           // boolean [true / false]

    //----- Control Flow -----
    TOK_IF,             // if statement
    TOK_THEN,           // then statement
    TOK_ELSE,           // else statement
    TOK_ELSE_IF,        // else if statement
    TOK_END_IF,         // end if statement
    TOK_WHILE_LOOP,     // while statement
    TOK_DO,             // do statement
    TOK_END_WHILE,      // end while statement
    TOK_REPEAT_LOOP,    // repeat statement
    TOK_TIMES,          // times statement
    TOK_END_REPEAT,     // end repear statement
    TOK_BREAK,          // break loop
    TOK_CONTINUE,       // continue loop

    //----- Operators -----
    TOK_EQUAL,          // =
    TOK_EQUAL_EQUAL,    // ==
    TOK_NOT_EQUAL,      // !=
    TOK_GREATER,        // >
    TOK_LESS,           // <
    TOK_GREATER_EQUAL,  // >=
    TOK_LESS_EQUAL,     // <=
    TOK_PLUS,           // +
    TOK_MINUS,          // -
    TOK_STAR,           // *
    TOK_SLASH,          // /
    TOK_MODULO,         // %
    TOK_NOT,            // not
    TOK_AND,            // and 
    TOK_OR,             // or

    //----- Block Symbols ----- 
    TOK_LBRACE,         // {
    TOK_RBRACE,         // }

    //----- End Marker -----
    TOK_END             // end of tokens
} TokenType;

typedef struct {
    TokenType type;
    char text[100];
} Token;

typedef struct {
    Token token[MAX_TOKENS];
    int count;
} TokenList;

typedef struct {
    const char *word;
    TokenType token;
} Keyword;

TokenList tokenize_line(const char *line);

#endif