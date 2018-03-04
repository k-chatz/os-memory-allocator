CC = gcc
OBJ      = main.o hashtable.o list.o malloc.o page.o
LINKOBJ  = main.o hashtable.o list.o malloc.o page.o
BIN      = mallocator


$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN)

main.o: main.c
	$(CC) -c main.c -o main.o

hashtable.o: ../hashtable.c
	$(CC) -c ../hashtable.c -o hashtable.o

list.o: ../list.c
	$(CC) -c ../list.c -o list.o

malloc.o: ../malloc.c
	$(CC) -c ../malloc.c -o malloc.o

page.o: ../page.c
	$(CC) -c ../page.c -o page.o

clean:
	rm -f *.o core
	rm -f $(BIN)

rebuild: clean $(BIN)
