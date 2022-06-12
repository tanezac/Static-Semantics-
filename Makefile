CC = gcc
CFLAGS = -g -Wall -Wshadow 
DEPS = token.h character.h testTree.h scanner.h parser.h statSem.h identifierStack.h testTree.c scanner.c parser.c statSem.c identifierStack.c p3.c
OBJ = testTree.o scanner.o parser.o statSem.o identifierStack.o p3.o
LDFLAGS = -static
OUTPUT = statSem

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
statSem: $(OBJ)
	$(CC)  $(CFLAGS) -o $@ $^

.PHONY: all clean
clean:
	/bin/rm -f $(OUTPUT) *.o *.log

