CC=gcc
CFLAGS=-Wall -fpic -I.
LINKFLAGS=-lm
SRCL=hinhTamGiac.c hinhTron.c hinhVuong.c 
SRC=main.c
OBJ=$(SRC:.c=.o)
OBJL=$(SRCL:.c=.o)
LIB=mylib
LIBFILE=libmylib.so

TARGET=bin 

all: $(TARGET)  running clean

$(TARGET):$(OBJ) $(LIBFILE)
	$(CC) -o $@ $(OBJ) -L. -l$(LIB) $(LINKFLAGS)

$(OBJ):
	$(CC) -c $(CFLAGS) $(SRC)

$(LIBFILE):$(OBJL)
	gcc -shared -o $(LIBFILE) $^
	sudo cp libmylib.so /usr/local/bin/$(LIBFILE)
	sudo ldconfig

$(OBJL): $(SRCL)
	$(CC) -c $(CFLAGS) $(SRCL)

running:
	./bin

clean:
	rm -rf *.o $(TARGET)


