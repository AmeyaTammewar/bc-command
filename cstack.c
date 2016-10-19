#include "g.h"
void cpush(cstack *s, char num) {
	s->a[s->i]= num;
	(s->i)++;
}

char cpop(cstack *s) {
	char t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int cempty(cstack *s) {
	return s->i == 0;
}
int cfull(cstack *s) {
	return s->i == MAX;
}

void cinit(cstack *s) {
	s->i = 0;
}
