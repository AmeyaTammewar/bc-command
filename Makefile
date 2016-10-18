try: tryinteger.o integer.o
	cc tryinteger.o integer.o -o try
integer.o: integer.c integer.h
	cc -c integer.c
tryinteger.o: tryinteger.c
	cc -c tryinteger.c
clean:
	rm *.o
