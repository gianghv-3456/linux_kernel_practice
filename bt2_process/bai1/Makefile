all: my_ls copy clean

my_ls.o: my_ls.c
	gcc -c my_ls.c

my_ls: my_ls.o
	gcc -o my_ls my_ls.o

copy:
	sudo cp my_ls /usr/local/bin

clean:
	rm -f my_ls.o my_ls

