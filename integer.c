#include "integer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void initInt(Integer a) {
	a.i = 0;
	a.arr = NULL;
}

Integer CreatIntegerFromString(char *str) {
	int la;
	static Integer I;
	initInt(I);
	la = strlen(str) - 1;
	I.arr = (char *)malloc(sizeof(char)*(la+2));
	strcpy(I.arr, str);
	for((I.i) = 0; (I.i) <= la; (I.i)++) {
		        I.arr[I.i] = I.arr[I.i] - 48;
		}
	return I;
}



Integer AddIntegers(Integer a, Integer b) {
	Integer c;initInt(c);
	static Integer Add;initInt(Add);
	int la, lb, i, j, r = 0, diff;
	la = a.i - 1;
	lb = b.i - 1;
	c.arr = (char *)malloc(sizeof(char)*((la+1)*(lb+1)));
        Add.arr = (char *)malloc(sizeof(char)*((la+1)*(lb+1)));
	if(la > lb) {
		diff = la - lb;
		for(i = b.i; i >= 0; i--) 
			b.arr[i + diff] = b.arr[i];
		for(i = 0; i < diff; i++)
			b.arr[i] = '0' - 48;
		b.i = b.i + diff;
	}
	if(lb > la) {
		diff = lb - la;
		for(i = a.i; i >= 0; i--)
			a.arr[i + diff] = a.arr[i];
		for(i = 0; i < diff; i++)
			a.arr[i] = '0' - 48;
		a.i = a.i + diff;
	}
	
	
	for(i = a.i - 1, j = b.i - 1; i >= 0; i--, j--) {
		c.arr[c.i++] = (a.arr[i] + b.arr[j] + r) % 10;
		r = (a.arr[i] + b.arr[j] +r) / 10;
	}
	c.arr[c.i] = r;
	
	for(i = c.i; i >= 0; i--)
		Add.arr[Add.i++] = c.arr[i];
	Add.arr[Add.i] = '\0';
	return Add;
}

			
Integer multiply(Integer a, Integer b) {
    static Integer mul; initInt(mul);
    Integer c; initInt(c);
    Integer temp; initInt(temp);
    int la, lb;
    int i, j, x = 0, y;
    long int r = 0;
    long sum = 0;
    la = a.i - 1;
    lb = b.i - 1;
    c.arr = (char *)malloc(sizeof(char)*MAX);
    mul.arr = (char *)malloc(sizeof(char)*MAX);
    temp.arr = (char *)malloc(sizeof(char)*MAX);   
    

    for(i = b.i - 1; i >= 0; i--){
         r = 0;
         for(j = a.i - 1; j >= 0; j--){
             temp.arr[temp.i++] = (b.arr[i]*a.arr[j] + r)%10;
             r = (b.arr[i]*a.arr[j]+r)/10;
         }
         temp.arr[temp.i++] = r;
         x++;
         for(y = 0; y < x; y++){
             temp.arr[temp.i++] = 0;
         }
    }
   
    
    r=0;
    for(i = 0; i < a.i + b.i; i++){
         sum =0;
         y=0;
         for(j = 1; j <= b.i; j++){
             if(i <= a.i - 1 + j){
                 sum = sum + temp.arr[y+i];
             }
             y += j + a.i;
         }
         c.arr[c.i++] = (sum + r) % 10;
         r = (sum + r) / 10;
    }
    c.arr[c.i] = r;
    
    for(i = c.i - 1; i >= 0; i--){
         mul.arr[mul.i++] = c.arr[i] + 48;
    }
    mul.arr[mul.i] = '\0';
    return mul;
}

void PrintInteger(Integer a) {
	int k;
	for(k = a.i - 1; k >= 0; k--) {
		a.arr[k] = a.arr[k] + 48;
	}
	a.arr[a.i] = '\0';
	printf("%s\n", a.arr);
}



Integer SubtractIntegers(Integer a, Integer b) {
	Integer c;initInt(c);
	static Integer Subtract;initInt(Subtract);
	int la, lb, r = 0, i, carry = 0, diff, flag = 0;
	la = a.i - 1;
	lb = b.i - 1;
	c.arr = (char *)malloc(sizeof(char)*((la+1)*(lb+1)));
        Subtract.arr = (char *)malloc(sizeof(char)*((la+1)*(lb+1)));
        
	if(la > lb) {
		diff = la - lb;
		for(i = b.i; i >= 0; i--) 
			b.arr[i + diff] = b.arr[i];
		for(i = 0; i < diff; i++)
			b.arr[i] = '0' - 48;
		b.i = b.i + diff;
		flag = 1;
	}
	if(lb > la) {
		diff = lb - la;
		for(i = a.i; i >= 0; i--)
			a.arr[i + diff] = a.arr[i];
		for(i = 0; i < diff; i++)
			a.arr[i] = '0' - 48;
		a.i = a.i + diff;
		flag = 2;
	}
	if(la == lb) {
		for(i = 0; i <= la; i++) {
			if(a.arr[i] > b.arr[i]) {
				flag = 1;
				break;
			}
			if(a.arr[i] < b.arr[i]) {
				flag = 2;
				break;
			}
		}
	}
		
	
	

	if(flag == 1) {
		for (i = a.i - 1; i >= 0; i--) {
			if(a.arr[i] < (b.arr[i] + carry)) {
				r = a.arr[i] + 10;
				c.arr[c.i] = r - (b.arr[i] + carry);
				c.i++;
				carry = 1;
			}
			else {
				c.arr[c.i] = a.arr[i] - (b.arr[i] + carry);
				c.i++;
				carry = 0;
			}
		}
	}
	
	if(flag == 2) {
		for(i = a.i - 1; i >= 0; i--) {
			if(b.arr[i] < (a.arr[i] + carry)) {
				r = b.arr[i] + 10;
				c.arr[c.i] = r - (a.arr[i] + carry);
				c.i++;
				carry = 1;
			}
			else {
				c.arr[c.i] = b.arr[i] - (a.arr[i] + carry);
				c.i++;
				carry = 0;
			}
		}
	}
	Subtract.i = 0;
	if(flag == 2) {
		Subtract.arr[Subtract.i] = '-' - 48;
		Subtract.i++;
	}			
	for(i = c.i; i >= 0; i--)
		Subtract.arr[Subtract.i++] = c.arr[i];
	Subtract.arr[Subtract.i] = '\0';
	return Subtract;
}




