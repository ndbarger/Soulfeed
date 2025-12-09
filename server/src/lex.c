#include <stdio.h>
#include <stdlib.h>
#include <windef.h>
#include <string.h>

#include "lex.h"

int char_in_str(char c, char* str)
{
    for (int i=0; i<strlen(str); i++)
    {
        if (c == str[i])
            return 1;
    }

    return 0;
}

struct T_Lex* lex_code(char* str)
{
    struct T_Lex *t_, *t;
    int num_tokens = 0;
    int is_lbl = FALSE;
    int lbl_counter = 0;
    int lbl_type = 0;

    char* current_lbl;

    t_ = malloc(strlen(str)*TLEX_SIZE);

    for (int i=0; i<strlen(str); i++)
    {
        printf("%c\n", str[i]);
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            if (lbl_type == 0 && is_lbl) // function
            {
                is_lbl = FALSE; // end label
                char* _ = malloc(num_tokens*TLEX_SIZE+1);
                memcpy(_, current_lbl, lbl_counter);
                lbl_counter = 0;
                t_[num_tokens*TLEX_SIZE] = TLEX_FUNC(_);
                num_tokens++;
                continue;
            } else if (lbl_type == 1 && is_lbl)
            {
                current_lbl[lbl_counter++] = str[i];
                continue;
            }
        } else if (str[i] == ';')
        {
            t_[num_tokens*TLEX_SIZE] = TLEX_SEMICOLON;
            num_tokens++;
            continue;
        } else if (char_in_str(str[i], TLEX_LETTERS))
        {
            if (is_lbl)
            {
                current_lbl[lbl_counter++] = str[i];
                continue;
            } else if (!is_lbl)
            {
                current_lbl = malloc(TLEX_LBLMAX);
                lbl_counter = 0;
                lbl_type == 0;
                is_lbl = TRUE;
                current_lbl[lbl_counter++] = str[i];
                continue;
            }
        }
    }

    t = malloc(num_tokens*TLEX_SIZE);
    memcpy(t, t_, num_tokens*TLEX_SIZE);

    return t;
}