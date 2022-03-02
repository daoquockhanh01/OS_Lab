all: main.o readline.o factorial.o
	gcc -o myfactorial main.o readline.o factorial.o
main.o: main.c readline.h factorial.h
	gcc -c -o main.o main.c
readline.o: readline.c readline.h
	gcc -c -o readline.o readline.c
factorial.o: factorial.c factorial.h
	gcc -c -o factorial.o factorial.c
clean:
	rm -f *.o myfactorial