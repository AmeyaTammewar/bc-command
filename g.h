#define MAX 100
#define OPERAND 10
#define OPERATOR 20
#define ASSIGOPR 30
#define VARIABLE 40
#define	END	50
#define ERROR	60
typedef struct Integer {
	char *arr;
	int i;
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
	int a;
}token;
token *getnext(char *, int *);

void push(stack *s, Integer num);
Integer pop(stack *s);
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
Integer CreatIntegerFromString(char *str);
Integer AddIntegers(Integer a, Integer b);
Integer SubtractIntegers(Integer a, Integer b);
Integer multiply(Integer a, Integer b);
void PrintInteger(Integer a);
