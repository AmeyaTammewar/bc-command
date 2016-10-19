#include "g.h"
#include<stdlib.h>
#include<string.h>
void push(stack *s, Integer num) {
	node *tmp;
	tmp = (node*)malloc(sizeof(node));
	tmp->next = NULL;
	tmp->I.arr = (char*)malloc(sizeof(char)*(num.i + 1));
	strcpy(tmp->I.arr, num.arr);
	tmp->I.i = num.i;
	if(s->len == 0) {
		s->head = s->tail = tmp;
		(s->len)++;
		return;
	}
	s->head->next = tmp;
	s->tail = s->head->next;
	s->len++;
}

Integer pop(stack *s) {
	node *tmp, *p;
	int i;
	Integer t;
	initInt(&t);
	t.arr = (char*)malloc(sizeof(char)*(s->tail->I.i + 1));
	strcpy(t.arr, s->tail->I.arr);
	t.i = s->tail->I.i;
	tmp = s->tail;
	p = s->head;
	for(i = 0; i < s->len - 2; i++) 
		p = p->next;
	p->next = NULL;
	free(s->tail->I.arr);
	free(s->tail);
	s->tail = p;
	(s->len)--;
	return t;
}
int empty(stack *s) {
	return s->head == NULL;
}
void full(stack *s) {
	return;
}

void init(stack *s) {
	s->head = s->tail = NULL;
	s->len = 0;
}
