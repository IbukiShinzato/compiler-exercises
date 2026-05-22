#include "lex.h"

#include <stdio.h>

#include "token.h"

#define true 1
#define false 0
#define TOKENSIZE 1024

#define SCAN_END '\0'

const char white_space[] = {'\t', ' ', SCAN_END};
const char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', SCAN_END};
const char operators[] = {'+', '-', '*', '/', SCAN_END};

#define ERROR_NULL 1
#define ERROR_UNKNOWN 2

static int do_check_simbols(char c, const char* simbol_array)
{
    int i;
    for (i = 0; simbol_array[i] != SCAN_END; i++)
    {
        if (c == simbol_array[i]) return true;
    }

    return false;
}

static int is_white_space(char c) { return do_check_simbols(c, white_space); }

static int is_numbers(char c) { return do_check_simbols(c, numbers); }

static int is_operators(char c) { return do_check_simbols(c, operators); }

static int operator_type(char c)
{
    int ret = 0;

    switch (c)
    {
        case '+':
            ret = OPERATOR_ADD;
            break;
        case '-':
            ret = OPERATOR_SUB;
            break;
        case '*':
            ret = OPERATOR_MUL;
            break;
        case '/':
            ret = OPERATOR_DIV;
            break;
    }

    return ret;
}

int get_token(char* token, char* buf, int* pos)
{
    int i, j, ret;

    i = *pos;
    j = 0;

    if (token == NULL)
    {
        ret = -ERROR_NULL;
        goto out;
    }

    /* skip white spaces */
    while (is_white_space(buf[i]) == true)
    {
        i++;
    }

    if (buf[i] == '\n')
    {
        ret = 0;
        goto out;
    }

    /* get operators */
    if (is_operators(buf[i]) == true)
    {
        token[j++] = buf[i++];
        ret = operator_type(buf[i - 1]);
        goto success;
    }

    /* get numbers */
    while (is_numbers(buf[i]) == true)
    {
        token[j++] = buf[i++];
    }

    /* get unknown simbols */
    if (i == *pos)
    {
        ret = -ERROR_UNKNOWN;
        goto out;
    }

    ret = NUMBER;

success:
    token[j] = '\0';
    *pos = i;
out:
    return ret;
}

int lex_analysis(char* buf)
{
    int i, ret;
    char token[TOKENSIZE];

    i = 0;

    while ((ret = get_token(token, buf, &i)) > 0)
    {
        register_token(token, ret);
    }

    return ret;
}
