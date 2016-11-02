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
#include <limits.h>
#include <string.h>
#include "g.h"
int State = 0;
datanode T;
int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while(((ch = getchar()) != '\n') && (i < len - 1)) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}
int main() {
	char str[MAX];
	int x = 0; 
	Integer *ans;
	initdata(T);
	while(x = readline(str, MAX)) {
		if(strcmp(str, "quit") == 0)
			return 0;
		ans = infix(str);
		if(State == 6) {
			State = 0;
			continue;
		}
		if(State == 8) {
			State = 0;
			printf("syntax error\n");
			continue;
		}
		State = 0; 
		PrintInteger(ans);
		free(ans);
	}
	return 0;
}

