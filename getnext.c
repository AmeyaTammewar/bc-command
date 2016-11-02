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
#include "g.h"
#include <string.h>

enum states { SPC, DIG, OPR, STOP, ERR, VAR, DEC};
token *getnext(char *arr, int *reset) {
	static int currstate;
	int nextstate, count = 0;
	static int i, flag = 0;
	extern int State;
	Integer *num;
	num = (Integer*)malloc(sizeof(Integer));
	initInt(num);
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	token *t = (token *)malloc(sizeof(token));
	initInt(&t->number);
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':  
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '<':
			case '>': case '=': case '&': case '!':
			case '|': case '^':
				nextstate = OPR;
				break;
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': 
			case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': 
			case 'w': case 'x': case 'y': case 'z': case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': 
			case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
			case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z': 
				nextstate = VAR;
				break;
			case '.' :
				nextstate = DEC;
				break;   
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}

		switch(currstate) {
			case SPC:
				if(nextstate == DIG || nextstate == VAR) {
					if(flag != 2)
						num->arr = (char*)malloc(sizeof(char)*MAX);
					num->arr[num->i] = arr[i];
					num->i++;
					num->arr[num->i] = '\0';
				}
				if(nextstate == OPR && flag != 0) {
					num->arr = (char*)malloc(sizeof(char)*MAX);
					num->arr[num->i] = arr[i];
					num->i++;
					num->arr[num->i] = '\0';
					flag++;
				}	
				break;
			case DIG:
				if(nextstate == DIG) {
					num->arr[num->i] = arr[i];
					num->i++;
					num->arr[num->i] = '\0';
					if(count != 0) {
						count++;
						num->count = count;
					}
					break;
				}
				
				else if(nextstate == DEC)
					break;
				else  {
					if(nextstate == OPR)
						i++;
					t->type = OPERAND;
					t->number.arr = (char*)malloc(sizeof(char)*(MAX));
					strcpy(t->number.arr, num->arr);
					t->number.i = num->i;
					t->number.count = num->count;
					free(num);
					currstate = nextstate;
					flag = 0;
					return t;
				}
				break;
			case OPR:
				if(nextstate == DIG) {
					if(flag != 0) {
						num->arr = (char*)malloc(sizeof(char)*MAX);
						num->arr[num->i] = arr[i - 1];
						num->i++;
						num->arr[num->i] = arr[i];
						num->i++;
						num->arr[num->i] = '\0';
						break;
					}
					else if(arr[i - 1] == '=') {
						num->arr = (char*)malloc(sizeof(char)*MAX);
						num->arr[num->i] = arr[i];
						num->i++;
						num->arr[num->i] = '\0';
						State = 6;
					}
					else {
						currstate = SPC;
						t->type = OPERATOR;
						t->op = arr[i - 1];	
						return t;
						break;
					}
				}
				else if(nextstate == OPR) {
					if(arr[i - 1] == '-') {
						t->type = ERROR;
						currstate = nextstate;
						return t;
						break;
					}
					else if(arr[i - 1] == ')') {
						t->type = OPERATOR;
						t->op = arr[i - 1];
						currstate = nextstate;
						i++;	
						return t;
						break;
					}
					else if((arr[i] != '(') && (arr[i] != ')') && (arr[i] != '=') && (arr[i] != '!') && (arr[i] != '&') && 						(arr[i] != '|')) {
					 	flag++;
						t->type = OPERATOR;
						t->op = arr[i - 1];
						currstate = nextstate;
						i++;	
						return t;
						break;
					}
					else if((arr[i] == '&') || (arr[i] == '|')) {
						i++;
						t->type = OPERATOR;
						t->op = arr[i - 1];
						currstate = SPC;	
						return t;
						break;
					}
					else if(arr[i] == '=') {
						if((arr[i - 1] == '>') || (arr[i - 1] == '<'))
							State = 1;
						if((arr[i - 1] == '=') || (arr[i - 1] == '!'))
							State = 2;
						t->type = OPERATOR;
						t->op = arr[i - 1];
						i++;
						currstate = SPC;	
						return t;
					}
					else  {
						t->type = OPERATOR;
						t->op = arr[i - 1];
						i++;
						currstate = nextstate;	
						return t;
					}
				}
				else if(nextstate == SPC) {
					if(arr[i - 1] == '=')
						State = 6;
					else if(arr[i - 1] == ')') {
						t->type = OPERATOR;
						t->op = arr[i - 1];
						currstate = nextstate;	
						return t;
						break;
					}
					else if(flag == 0) {
						flag++;
						t->type = OPERATOR;
						t->op = arr[i - 1];
						currstate = nextstate;	
						return t;
						break;
					}
				}
				else {
					t->type = OPERATOR;
					t->op = arr[i - 1];
					currstate = nextstate;	
					return t;
				}
				break;
			case DEC :
				if(nextstate == DIG) {
					num->arr[num->i] = arr[i];
					num->i++;
					num->arr[num->i] = '\0';
					count++;
					num->count = count;
					break;
				}
				break;	

			case VAR:
				if(nextstate == VAR) {
					num->arr[num->i] = arr[i];
					num->i++;
					num->arr[num->i] = '\0';
					break;
				}
				else {
					t->type = VARIABLE;
					t->number.arr = (char*)malloc(sizeof(char)*MAX);
					strcpy(t->number.arr, num->arr);
					t->number.i = num->i;
					if(strcmp(t->number.arr, "length") == 0)
						t->type = LENGTH;
					if(strcmp(t->number.arr, "scale") == 0)
						t->type = SCALE;
					if(strcmp(t->number.arr, "print") == 0)
						t->type = PRINT;
					currstate = nextstate;
					i++;
					free(num);
					return t;
				}
				break;

			case STOP:
				t->type = END;
				currstate = nextstate;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}








