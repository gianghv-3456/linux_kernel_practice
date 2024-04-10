all: sleep_program send_signal

sleep_program: sleep_program.c
	gcc -o sleep_program sleep_program.c

send_signal: send_signal.c
	gcc -o send_signal send_signal.c

clean:
	rm -f sleep_program send_signal
