#include <stdio.h>
#include <stdlib.h>

#include "token.h"

token_list* current_token;
int is_error;

#define SYNTAX_ERROR 1
#define ZERO_DIVIDE 2

static int exp();
static int exp_tail(int l);
static int term();
static int term_tail(int l);
static int factor();

static int exp()
{
    int l, ret;

    current_token = get_next_token();
    if (current_token == NULL)
    {
#ifdef DEBUG
        printf("syntax error in exp()\n");
#endif
        is_error = SYNTAX_ERROR;
        return 0;
    }

    l = term();
    ret = exp_tail(l);

    return ret;
}

static int exp_tail(int l)
{
    int r = l;

    if (current_token == NULL)
    {
        return r;
    }

    if (current_token->type == OPERATOR_ADD || current_token->type == OPERATOR_SUB)
    {
        int op = current_token->type;
        current_token = get_next_token();
        if (current_token == NULL)
        {
#ifdef DEBUG
            printf("syntax error in exp_tail() \n");
#endif
            is_error = SYNTAX_ERROR;
            return r;
        }

        r = term();

        switch (op)
        {
            case OPERATOR_ADD:
                r = l + r;
                break;
            case OPERATOR_SUB:
                r = l - r;
                break;
            default:
                is_error = SYNTAX_ERROR;
                return r;
        }

        r = exp_tail(r);
    }

    return r;
}

static int term()
{
    int l, ret;
    l = factor();
    ret = term_tail(l);

    return ret;
}

static int term_tail(int l)
{
    int r = l;

    if (current_token == NULL)
    {
        return l;
    }

    if (current_token->type == OPERATOR_MUL)
    {
        current_token = get_next_token();
        if (current_token == NULL)
        {
#ifdef DEBUG
            printf("syntax error in term_tail()\n");
#endif
            is_error = SYNTAX_ERROR;
            return 0;
        }

        r = factor();
        r = l * r;
        r = term_tail(r);
    }

    return r;
}

static int factor()
{
    int ret = 0;

    if (current_token->type == NUMBER)
    {
        ret = atoi(current_token->token);
    }
    else
    {
#ifdef DEBUG
        printf("syntax error in factor()\n");
#endif
        is_error = SYNTAX_ERROR;
    }

    current_token = get_next_token();
    return ret;
}

void syntax_analysis()
{
    int ret;

    ret = exp();
    if (is_error || current_token != NULL)
    {
        switch (is_error)
        {
            case SYNTAX_ERROR:
                fprintf(stderr, "Syntax error\n");
        }

        is_error = 0;
    }
    else
        printf("%d\n", ret);

    delete_token_all();
}
