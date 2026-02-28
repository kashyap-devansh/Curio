#ifndef ERROR_H
#define ERROR_H

typedef enum {
    //----- File / Input Errors (checked before anything else) -----
    E_FILE_NO_INPUT,
    E_FILE_WRONG_EXTENSION,
    E_FILE_CANNOT_OPEN,

    //----- Tokenizer Errors (next stage after file load) -----
    E_TOKEN_UNKNOWN_CHAR,

    //----- Syntax Errors (token structure problem) -----
    E_SYNTAX_MAKE_INCOMPLETE,
    E_SYNTAX_UNKNOWN_TYPE,
    E_SYNTAX_SET_INCOMPLETE,
    E_SYNTAX_MISSING_EQUAL,
    E_SYNTAX_TAKE_INCOMPLETE,
    E_SYNTAX_PRINT_MISSING_ARG,
    E_SYNTAX_COMPLEX_EXPRESSION,
    E_SYNTAX_IF_INCOMPLETE,
    E_SYNTAX_IF_INVALID_STRUCTURE,
    E_SYNTAX_IF_BOOL_INVALID,
    E_SYNTAX_IF_MISSING_THEN,
    E_SYNTAX_IF_MISSING_END,
    E_SYNTAX_WHILE_INCOMPLETE,
    E_SYNTAX_WHILE_INVALID_STRUCTURE,
    E_SYNTAX_WHILE_INVALID_CONDITION,
    E_SYNTAX_WHILE_MISSING_DO,
    E_SYNTAX_WHILE_INVALID_BOOL_CONDITION,
    E_SYNTAX_WHILE_MISSING_END,
    E_SYNTAX_REPEAT_INCOMPLETE,
    E_SYNTAX_REPEAT_INVALID_STRUCTURE,
    E_SYNTAX_REPEAT_INVALID_EXPRESSION,
    E_SYNTAX_REPEAT_MISSING_TIMES,
    E_SYNTAX_REPEAT_MISSING_END,

    //----- Name Errors (variable existence checks) -----
    E_NAME_ALREADY_EXISTS,
    E_NAME_NOT_DEFINED,
    E_NAME_NOT_DEFINED_TAKE,
    E_NAME_NOT_FOUND_PRINT,
    E_NAME_NOT_FOUND_VALUE,

    //----- Type Errors (assignment, invalid operations) -----
    E_TYPE_ASSIGN_WHOLE,
    E_TYPE_ASSIGN_REAL,
    E_TYPE_ASSIGN_SYMBOL,
    E_TYPE_ASSIGN_STRING,
    E_TYPE_ASSIGN_BOOL,
    E_TYPE_INVALID_TAKE,
    E_TYPE_REAL_MODULO,
    E_TYPE_INVALID_STRING_OPERATION,
    E_TYPE_INVALID_BOOL_OPERATION,
    E_TYPE_REPEAT_NON_NUMERIC,
    E_TYPE_INVALID_NUMERIC_BOOL,

    //----- Comparison Errors -----
    E_COMPARE_UNDEFINED_IDENTIFIER,
    E_COMPARE_TYPE_MISMATCH,
    E_COMPARE_INVALID_OPERATION,
    E_COMPARE_NON_BOOL_ASSIGN,
    E_COMPARE_INVALID_OPERANDS,

    //----- Logical Errors -----
    E_LOGICAL_INVALID_OPERATOR,
    E_LOGICAL_INVALID_OPERAND,
    E_LOGICAL_ASSIGN_TO_NON_BOOL,
    E_LOGICAL_BOOL_NOT_DECLARED,

    //----- Runtime Errors (actual evaluatiion / operations issues) -----
    E_RUNTIME_DIV_BY_ZERO,
    E_RUNTIME_UNKNOWN_OPERATOR,
    E_RUNTIME_STRING_OVERFLOW
}ErrorCode;

void error_ez(ErrorCode error_type, int line_number, const char *detail_1, const char *detail_2, char bad_char);

#endif




/* ============================================================
   FILE ERROR: No input file provided
   CODE: E-FILE-NO-INPUT
   MESSAGE: No input file provided. Usage: run <file.ext>.
   ============================================================ */


/* ============================================================
   FILE ERROR: Wrong file extension
   CODE: E-FILE-WRONG-EXTENSION
   MESSAGE: Input file must have the correct language extension.
   ============================================================ */


