CC = g++
CFLAGS = -c

all: final

final: main.o complex.o
	$(CC) main.o complex.o -o final

main.o: main.cpp complex.h
	$(CC) $(CFLAGS) main.cpp

complex.o: complex.cpp complex.h
	$(CC) $(CFLAGS) complex.cpp

clean:
	rm *o final
