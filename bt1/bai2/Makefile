CC=gcc
CFLAGS=-Wall -I.
LINKFLAGS=-lm
SRCL=hinhTamGiac.c hinhTron.c hinhVuong.c 
SRC=main.c
OBJ=$(SRC:.c=.o)
OBJL=$(SRCL:.c=.o)
LIB=mylib
LIBFILE=libmyLib.a

TARGET=bin 

all: $(TARGET)  running clean
$(TARGET):$(OBJ) $(LIBFILE)
	$(CC) -o $@ $(OBJ) -L. -l$(LIB) $(LINKFLAGS)

$(OBJ):
	$(CC) -c $(CFLAGS) $(SRC)

$(LIBFILE):$(OBJL)
	ar rcs lib$(LIB).a $^

$(OBJL): $(SRCL)
	$(CC) -c $(CFLAGS) $(SRCL)

running:
	./bin

clean:
	rm -rf *.o $(TARGET)


