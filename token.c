#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "lex.h"
#include "list.h"

LIST_HEAD(token_list_head);

static struct list_head *get_token_list_head()
{
	return &token_list_head;
}

static int token_list_add(token_list *tl)
{
	struct list_head  *tl_head;
	
	tl_head = get_token_list_head();
	list_add_tail(&(tl->list), tl_head);
	return 0;
}



int register_token(char *token, int token_type)
{
	token_list        *tl;
	char              *buf;

	buf = (char*)malloc(strlen(token)+1);
	if (buf == NULL) {
		fprintf(stderr, "fatal error\n");
		return -1;
	}

	strncpy(buf, token, strlen(token));

	tl  = (token_list*)malloc(sizeof(token_list));
	if (tl == NULL) {
		fprintf(stderr, "fatal error\n");
		return -1;
	}

	tl->token = buf;
	tl->type  = token_type;
	return token_list_add(tl);
}

int free_token_list(token_list *target)
{
	free(target->token);
	free(target);

	return 0;
}

int delete_token_all()
{
	token_list       *tl;
	struct list_head *tl_head, *list;

	tl_head = get_token_list_head();
	for (list = tl_head->next; list != tl_head; list = tl_head->next) {
		tl = container_of(list, token_list, list);
		list_del(&(tl->list));
		free_token_list(tl);
	}

	return 0;
}

void show_token_list()
{
	token_list       *tl;
	struct list_head *tl_head, *list;

	tl_head = get_token_list_head();
	for (list = tl_head->next; list != tl_head; list = list->next) {
		tl = container_of(list, token_list, list);
		printf("Token: %s, Type: %d\n", tl->token, tl->type);
	}
	
	return ;
}

token_list *get_next_token()
{
	token_list               *tl;
	static struct list_head  *current_pos = NULL;

	if (current_pos == NULL) {
		current_pos = get_token_list_head();
	} 

	current_pos = current_pos->next;
	if (current_pos == get_token_list_head()) return NULL;

	tl = container_of(current_pos, token_list, list);

	return tl;
}

