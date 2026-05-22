#ifndef __TOKEN_H_
#define __TOKEN_H_

#include "lex.h"
#include "list.h"

enum token_types
{
    NUMBER = 1,
    OPERATOR_ADD,
    OPERATOR_SUB,
    OPERATOR_MUL,
    OPERATOR_DIV,
};

typedef struct token_list
{
    char* token;
    enum token_types type;
    struct list_head list;
} token_list;

int register_token(char* token, int token_type);
int free_token_list(token_list* target);
int delete_token_all();
void show_token_list();
token_list* get_next_token();

#endif /* __TOKEN_H_ */
