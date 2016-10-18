#include <stdio.h>
#include <stdlib.h>
#include "getnext.h"

enum states { SPC, DIG, OPR, STOP, ERR, A, VAR};
token *getnext(char *arr, int *reset) {
	static int currstate;
	int nextstate;
	static int i;
	Integer num;
	num.i = 0;
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': 
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')':
				nextstate = OPR;
				break;
			case '=':
				nextstate = A;
				break;
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': 
			case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': 
			case 'w': case 'x': case 'y': case 'z': case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': 
			case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
			case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z': 
				nextstate = VAR;
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
				if(nextstate == DIG)
						num.arr[num.i] = arr[i];
						num.i++;			
				break;
			case DIG:
				if(nextstate == DIG)
					num.arr[num.i] = arr[i];
					num.i++;
				else  {
					t->type = OPERAND;
					t->number = num;
					currstate = nextstate;
					return t;
				}
				break;
			case OPR:
				t->type = OPERATOR;
				t->op = arr[i - 1];	
				currstate = nextstate;
				return t;
				break;

			case VAR:
				t->type = VARIABLE;
				t->a = arr[i - 1];
				currstate = nextstate;
				return t;
				break;
			case A:
				t->type = ASSIGOPR;
				t->op = arr[i - 1];
				currstate = nextstate;
				return t;
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





