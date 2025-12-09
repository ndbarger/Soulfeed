#ifndef LEX_H
#define LEX_H

/*
lexical analysis
*/

#define TLEX_SIZE sizeof(struct T_Lex)
#define TLEX_LBLMAX 1024

#define TLEX_WHITESPACE (struct T_Lex){ TOKEN_WHITESPACE, " ", "TOKEN_WHITESPACE" }
#define TLEX_SEMICOLON (struct T_Lex){ TOKEN_SEMICOLON, ";", "TOKEN_SEMICOLON" }
#define TLEX_FUNC(s) (struct T_Lex){ TOKEN_FUNC, s, "TOKEN_FUNC" }
#define TLEX_NUMBER(n) (struct T_Lex){ TOKEN_NUMBER, n, "TOKEN_NUMBER" }
#define TLEX_CHAR(c) (struct T_Lex){ TOKEN_CHAR, c, "TOKEN_CHAR" }
#define TLEX_STR(s) (struct T_Lex){ TOKEN_STR, s, "TOKEN_STR" }
#define TLEX_LGATOR (struct T_Lex){ TOKEN_LGATOR, ">", "TOKEN_LGATOR" }
#define TLEX_RGATOR (struct T_Lex){ TOKEN_RGATOR, "<", "TOKEN_RGATOR" }

#define TLEX_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
#define TLEX_NUMBERS "0123456789"

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

struct T_Lex
{
    LexToken token;
    char* value;
    char* repr;
};

struct T_Lex* lex_code(char* str);

#endif