CFLAGS= -ansi -pedantic -Wall -g
LFLAGS= -g
LIBS= -lm
CC = gcc
EXEC = ppal
OBJS = ppal.o dicionario.o
# target
$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS) $(LIBS)


ppal.o: ppal.c dicionario.h
	$(CC) $(CFLAGS) -c ppal.c


dicionario.o: dicionario.c dicionario.h
	$(CC) $(CFLAGS) -c dicionario.c

clean:
	rm -f *.o $(EXEC)

