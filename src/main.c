#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "control_flow.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        error_ez(E_FILE_NO_INPUT, 0, argv[0], "\0", '\0');
        return 1;
    }

    if(!strstr(argv[1], ".cuo")) {
        error_ez(E_FILE_WRONG_EXTENSION, 0, "\0", "\0", '\0');
        exit(1);
    }

    FILE *file = fopen(argv[1], "r"); 

    if(file == NULL) {
        error_ez(E_FILE_CANNOT_OPEN,0, argv[1], "\0", '\0');
        return 1;
    }

    int line_number = 1;

    whole num[100];
    int count_whole = 0;

    symbol chara[100];
    int count_symbol = 0;

    real decimal[100];
    int count_real = 0;

    string str[100];
    int count_string = 0;

    bool truth[100];
    int count_bool = 0;

    char line[500];

    //----------------------------------------------------- Interpreter Loop --------------------------------------------------------    
    while(fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if(strlen(line) == 0) {
            line_number++;
            continue;
        }

        TokenList tokens = tokenize_line(line);

        interpret(tokens, line, file, &line_number, num, &count_whole, chara, &count_symbol, decimal, &count_real, str, &count_string, truth, &count_bool);

        line_number++;
    }
    
    fclose(file);

    return 0;
}