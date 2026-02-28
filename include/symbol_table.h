#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

//---------------------------------------------- DATA TYPES ---------------------------------

typedef struct number{
    char name[100];
    int value;
} whole;  // for integers

typedef struct symbol{
    char name[100];
    char value;
} symbol;  // for characters

typedef struct real{
    char name[100];
    double value;
} real;  // for float

typedef struct string {
    char name[100];
    char value[400];
} string;  // for strings

typedef struct boolean {
    char name[100];
    short int value;
} boolVar;  // for boolean

#define bool boolVar

int variable_exists(char *name, whole num[], int whole_count, symbol chara[], int symbol_count, real decimal[], int real_count, string str[], int string_count, bool truth[], int bool_count);  // Function to check if the variable name already exists or not

#endif