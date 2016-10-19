#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "g.h"
Integer infix(char *);
int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < len - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}





int main() {
	char str[10000];
	int x; 
	Integer ans;initInt(&ans);
	while((x = readline(str, 10000))) {
		if(strcmp("quit", str) == 0)
			return 0;
		ans = infix(str);
		PrintInteger(ans);
	}
	return 0;
}
