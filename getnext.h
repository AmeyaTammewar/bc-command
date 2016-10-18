#define OPERAND 10
#define OPERATOR 20
#define ASSIGOPR 30
#define VARIABLE 40
#define	END	50
#define ERROR	60
typedef struct token {
	int type; // type takes values OPERAND/OPERATOR/END/
	Integer number;
	char op;
	int a;
}token;
token *getnext(char *, int *);
