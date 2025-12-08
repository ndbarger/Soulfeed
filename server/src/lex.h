#ifndef LEX_H
#define LEX_H

/*
lexical analysis
*/

typedef enum
{
    TOKEN_WHITESPACE,   // ignore
    TOKEN_SEMICOLON,    // end statement
    TOKEN_FUNC,         // function
    TOKEN_NUMBER,       // number
    TOKEN_CHAR,         // letter or (character) number
    TOKEN_STR,          // string of characters
    TOKEN_LGATOR,       // <
    TOKEN_RGATOR,       // >
} LexToken;

typedef struct
{
    LexToken token;
    char* value;
} T_Lex;

T_Lex lex_string(char* str);

#endif