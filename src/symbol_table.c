#include <string.h>
#include "symbol_table.h"

// CHeck if a variable name already exits in any type list
int variable_exists(char *name, whole num[], int whole_count, symbol chara[], int symbol_count, real decimal[], int real_count, string str[], int string_count, bool truth[], int bool_count) {
    for(int i = 0; i < whole_count; i++) {         // Check for already existed whole [int] variable name
        if(strcmp(num[i].name, name) == 0) {
            return 1;
        }
    }
    
    for(int i = 0; i < symbol_count; i++) {        // Check for already existed symbol [char] variable name
        if(strcmp(chara[i].name, name) == 0) {
            return 1;
        }
    }

    for(int i = 0; i < real_count; i++) {
        if(strcmp(decimal[i].name, name) == 0) {   // Check for already existed real [float] variable name
            return 1;
        }
    }

    for(int i = 0; i < string_count; i++) {        // Check for already existed string [char str[]] variable name   
        if(strcmp(str[i].name, name) == 0) {
            return 1;
        }
    }

    for(int i = 0; i < bool_count; i++) {        // Check for already existed bool [0|1] variable name
        if(strcmp(truth[i].name, name) == 0) {
            return 1;
        }
    }
 
    return 0;
}