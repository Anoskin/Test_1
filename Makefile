CC = gcc


test1.exe: main.o
	$(CC) -o test1.exe main.o


main.o: main.c
	$(CC) -O0 -g3 -Wall -c main.c
