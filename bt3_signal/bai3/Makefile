all: program_A program_B running clean

program_A: program_A.c
	gcc -o program_A program_A.c

program_B: program_B.c
	gcc -o program_B program_B.c

running:
	./program_A

clean:
	rm -f program_A program_B
