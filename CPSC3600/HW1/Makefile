all: valueServer valueGuesser

valueServer: valueServer.o
	gcc -Wall valueServer.o -o valueServer

valueGuesser: valueGuesser.o
	gcc -Wall valueGuesser.o -o valueGuesser

.c.o:
	gcc -c $*.c

clean:
	 rm valueGuesser valueServer *o

valueServer.c: headers.h
valueGuesser.c: headers.h
