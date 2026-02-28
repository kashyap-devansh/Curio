#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#define DIVIDER "============================================================"

void error_ez(ErrorCode error_type, int line_number, const char *detail_1, const char *detail_2, char bad_char) {
    
    switch (error_type) {

        //----------------------------------------- FILE Errors -----------------------------------------
        case E_FILE_NO_INPUT : {
            printf("\n" DIVIDER "\nFILE ERROR: No input file provided\nCODE: E-FILE-NO-INPUT\nMESSAGE: No input file provided.\nUsage: %s <file.cuo>.\n" DIVIDER "\n", detail_1);
            exit(1);
            break;
        }

        case E_FILE_WRONG_EXTENSION : {
            printf("\n" DIVIDER "\nFILE ERROR: Wrong file extension\nCODE: E-FILE-WRONG-EXTENSION\nMESSAGE: Input file must have the correct language extension.\nEXAMPLE: program.cur\n" DIVIDER "\n");
            exit(1);
            break;
        }

        case E_FILE_CANNOT_OPEN : {
            printf("\n" DIVIDER "\nFILE ERROR: Cannot open file\nCODE: E-FILE-CANNOT-OPEN\nMESSAGE: Could not open file \"%s\".\n" DIVIDER "\n", detail_1);
            exit(1);
            break;
        }

        //----------------------------------------- Tokenizer Errors -----------------------------------------
        case E_TOKEN_UNKNOWN_CHAR : {
            printf("\n" DIVIDER "\nTOKENIZER ERROR: Unknown character\nCODE: E-TOKEN-UNKNOWN-CHAR\nMESSAGE: Unknown character \"%c\".\nLINE NUMBER: %d\n" DIVIDER "\n", bad_char, line_number);
            exit(1);
            break;
        }
        
        //----------------------------------------- Syntax Errors -----------------------------------------
        case E_SYNTAX_MAKE_INCOMPLETE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Incomplete 'make' statement\nCODE: E-SYNTAX-MAKE-INCOMPLETE\nMESSAGE: Incomplete 'make' statement. Expected: make <type> <name>.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_SYNTAX_UNKNOWN_TYPE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Unknown data type\nCODE: E-SYNTAX-UNKNOWN-TYPE\nMESSAGE: Unknown data type \"%s\". Valid types: whole, real, symbol, string.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_SYNTAX_SET_INCOMPLETE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Incomplete 'set' statement\nCODE: E-SYNTAX-SET-INCOMPLETE\nMESSAGE: Incomplete 'set' statement. Expected: set <name> = <value>.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_SYNTAX_MISSING_EQUAL : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing '=' in assignment\nCODE: E-SYNTAX-MISSING-EQUAL\nMESSAGE: Expected '=' after variable name \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_SYNTAX_TAKE_INCOMPLETE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Incomplete 'take' statement\nCODE: E-SYNTAX-TAKE-INCOMPLETE\nMESSAGE: Incomplete 'take' statement. Expected: take <type> <name>.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_SYNTAX_PRINT_MISSING_ARG : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing argument for print\nCODE: E-SYNTAX-PRINT-MISSING-ARG\nMESSAGE: Missing argument for 'print'. Expected: print \"text\" or print {variable}.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_SYNTAX_COMPLEX_EXPRESSION : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Unsupported complex expression\nCODE: E-SYNTAX-COMPLEX-EXPRESSION\nMESSAGE: Complex expressions are not supported. Only: set <x> = <a> <op> <b>.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_IF_INCOMPLETE : { 
            printf("\n" DIVIDER "\nSYNTAX ERROR: Incomplete 'if' statement\nCODE: E-SYNTAX-IF-INCOMPLETE\nMESSAGE: Incomplete 'if' statement. Condition is missing or malformed.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_IF_INVALID_STRUCTURE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid 'if' statement structure\nCODE: E-SYNTAX-IF-INVALID-STRUCTURE\nMESSAGE: Invalid token count or unsupported 'if' condition format.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_IF_BOOL_INVALID : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid boolean 'if' condition\nCODE: E-SYNTAX-IF-BOOL-INVALID\nMESSAGE: Invalid boolean condition in 'if' statement.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_IF_MISSING_THEN : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing 'then' or 'end'\nCODE: E-SYNTAX-IF-MISSING-THEN-END\nMESSAGE: Expected 'then end' at the end of 'if' condition.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_IF_MISSING_END : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing 'endif'\nCODE: E-SYNTAX-IF-MISSING-END\nMESSAGE: 'if' block was not properly closed with 'endif'.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_WHILE_INCOMPLETE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Incomplete 'while' statement\nCODE: E-SYNTAX-WHILE-INCOMPLETE\nMESSAGE: Incomplete 'while' statement. Condition is missing or malformed.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number); 
            exit(1); 
            break;
        }
        case E_SYNTAX_WHILE_INVALID_STRUCTURE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid 'while' statement structure\nCODE: E-SYNTAX-WHILE-INVALID-STRUCTURE\nMESSAGE: Invalid 'while' statement structure.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_WHILE_INVALID_CONDITION : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid 'while' condition\nCODE: E-SYNTAX-WHILE-INVALID-CONDITION\nMESSAGE: Invalid condition format in 'while' statement.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_WHILE_MISSING_DO : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing 'do' in while statement\nCODE: E-SYNTAX-WHILE-MISSING-DO\nMESSAGE: Expected 'do' at the end of 'while' condition.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_WHILE_INVALID_BOOL_CONDITION : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid boolean condition in while\nCODE: E-SYNTAX-WHILE-INVALID-BOOL-CONDITION\nMESSAGE: Invalid boolean condition in 'while' statement.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_WHILE_MISSING_END : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing 'endwhile'\nCODE: E-SYNTAX-WHILE-MISSING-END\nMESSAGE: 'while' block was not properly closed with 'endwhile'.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_REPEAT_INCOMPLETE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Incomplete 'repeat' statement\nCODE: E-SYNTAX-REPEAT-INCOMPLETE\nMESSAGE: Incomplete 'repeat' statement. Expected a valid repeat count.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_REPEAT_INVALID_STRUCTURE : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid 'repeat' statement structure\nCODE: E-SYNTAX-REPEAT-INVALID-STRUCTURE\nMESSAGE: Invalid token structure for 'repeat' statement.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_SYNTAX_REPEAT_INVALID_EXPRESSION : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Invalid 'repeat' expression\nCODE: E-SYNTAX-REPEAT-INVALID-EXPRESSION\nMESSAGE: Invalid arithmetic expression used as repeat count.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
        }
        case E_SYNTAX_REPEAT_MISSING_TIMES : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing 'times' keyword\nCODE: E-SYNTAX-REPEAT-MISSING-TIMES\nMESSAGE: Expected 'times' keyword after repeat value.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
        }
        case E_SYNTAX_REPEAT_MISSING_END : {
            printf("\n" DIVIDER "\nSYNTAX ERROR: Missing 'endrepeat'\nCODE: E-SYNTAX-REPEAT-MISSING-END\nMESSAGE: 'repeat' block was not properly closed with 'endrepeat'.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
        }

        //----------------------------------------- Name Errors -----------------------------------------
        case E_NAME_ALREADY_EXISTS : {
            printf("\n" DIVIDER "\nNAME ERROR: Variable already exists\nCODE: E-NAME-ALREADY-EXISTS\nMESSAGE: Variable \"%s\" already exists.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_NAME_NOT_DEFINED : {
            printf("\n" DIVIDER "\nNAME ERROR: Variable not defined\nCODE: E-NAME-NOT-DEFINED\nMESSAGE: Variable \"%s\" is not defined.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_NAME_NOT_DEFINED_TAKE : {
            printf("\n" DIVIDER "\nNAME ERROR: Variable not defined in 'take'\nCODE: E-NAME-NOT-DEFINED-TAKE\nMESSAGE: Variable \"%s\" is not defined.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_NAME_NOT_FOUND_PRINT : {
            printf("\n" DIVIDER "\nNAME ERROR: Variable not found in print interpolation\nCODE: E-NAME-NOT-FOUND-PRINT\nMESSAGE: Variable \"%s\" not found during print interpolation.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_NAME_NOT_FOUND_VALUE : {
            printf("\n" DIVIDER "\nNAME ERROR: Variable not found during value lookup\nCODE: E-NAME-NOT-FOUND-VALUE\nMESSAGE: Variable \"%s\" is not defined.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        //----------------------------------------- Type Errors -----------------------------------------
        case E_TYPE_ASSIGN_WHOLE : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid assignment to whole\nCODE: E-TYPE-ASSIGN-WHOLE\nMESSAGE: Cannot assign \"%s\" to whole variable \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, detail_2, line_number);
            exit(1);
            break;
        }

        case E_TYPE_ASSIGN_REAL : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid assignment to real\nCODE: E-TYPE-ASSIGN-REAL\nMESSAGE: Cannot assign \"%s\" to real variable \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, detail_2, line_number);
            exit(1);
            break;
        }

        case E_TYPE_ASSIGN_SYMBOL : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid assignment to symbol\nCODE: E-TYPE-ASSIGN-SYMBOL\nMESSAGE: Cannot assign \"%s\" to symbol variable \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, detail_2, line_number);
            exit(1);
            break;
        }

        case E_TYPE_ASSIGN_STRING : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid assignment to string\nCODE: E-TYPE-ASSIGN-STRING\nMESSAGE: Cannot assign \"%s\" to string variable \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, detail_2, line_number);
            exit(1);
            break;
        }

        case E_TYPE_ASSIGN_BOOL : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid assignment to bool\nCODE: E-TYPE-ASSIGN-BOOL\nMESSAGE: Cannot assign \"%s\" to bool variable \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, detail_2, line_number);
            exit(1);
            break;
        }

        case E_TYPE_INVALID_TAKE : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid type in 'take'\nCODE: E-TYPE-INVALID-TAKE\nMESSAGE: Invalid type for 'take'. Expected: whole, real, symbol, or string.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_TYPE_REAL_MODULO : {
            printf("\n" DIVIDER "\nTYPE ERROR: Illegal modulo on real numbers\nCODE: E-TYPE-REAL-MODULO\nMESSAGE: Operator '%%' is not allowed for real numbers.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_TYPE_INVALID_STRING_OPERATION : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid operation on string\nCODE: E-TYPE-INVALID-STRING-OPERATION\nMESSAGE: Only '+' operation is allowed for string type.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_TYPE_INVALID_BOOL_OPERATION : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid operation on boolean\nCODE: E-TYPE-INVALID-BOOL-OPERATION\nMESSAGE: Arithmetic operations are not allowed on boolean type.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_TYPE_REPEAT_NON_NUMERIC : {
            printf("\n" DIVIDER "\nTYPE ERROR: Non-numeric repeat count\nCODE: E-TYPE-REPEAT-NON-NUMERIC\nMESSAGE: Repeat count must be of type whole or real.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_TYPE_INVALID_NUMERIC_BOOL : {
            printf("\n" DIVIDER "\nTYPE ERROR: Invalid numeric value\nCODE: E-TYPE-INVALID-NUMERIC-BOOL\nMESSAGE: Numeric values used directly in conditions must be 0 or 1.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        //----------------------------------------- Comparison Errors -----------------------------------------
        case E_COMPARE_UNDEFINED_IDENTIFIER : {
            printf("\n" DIVIDER "\nCOMPARE ERROR: Undefined identifier\nCODE: E-COMPARE-UNDEFINED-IDENTIFIER\nMESSAGE: Identifier \"%s\" is not defined.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_COMPARE_TYPE_MISMATCH : {
            printf("\n" DIVIDER "\nCOMPARE ERROR: Invalid comparison\nCODE: E-COMPARE-TYPE-MISMATCH\nMESSAGE: Cannot compare \"%s\" with \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, detail_2, line_number);
            exit(1);
            break;
        }

        case E_COMPARE_INVALID_OPERATION : {
            printf("\n" DIVIDER "\nCOMPARE ERROR: Invalid operator\nCODE: E-COMPARE-INVALID-OPERATOR\nMESSAGE: Operator \"%s\" is not valid for this comparison.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_COMPARE_NON_BOOL_ASSIGN : {
            printf("\n" DIVIDER "\nCOMPARE ERROR: Invalid assignment\nCODE: E-COMPARE-NON-BOOL-ASSIGN\nMESSAGE: Comparison result must be assigned to a bool variable.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }
        case E_COMPARE_INVALID_OPERANDS : {
            printf("\n" DIVIDER "\nCOMPARE ERROR: Invalid comparison operands\nCODE: E-COMPARE-INVALID-OPERANDS\nMESSAGE: Operands used in comparison are not compatible.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
        }

        //----------------------------------------- Logical Errors -----------------------------------------
        case E_LOGICAL_INVALID_OPERATOR : {
            printf("\n" DIVIDER "\nLOGICAL ERROR: Invalid logical operator\nCODE: E-LOGICAL-INVALID-OPERATOR\nMESSAGE: Operator \"%s\" is not valid for logical expressions.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        case E_LOGICAL_INVALID_OPERAND : {
            printf("\n" DIVIDER "\nLOGICAL ERROR: Invalid operand type\nCODE: E-LOGICAL-INVALID-OPERAND\nMESSAGE: Logical operations require number, char, or identifier operands.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_LOGICAL_ASSIGN_TO_NON_BOOL : {
            printf("\n" DIVIDER "\nLOGICAL ERROR: Invalid logical assignment\n: E-LOGICAL-ASSIGN-TO-NON-BOOL\nMESSAGE: Logical expression result must be assigned to a bool variable.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_LOGICAL_BOOL_NOT_DECLARED : {
            printf("\n" DIVIDER "\nLOGICAL ERROR: Bool variable not declared\nCODE: E-LOGICAL-BOOL-NOT-DECLARED\nMESSAGE: Bool variable \"%s\" is not declared.\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }

        //----------------------------------------- Runtime Errors -----------------------------------------
        case E_RUNTIME_DIV_BY_ZERO : {
            printf("\n" DIVIDER "\nRUNTIME ERROR: Division by zero\nCODE: E-RUNTIME-DIV-BY-ZERO\nMESSAGE: Division by zero.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_RUNTIME_STRING_OVERFLOW : {
            printf("\n" DIVIDER "\nRUNTIME ERROR: String overflow\nCODE: E-RUNTIME-STRING-OVERFLOW\nMESSAGE: String operation exceeds maximum allowed length.\nLINE NUMBER: %d\n" DIVIDER "\n", line_number);
            exit(1);
            break;
        }

        case E_RUNTIME_UNKNOWN_OPERATOR : {
            printf("\n" DIVIDER "\nRUNTIME ERROR: Unknown operator\nCODE: E-RUNTIME-UNKNOWN-OPERATOR\nMESSAGE: Unknown operator \"%s\".\nLINE NUMBER: %d\n" DIVIDER "\n", detail_1, line_number);
            exit(1);
            break;
        }
    }
}