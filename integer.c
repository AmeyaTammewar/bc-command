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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
extern int State;
void initInt(Integer *a) {
	a->i = 0;
	a->count = 0;
	a->arr = NULL;
}
void integer(Integer *a) {
	int i;
	for(i = 0; i <= a->i; i++) {
		        a->arr[i] = a->arr[i] - '0';
	}
}
Integer *AddIntegers(Integer *a, Integer *b) {
	Integer *c;
	Integer *Add;
	int la, lb, i, j, r = 0, diff, flag1 = 0, flag2 = 0, flag = 0;
	for(i = 0; i < a->i; i++) {
		if(a->arr[i] == '.' - '0') {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		for(j = i; j < a->i; j++)
			a->arr[j] = a->arr[j + 1];
		a->i--;
		flag = 0;
	}
	for(i = 0; i < b->i; i++) {
		if(b->arr[i] == '.' - '0') {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		for(j = i; j < b->i; j++)
			b->arr[j] = b->arr[j + 1];
		b->i--;
		flag = 0;
	}
	if(a->arr[0] == '-' - '0') {
		for(i = 1; i <= a->i; i++) 
			a->arr[i - 1] = a->arr[i];
		a->i = a->i - 1;
		flag1 = 1;
	}
	if(b->arr[0] == '-' - '0') {
		for(i = 1; i <= b->i; i++)
			b->arr[i - 1] = b->arr[i];
		b->i = b->i - 1;
		flag2 = 1;
	}
	if(flag1 == 1 && flag2 != 1) {
		Add = SubtractIntegers(b, a);
		return Add;
	}
	if(flag2 == 1 && flag1 != 1) {
		Add = SubtractIntegers(a, b);
		return Add;
	}		
	if(a->count > b->count) {
		j = a->count - b->count;
		for(i = b->i; i < b->i + j; i++)
			b->arr[i] = '0' - '0';
		b->i = b->i + j;
		b->count = a->count;
	}
	if(b->count > a->count) {
		j = b->count - a->count;
		for(i = a->i; i < a->i + j; i++)
			a->arr[i] = '0' - '0';
		a->i = a->i + j;
		a->count = b->count;
	}
	la = a->i - 1;
	lb = b->i - 1;
	c = (Integer*)malloc(sizeof(Integer));
	Add = (Integer*)malloc(sizeof(Integer));
	initInt(c);
	initInt(Add);
	c->arr = (char*)malloc(sizeof(char)*MAX);
        Add->arr = (char*)malloc(sizeof(char)*MAX);
	if(la > lb) {
		diff = la - lb;
		for(i = b->i; i >= 0; i--) 
			b->arr[i + diff] = b->arr[i];
		for(i = 0; i < diff; i++)
			b->arr[i] = '0' - '0';
		b->i = b->i + diff;
	}
	if(lb > la) {
		diff = lb - la;
		for(i = a->i; i >= 0; i--)
			a->arr[i + diff] = a->arr[i];
		for(i = 0; i < diff; i++)
			a->arr[i] = '0' - '0';
		a->i = a->i + diff;
	}
	
	
	for(i = a->i - 1, j = b->i - 1; i >= 0; i--, j--) {
		c->arr[c->i++] = (a->arr[i] + b->arr[j] + r) % 10;
		r = (a->arr[i] + b->arr[j] +r) / 10;
	}
	c->arr[c->i] = r;
	Add->i = 0;
	if(flag1 == 1 && flag2 == 1) {
		Add->arr[Add->i] = '-' - '0';
		Add->i++;
	}			
	for(i = c->i; i >= 0; i--)
		Add->arr[Add->i++] = c->arr[i];
	Add->arr[Add->i] = '\0';
	if(a->count != 0) {
		for(i = Add->i; i >= Add->i - a->count; i--)
			Add->arr[i + 1] = Add->arr[i];
		Add->arr[Add->i - a->count] = '.' - '0';
		Add->i = Add->i + 1;
		Add->count = a->count;
	}
	for(i = 0; i < Add->i; i++) {
		if(Add->arr[i] != '0' - '0')
			break;
	}
	for(j = 0; j <= (Add->i - i); j++)
		Add->arr[j] = Add->arr[j + i];
	Add->i = Add->i - i;
	free(c);
	return Add;
}

Integer *multiply(Integer *a, Integer *b) {
	Integer *mul; 
	Integer *c; 
	Integer *temp;
	int la, lb, flag1 = 0, flag2 = 0, flag = 0;
	int i, j, p = 0, q;
	long int r = 0;
	long sum = 0;
	for(i = 0; i < a->i; i++) {
		if(a->arr[i] == '.' - '0') {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		for(j = i; j < a->i; j++)
			a->arr[j] = a->arr[j + 1];
		a->i--;
		flag = 0;
	}
	for(i = 0; i < b->i; i++) {
		if(b->arr[i] == '.' - '0') {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		for(j = i; j < b->i; j++)
			b->arr[j] = b->arr[j + 1];
		b->i--;
		flag = 0;
	}
	if(a->arr[0] == '-' - '0') {
		for(i = 1; i <= a->i; i++) 
			a->arr[i - 1] = a->arr[i];
		a->i = a->i - 1;
		flag1 = 1;
	}
	if(b->arr[0] == '-' - '0') {
		for(i = 1; i <= b->i; i++)
			b->arr[i - 1] = b->arr[i];
		b->i = b->i - 1;
		flag2 = 1;
	}
	la = a->i - 1;
	lb = b->i - 1;
	c = (Integer *)malloc(sizeof(Integer));
	initInt(c);
	mul = (Integer *)malloc(sizeof(Integer));
	initInt(mul);
	temp = (Integer *)malloc(sizeof(Integer));
	initInt(temp);
	c->arr = (char *)malloc(sizeof(char)*MAX);
	mul->arr = (char *)malloc(sizeof(char)*MAX);
	temp->arr = (char *)malloc(sizeof(char)*MAX);   

	for(i = b->i - 1; i >= 0; i--){
		r = 0;
		for(j = a->i - 1; j >= 0; j--){
			temp->arr[temp->i++] = (b->arr[i] * a->arr[j] + r) % 10;
			r = (b->arr[i] * a->arr[j] + r) / 10;
		}
		temp->arr[temp->i++] = r;
		p++;
		for(q = 0; q < p; q++){
			temp->arr[temp->i++] = '0' - '0';
		}
	}
	r = 0;
	for(i = 0; i < (a->i + b->i); i++){
		sum = 0;
		q = 0;
		for(j = 1; j <= b->i; j++){
			if(i <= a->i - 1 + j){
				sum = sum + temp->arr[q + i];
			}
			q = q + j + a->i;
		}
		c->arr[c->i++] = (sum + r) % 10;
		r = (sum + r) / 10;
	}
	c->arr[c->i] = r;
	mul->i = 0;
	if(flag1 == 1 || flag2 == 1) {
		mul->arr[mul->i] = '-' - '0';
		mul->i++;
	}			
	for(i = c->i - 1; i >= 0; i--){
		mul->arr[mul->i++] = c->arr[i];
	}
	mul->arr[mul->i] = '\0';
	q = a->count + b->count;
	if(q != 0) {
		for(i = mul->i ; i >= mul->i - q; i--) {
			mul->arr[i + 1] = mul->arr[i];
		}
		mul->arr[mul->i - q] = '.' - '0';
		mul->i = mul->i + 1;
		mul->count = q;
	}
	for(i = 0; i < mul->i; i++) {
		if(mul->arr[i] != '0' - '0')
			break;
	}
	for(j = 0; j <= (mul->i - i); j++)
		mul->arr[j] = mul->arr[j + i];
	mul->i = mul->i - i;
	free(c);
	free(temp);
	return mul;
}
Integer *SubtractIntegers(Integer *a, Integer *b) {
	Integer *c;
	Integer *Subtract;
	int la, lb, r = 0, i, carry = 0, diff, flag = 0, j;
	for(i = 0; i < a->i; i++) {
		if(a->arr[i] == '.' - '0') {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		for(j = i; j < a->i; j++)
			a->arr[j] = a->arr[j + 1];
		a->i--;
		flag = 0;
	}
	for(i = 0; i < b->i; i++) {
		if(b->arr[i] == '.' - '0') {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		for(j = i; j < b->i; j++)
			b->arr[j] = b->arr[j + 1];
		b->i--;
		flag = 0;
	}
	if(a->count > b->count) {
		j = a->count - b->count;
		for(i = b->i; i < b->i + j; i++)
			b->arr[i] = '0' - '0';
		b->i = b->i + j;
		b->count = a->count;
	}
	if(b->count > a->count) {
		j = b->count - a->count;
		for(i = a->i; i < a->i + j; i++)
			a->arr[i] = '0' - '0';
		a->i = a->i + j;
		a->count = b->count;
	}
	la = a->i - 1;
	lb = b->i - 1;
	c = (Integer*)malloc(sizeof(Integer));
	initInt(c);
	Subtract = (Integer*)malloc(sizeof(Integer));
	initInt(Subtract);
	c->arr = (char *)malloc(sizeof(char)*MAX);
        Subtract->arr = (char *)malloc(sizeof(char)*MAX);
        for(i = 0; i < MAX; i++) 
		c->arr[i] = '0' - '0';
	if(la > lb) {
		diff = la - lb;
		for(i = b->i; i >= 0; i--) 
			b->arr[i + diff] = b->arr[i];
		for(i = 0; i < diff; i++)
			b->arr[i] = '0' - '0';
		b->i = b->i + diff;
		flag = 1;
	}
	if(lb > la) {
		diff = lb - la;
		for(i = a->i; i >= 0; i--)
			a->arr[i + diff] = a->arr[i];
		for(i = 0; i < diff; i++)
			a->arr[i] = '0' - '0';
		a->i = a->i + diff;
		flag = 2;
	}
	if(la == lb) {
		for(i = 0; i <= la; i++) {
			if(a->arr[i] > b->arr[i]) {
				flag = 1;
				break;
			}
			if(a->arr[i] < b->arr[i]) {
				flag = 2;
				break;
			}
		}
	}
		
	if(flag == 1) {
		for (i = a->i - 1; i >= 0; i--) {
			if(a->arr[i] < (b->arr[i] + carry)) {
				r = a->arr[i] + 10;
				c->arr[c->i] = r - (b->arr[i] + carry);
				c->i++;
				carry = 1;
			}
			else {
				c->arr[c->i] = a->arr[i] - (b->arr[i] + carry);
				c->i++;
				carry = 0;
			}
		}
	}
	
	if(flag == 2) {
		for(i = a->i - 1; i >= 0; i--) {
			if(b->arr[i] < (a->arr[i] + carry)) {
				r = b->arr[i] + 10;
				c->arr[c->i] = r - (a->arr[i] + carry);
				c->i++;
				carry = 1;
			}
			else {
				c->arr[c->i] = b->arr[i] - (a->arr[i] + carry);
				c->i++;
				carry = 0;
			}
		}
	}
	Subtract->i = 0;
	if(flag == 2) {
		Subtract->arr[Subtract->i] = '-' - '0';
		Subtract->i++;
	}			
	for(i = c->i; i >= 0; i--)
		Subtract->arr[Subtract->i++] = c->arr[i];
	Subtract->arr[Subtract->i] = '\0';
	if(a->count != 0) {
		for(i = Subtract->i; i >= Subtract->i - a->count; i--)
			Subtract->arr[i + 1] = Subtract->arr[i];
		Subtract->arr[Subtract->i - a->count] = '.' - '0';
		Subtract->i = Subtract->i + 1;
		Subtract->count = a->count;
	}
	for(i = 0; i < Subtract->i; i++) {
		if(Subtract->arr[i] != '0' - '0')
			break;
	}
	for(j = 0; j <= (Subtract->i - i); j++)
		Subtract->arr[j] = Subtract->arr[j + i];
	Subtract->i = Subtract->i - i;
	free(c);
	return Subtract;
}
Integer *divide(Integer *a, long int b) {
	Integer *c;
	extern int State;
	int i, j, flag = 0;
	long int temp = 1, remainder;
	temp = a->arr[0];
	remainder = a->arr[0];
	c = (Integer *)malloc(sizeof(Integer));
	initInt(c);
	c->arr = (char*)malloc(sizeof(char)*MAX);
	for(i = 1; i <= a->i; i++){
		if(b <= temp){
			c->arr[c->i++] = temp / b;
			temp = temp % b;
			remainder = temp;
			temp = temp*10 + a->arr[i];
			flag = 1;

		}
		else {
			remainder = temp;
			temp = temp*10 + a->arr[i];
			if(flag == 1)
				c->arr[c->i++] = '0' - '0';
		}
	}
	c->arr[c->i] = '\0';
	if(State == 5) {
		c->i = 0;
		if(remainder == 0) {
			c->arr[0] = '0' - '0';
			c->i++;
			c->arr[c->i] = '\0';
			State = 0;
			return c;
		}
		while(remainder != 0) {
			temp = remainder % 10;
			remainder = remainder / 10;
			c->arr[c->i] = temp;
			c->i++;
		}
		j = 0;
		for(i = c->i - 1; i >= 0; i--) {
			c->arr[j++] = c->arr[i]; 
		}
		c->arr[j] = '\0';
		c->i = j;
		State = 0;
	}
	return c;
}
		
Integer *Compare(Integer *a, Integer *b, char opr) {
	int x, y, i, diff, flag = 0, j = 0;
	extern int State;
	Integer *p;
	p = (Integer *)malloc(sizeof(Integer));
	initInt(p);
	p->arr = (char*)malloc(sizeof(char)*3);
	x = a->i - a->count;
	y = b->i - b->count;
	switch(opr) {
		case '>':
			if(x > y) {
				p->arr[p->i] = '1' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				return p;
			}
			else if(x < y) {
				p->arr[p->i] = '0' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				return p;
			}
			else {
				if(a->i > b->i) {
					diff = a->i - b->i;
					for(i = b->i; i < b->i + diff; i++) {
						b->arr[i] = '0' - '0';
					}
					b->i = b->i + diff;
					b->count = b->count + diff;
				}
				if(b->i > a->i) {
					diff = b->i - a->i;
					for(i = a->i; i < a->i + diff; i++) {
						a->arr[i] = '0' - '0';
					}
					a->i = a->i + diff;
					a->count = a->count + diff;
				}
				for(i = 0; i < a->i; i++) {
					if(a->arr[i] > b->arr[i]) {
						flag = 1;
						break;
					}
					if(a->arr[i] == b->arr[i]) 
						j++;
				}
				if((flag == 1) || ((State == 1) && (i == j))) {
					p->arr[0] = '1' - '0';
					p->i++;
					p->arr[p->i] = '\0';
					return p;
				}
				else {
					p->arr[0] = '0' - '0';
					p->i++;
					p->arr[p->i] = '\0';
					return p;
				}
				
							
			}
			break;
		case '<':
			if(x < y) {
				p->arr[0] = '1' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				return p;
			}
			else if(x > y) {
				p->arr[0] = '0' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				return p;
			}
			else {
				if(a->i > b->i) {
					diff = a->i - b->i;
					for(i = b->i; i < b->i + diff; i++) {
						b->arr[i] = '0' - '0';
					}
					b->i = b->i + diff;
					b->count = b->count + diff;
				}
				if(b->i > a->i) {
					diff = b->i - a->i;
					for(i = a->i; i < a->i + diff; i++) {
						a->arr[i] = '0' - '0';
					}
					a->i = a->i + diff;
					a->count = a->count + diff;
				}
				for(i = 0; i < a->i; i++) {
					if(a->arr[i] < b->arr[i]) {
						flag = 1;
						break;
					}
					if(a->arr[i] == b->arr[i]) 
						j++;
				}
				if((flag == 1) || ((State == 1) && (i == j))) {		
					p->arr[0] = '1' - '0';
					p->i++;
					p->arr[p->i] = '\0';
					return p;
				}
					
				else {
					p->arr[0] = '0' - '0';
					p->i++;
					p->arr[p->i] = '\0';
					return p;
				}
				
							
			}
			break;
		case '=':
			intstring(a);
			intstring(b);
			if((a->i == b->i) && (a->count == b->count) && (strcmp(a->arr, b->arr) == 0)) {
				p->arr[0] = '1' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
			else {
				p->arr[0] = '0' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
		break;
		case '!':
			intstring(a);
			intstring(b);
			if((a->i == b->i) && (a->count == b->count) && (strcmp(a->arr, b->arr) == 0)) {
				p->arr[0] = '0' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
			else {
				p->arr[0] = '1' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
		break;
		case '&':
			intstring(a);
			intstring(b);
			if((strcmp(a->arr, "0") != 0) && (strcmp(b->arr, "0") != 0)) {
				p->arr[0] = '1' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
			else {
				p->arr[0] = '0' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
		break;
		case '|':
			intstring(a);
			intstring(b);
			if((strcmp(a->arr, "0") == 0) && (strcmp(b->arr, "0") == 0)) {
				p->arr[0] = '0' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
			else {
				p->arr[0] = '1' - '0';
				p->i++;
				p->arr[p->i] = '\0';
				integer(a);
				integer(b);
				return p;
			}
		break;			
	}
}

Integer *power(Integer *a, long int y) {
	Integer *b;
	long int i;
	b = (Integer *)malloc(sizeof(Integer));
	initInt(b);
	b->arr = (char *)malloc(sizeof(char)*MAX);
	b->arr[0] = '1' - '0';
	b->i++;
	b->arr[b->i] = '\0';
	for(i = y; i > 0; i--)
		b = multiply(b, a);
		return b;  
}
Integer *length(Integer *a) {
	Integer *I;	
	int x = 0, k, i = 0, j, flag = 0;
	char c[16];
	I = (Integer *)malloc(sizeof(Integer));
	initInt(I);
	I->arr = (char*)malloc(sizeof(char)*MAX);
	if(State == 3) { 
		for(i = 0; i < a->i; i++) {
			if(a->arr[i] == '.' - '0') {
				flag = 1;
				break;
			}
		}
		if(flag == 1)
			x = a->i - 1;
		else
			x = a->i;
	}
	if(State == 4) { 
		x = a->count;
		if(x == 0) {
			I->arr[0] = '0' - '0';
			I->i++;
			I->arr[I->i] = '\0';
			State = 0;
			return I;
		}
	} 
	i = 0;
	while(x != 0) { 
        	k = x % 10;
		x = x / 10;
		c[i] = k;
		i++;
	}
	j = 0;
	for(k = i-1; k >= 0; k--) {
		c[j++] = c[k]; 
	}
	c[j] = '\0';
	strcpy(I->arr, c);
	I->i = j;
	State = 0;
	return I; 
}
long int Atoi(Integer *a) {
	long int b = 0;
	int i;
	for(i = 0; i < a->i; i++) 
		b = b*10 + a->arr[i] - '0';
	return b;
}
void PrintInteger(Integer *a) {
	printf("%s\n", a->arr);
}

void intstring(Integer *a) {
	int k;
	for(k = a->i - 1; k >= 0; k--) {
		a->arr[k] = a->arr[k] + '0';
	}
	a->arr[a->i] = '\0';
}
void initdata(datanode T) {
	int i;
	for(i = 0; i < SIZE; i++) {
		T.d[i].value.i = 0;
		T.d[i].value.count = 0;
		T.d[i].value.arr = NULL;
	}
	T.i = 0;
}	




