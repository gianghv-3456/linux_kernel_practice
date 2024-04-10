CC=gcc
CFLAGS=-Wall -I.
LINKFLAGS=-lm
SRC=main.c hinhTamGiac.c hinhTron.c hinhVuong.c 
OBJ=$(SRC:.c=.o)
TARGET=bin 

all: $(TARGET)  running clean
$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(LINKFLAGS)

$(OBJ):
	$(CC) -c $(CFLAGS) $(SRC)

running:
	./bin

clean:
	rm -rf *.o $(TARGET)


