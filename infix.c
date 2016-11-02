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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g.h"
extern int State;
extern datanode T;
int precedence(char op) {
	if(op == '(')
		return 11;
	if(op == '^') 
		return 10;
	if(op == '%')
		return 9;
	if(op == '*' || op == '/')
		return 8;
	if(op == '+' || op == '-')
		return 7;
	if(op == '>' || op == '<')
		return 6;
	if(op == '=' || op == '!')
		return 5;
	if(op == '&')
		return 4;
	if(op == '|')
		return 3;
	if(op == ')')
		return 2;
	return 1;
}
char ctop(cstack *cs) {
	char x = cpop(cs);
	cpush(cs, x);
	return x;
}
Integer *infix(char *str) {
	stack s;
	cstack cs;
	token *t;
	Integer *x, *y, *result;
	int p;
	long int z;
	int reset = 1, a, b, Variable = 0, i;
	char opr;
	cinit(&cs);
	init(&s);
	
	while(1) {
		t = getnext (str, &reset);
		if(t->type == OPERAND) {
			push(&s, &t->number);			
			free(t->number.arr);
		}
		
		else if (t->type == OPERATOR) {
			if(!cempty(&cs)) {
				p = ctop(&cs);
				a = precedence(p);	
				b = precedence(t->op);	
				while((a >= b) && (p != '(')) {
					opr = cpop(&cs);
					x = pop(&s);
					y = pop(&s);
					integer(x);
					integer(y);
					switch(opr) {
						case '+':
							result = AddIntegers(y, x);
							break;
						case '-':
							result = SubtractIntegers(y, x);
							break;
						case '*':
							result = multiply(y, x);
							break;
						case '^':
							intstring(x);
							z = Atoi(x);
							result = power(y, z);
							break;
						case '/':
							intstring(x);
							z = Atoi(x); 
							result = divide(y, z);
							break;
						case '%':
							State = 5;
							intstring(x);
							z = Atoi(x); 
							result = divide(y, z);
							break;
						case '<':case '>':case '=':case '!':case '&':case '|':
							result = Compare(y, x, opr);
							break;
				
					}
					intstring(result);
					push(&s, result);
					if(!cempty(&cs)) {
						p = ctop(&cs);	
						a = precedence(p);
						if(p == '(')
							p = cpop(&cs);
					}
					else
						break;
				}
			}
			if(t->op != ')')
				cpush(&cs, t->op);
		} 
		else if(t->type == VARIABLE) {
			if(State == 7) {
				for(i = 0; i < T.i; i++) {
					if(strcmp(T.d[i].arr, t->number.arr) == 0)
						break;
				}
				x = (Integer *)malloc(sizeof(Integer));
				initInt(x);
				x->arr = (char *)malloc(sizeof(char)*MAX);
				strcpy(x->arr, T.d[i].value.arr);
				T.d[i].value.i = x->i;
				T.d[i].value.count = x->count;
				State = 0;
				return(x);
			}
			else		
				strcpy(T.d[T.i].arr, t->number.arr);
		}
		else if(t->type == LENGTH) {
			State = 3;
		}
		else if(t->type == SCALE) {
			State = 4;
		}
		else if(t->type == PRINT) {
			State = 7;
		}
		else if(t->type == END) {
			while(!cempty(&cs)) {
				opr = cpop(&cs);
				
				if(s.len != 0) {
 					x = pop(&s);
					integer(x);
				}
				if(s.len != 0) { 	
					y = pop(&s);
					integer(y);
				}
				else {
					if(State == 3 || State == 4) { 
						y = length(x);
						intstring(y);
						return y;
					}
					if(State == 6) {
						intstring(x);
						T.d[T.i].value.arr = (char *)malloc(sizeof(char)*MAX);
						strcpy(T.d[T.i].value.arr, x->arr);
						T.i++;
						return x;
					}  
				}	
				switch(opr) {
					case '+':
						result = AddIntegers(y, x);
						break;
					case '-':
						result = SubtractIntegers(y, x);
						break;
					case '*':
						result = multiply(y, x);
						break;
					case '^':
						intstring(x);
						z = Atoi(x);
						result = power(y, z);
						break; 
					case '/':
						intstring(x);
						z = Atoi(x);
						result = divide(y, z);
						break;
					case '%':
						State = 5;
						intstring(x);
						z = Atoi(x);
						result = divide(y, z);
						break;
					case '<':case '>':case '=':case '!':case '&':case '|':
						result = Compare(y, x, opr);
						break;
				
				}
				intstring(result);
				push(&s, result);
			}
			
			if(State == 3 || State == 4) {
				integer(result);
				result = length(result);
				intstring(result);
			}
			if(State == 6) {
				result = pop(&s);
				T.d[T.i].value.arr = (char *)malloc(sizeof(char)*MAX);
				strcpy(T.d[T.i].value.arr, result->arr);
				T.i++;
			}  
			free(x);
			free(y);
			free(t);
			return result;
		} 
		else if(t->type == ERROR) {
			State = 8;
			x = (Integer *)malloc(sizeof(Integer));
			initInt(x);
			return x;
		}	
		
	}
}
