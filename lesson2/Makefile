CC = g++
CFLAGS = -c

all: final

final: main.o 
	$(CC) main.o -o final

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm *.o final