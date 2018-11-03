all:
	gcc main.c -o main.o -Wall
run:
	./main.o
clean:
	-rm -f main.o
