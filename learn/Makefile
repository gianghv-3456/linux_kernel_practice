CC=gcc
CFLAGS=-Wall -I.
SRC = fork_test.c
OBJ = $(SRC:.c=.o)
TARGET = bin

all: $(TARGET) running clean
$(TARGET):$(OBJ)
	$(CC) -o $@ $^ -lm

$(OBJ):
	$(CC) -c $(CFLAGS) $(SRC)

running:
	./bin

clean:
	rm -rf *.o $(TARGET)