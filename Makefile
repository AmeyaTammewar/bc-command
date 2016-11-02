try: main.o integer.o stack.o cstack.o getnext.o infix.o 
	cc main.o integer.o stack.o cstack.o getnext.o infix.o -o project
main.o: main.c g.h
	cc -c main.c
integer.o: integer.c g.h
	cc -c integer.c
stack.o: stack.c g.h
	cc -c stack.c
cstack.o: cstack.c g.h
	cc -c cstack.c
getnext.o: getnext.c g.h
	cc -c getnext.c
infix.o: infix.c g.h
	cc -c infix.c
clean:
	rm *.o
