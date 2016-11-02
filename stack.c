/**************************************************************************************************************
 * Copyright (C) 2016 Ameya A. Tammewar (Tammewaraa15.it@coep.ac.in)
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Gneral Publlic License as published by the the 
 * Free Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have recieved a GNU Generl Public License along wih this
 * program; If not, see <https://www.gnu.org/licenses/>.
 *************************************************************************************************************/
#include "g.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
void push(stack *s, Integer *num) {
	node *tmp;
	tmp = (node*)malloc(sizeof(node));
	tmp->next = NULL;
	tmp->I.arr = (char*)malloc(sizeof(char)*MAX);
	strcpy(tmp->I.arr, num->arr);
	tmp->I.i = num->i;
	tmp->I.count = num->count;
	if(s->len == 0) {
		s->head = s->tail = tmp;
		(s->len)++;
		return;
	}
	s->tail->next = tmp;
	s->tail = tmp;
	s->len++;
}
Integer *pop(stack *s) {
	node *tmp, *p;
	int i;
	Integer *t;
	t = (Integer*)malloc(sizeof(Integer));
	initInt(t);
	t->arr = (char*)malloc(sizeof(char)*MAX);
	strcpy(t->arr, s->tail->I.arr);
	t->i = s->tail->I.i;
	t->count = s->tail->I.count;
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
	return (s->head == NULL);
}
void full(stack *s) {
	return;
}
void init(stack *s) {
	s->head = s->tail = NULL;
	s->len = 0;
}
