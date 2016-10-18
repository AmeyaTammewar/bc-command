#define MAX 100
typedef struct Integer {
	char *arr;
	int i;
}Integer;

void initInt(Integer a);
Integer CreatIntegerFromString(char *str);
Integer AddIntegers(Integer a, Integer b);
Integer SubtractIntegers(Integer a, Integer b);
Integer multiply(Integer a, Integer b);
void PrintInteger(Integer a);
