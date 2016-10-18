#include<stdio.h>
#include<string.h>
#include"integer.h"
int main() {
	Integer a, b, c;
	char str1[100], str2[100];
	int choice;
	initInt(a);
	initInt(b);
	initInt(c);
	printf("1.Add\n2.subtract\n3.multiply\n4.help\n");
	scanf("%d", &choice);
	scanf("%s", str1);
	scanf("%s", str2);
	a = CreatIntegerFromString(str1);
	b = CreatIntegerFromString(str2);
	switch(choice) {
		case 1:
			c = AddIntegers(a, b);
			break;
		case 2:
			c = SubtractIntegers(a, b);
			break;
		case 3:
			c = multiply(a, b);
			break;
		case 4: 
			printf("usage: 1.enter choice\n2.enter two nos\n");
	} 
	PrintInteger(c);
	return 0;
}
