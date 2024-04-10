all: bin running clean
bin: main.o hinhHoc.a 
	gcc -o bin main.o -L. -lhinhHoc -lm 

main.o: main.c 
	gcc -c main.c -Wall -I.

hinhHoc.a: hinhTamGiac.o hinhVuong.o hinhTron.o 
	ar rcs libhinhHoc.a hinhTamGiac.o hinhVuong.o hinhTron.o 

hinhVuong.o: hinhVuong.c
	gcc -c hinhVuong.c
hinhTamGiac.o: hinhTamGiac.c
	gcc -c hinhTamGiac.c 
hinhTron.o: hinhTron.c
	gcc -c hinhTron.c


running:
	./bin
clean:
	rm -rf *.o bin