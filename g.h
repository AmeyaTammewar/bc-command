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
#define MAX 10000
#define SIZE 100
#define OPERAND 11
#define OPERATOR 12
#define PRINT 13
#define VARIABLE 14
#define LENGTH 15
#define SCALE 16
#define	END 17
#define ERROR 18
extern int State;
typedef struct Integer {
	char *arr;
	int i, count;
}Integer;

typedef struct node {
	Integer I;
	struct node *next;
}node;
typedef struct stack{
	node *head, *tail;
	int len;
}stack;

typedef struct cstack{
	char a[MAX];
	int i;
}cstack;

typedef struct token {
	int type; 
	Integer number;
	char op;
}token;
typedef struct data {
	char arr[16];
	Integer value;
}data;
typedef struct datanode {
	data d[SIZE];
	int i;
}datanode;
void initdata(datanode T);

token *getnext(char *, int *);
Integer *infix(char *);

void push(stack *s, Integer *num);
Integer *pop(stack *s);
int empty(stack *s);
void full(stack *s);
void init(stack *s);

void cpush(cstack *s, char num);
char cpop(cstack *s);
int cempty(cstack *s);
int cfull(cstack *s);
void cinit(cstack *s);

void initInt(Integer *a);
void integer(Integer *a);
void intstring(Integer *a);
Integer *AddIntegers(Integer *a, Integer *b);
Integer *SubtractIntegers(Integer *a, Integer *b);
Integer *multiply(Integer *a, Integer *b);
Integer *divide(Integer *a, long int b);
Integer *power(Integer *a, long int y);
Integer *Compare(Integer *a, Integer *b, char opr);
void PrintInteger(Integer *a);
long int Atoi(Integer *a);
Integer *length(Integer *a);



