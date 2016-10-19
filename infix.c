#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g.h"

int precedence(char op) {
	if(op == '(')
		return 5;
	if(op == '%')
		return 4;
	if(op == '*' || op == '/')
		return 3;
	if(op == '+' || op == '-')
		return 2;
	if(op == ')')
		return 1;
	return 0;
}
char ctop(cstack *cs) {
	char x = cpop(cs);
	cpush(cs, x);
	return x;
}
Integer infix(char *str) {
	stack s;
	cstack cs;
	token *t;
	Integer x, y, z, result;
	int p;
	int reset = 1, a, b;
	char opr;
	initInt(&x);
	initInt(&y);
	initInt(&z);
	initInt(&result);
	cinit(&cs);
	init(&s);
	while(1) {
		t = getnext (str, &reset);
		if(t->type == OPERAND) {
			push(&s, t->number);			
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
					integer(&x);
					integer(&y);
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
						/*case '/':
							result = y / x;
							break;
						case '%':
							result = y % x;
							break;*/
				
					}
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
		else if(t->type == ASSIGOPR) {
			cpush(&cs, t->op);
		}
		/*else if(t->type == VARIABLE) {
			z = t->a;
		}*/ 
		else if (t->type == END) {
			while(!cempty(&cs)) {
				opr = cpop(&cs);
				if(!empty(&s)) 	
					x = pop(&s);
				if(!empty(&s)) 	
					y = pop(&s);
					integer(&x);
					integer(&y);
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
					/*case '/':
						result = divide(y, x);
						break;
					case '%':
						result = y % x;
						break;
					case '=':
						z = x;
						return z;*/
				
				}
				push(&s, result);
			}
			return result;
		} //else
			//return INT_MIN;
	}
}
