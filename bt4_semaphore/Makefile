all: main running clean

main: main.o
	gcc -o main main.o

main.o: main.c
	gcc -c main.c

running:
	./main

clean:
	rm -f main *.o

