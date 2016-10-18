#define MAX 128
typedef struct stack{
	Integer a[MAX];
	int i;
}stack;
void push(stack *s, Integer num);
Integer pop(stack *s);
int empty(stack *s);
int full(stack *s);
void init(stack *s);