/* ============================================================
   FILE ERROR: Cannot open file
   CODE: E-FILE-CANNOT-OPEN
   MESSAGE: Could not open file '%s'.
   ============================================================ */



/* ============================================================
   TOKENIZER ERROR: Unknown character
   CODE: E-TOKEN-UNKNOWN-CHAR
   MESSAGE: Unknown character '%c'.
   ============================================================ */



/* ============================================================
   SYNTAX ERROR: Incomplete 'make' statement
   CODE: E-SYNTAX-MAKE-INCOMPLETE
   MESSAGE: Incomplete 'make' statement. Expected: make <type> <name>.
   ============================================================ */


/* ============================================================
   SYNTAX ERROR: Unknown data type
   CODE: E-SYNTAX-UNKNOWN-TYPE
   MESSAGE: Unknown data type '%s'. Valid types: whole, real, symbol, string.
   ============================================================ */


/* ============================================================
   SYNTAX ERROR: Incomplete 'set' statement
   CODE: E-SYNTAX-SET-INCOMPLETE
   MESSAGE: Incomplete 'set' statement. Expected: set <name> = <value>.
   ============================================================ */


/* ============================================================
   SYNTAX ERROR: Missing '=' in assignment
   CODE: E-SYNTAX-MISSING-EQUAL
   MESSAGE: Expected '=' after variable name '%s'.
   ============================================================ */


/* ============================================================
   SYNTAX ERROR: Incomplete 'take' statement
   CODE: E-SYNTAX-TAKE-INCOMPLETE
   MESSAGE: Incomplete 'take' statement. Expected: take <type> <name>.
   ============================================================ */


/* ============================================================
   SYNTAX ERROR: Missing argument for print
   CODE: E-SYNTAX-PRINT-MISSING-ARG
   MESSAGE: Missing argument for 'print'. Expected: print "text" or print {variable}.
   ============================================================ */


/* ============================================================
   SYNTAX ERROR: Unsupported complex expression
   CODE: E-SYNTAX-COMPLEX-EXPRESSION
   MESSAGE: Complex expressions are not supported. Only: set <x> = <a> <op> <b>.
   ============================================================ */



/* ============================================================
   NAME ERROR: Variable already exists
   CODE: E-NAME-ALREADY-EXISTS
   MESSAGE: Variable '%s' already exists.
   ============================================================ */


/* ============================================================
   NAME ERROR: Variable not defined
   CODE: E-NAME-NOT-DEFINED
   MESSAGE: Variable '%s' is not defined.
   ============================================================ */


/* ============================================================
   NAME ERROR: Variable not defined in 'take'
   CODE: E-NAME-NOT-DEFINED-TAKE
   MESSAGE: Variable '%s' is not defined.
   ============================================================ */


/* ============================================================
   NAME ERROR: Variable not found in print interpolation
   CODE: E-NAME-NOT-FOUND-PRINT
   MESSAGE: Variable '%s' not found during print interpolation.
   ============================================================ */


/* ============================================================
   NAME ERROR: Variable not found during value lookup
   CODE: E-NAME-NOT-FOUND-VALUE
   MESSAGE: Variable '%s' is not defined.
   ============================================================ */



/* ============================================================
   TYPE ERROR: Invalid assignment to whole
   CODE: E-TYPE-ASSIGN-WHOLE
   MESSAGE: Cannot assign '%s' to whole variable '%s'.
   ============================================================ */


/* ============================================================
   TYPE ERROR: Invalid assignment to real
   CODE: E-TYPE-ASSIGN-REAL
   MESSAGE: Cannot assign '%s' to real variable '%s'.
   ============================================================ */


/* ============================================================
   TYPE ERROR: Invalid type in 'take'
   CODE: E-TYPE-INVALID-TAKE
   MESSAGE: Invalid type for 'take'. Expected: whole, real, symbol, or string.
   ============================================================ */


/* ============================================================
   TYPE ERROR: Illegal modulo on real numbers
   CODE: E-TYPE-REAL-MODULO
   MESSAGE: Operator '%' is not allowed for real numbers.
   ============================================================ */



/* ============================================================
   RUNTIME ERROR: Division by zero
   CODE: E-RUNTIME-DIV-BY-ZERO
   MESSAGE: Division by zero.
   ============================================================ */


/* ============================================================
   RUNTIME ERROR: Unknown operator
   CODE: E-RUNTIME-UNKNOWN-OPERATOR
   MESSAGE: Unknown operator '%s'.
   ============================================================ */
