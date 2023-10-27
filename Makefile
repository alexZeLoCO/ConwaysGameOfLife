CC=gcc
maindir=src
logicdir=libs/game/logic
factorydir=libs/game/factory
boarddir=libs/board
errordir=libs/error
GCFLAGS=-g
LIBS=$(shell pkg-config --libs jansson)
CFLAGS=$(shell pkg-config --cflags jansson)

main : $(maindir)/main.c logic.o board.o factory.o
	$(CC) $(maindir)/main.c -o main logic.o board.o factory.o $(LIBS) $(CFLAGS) $(GCLFAGS)

logic.o : $(logicdir)/logic.h $(logicdir)/logic.c board.o error.o
	$(CC) -c $(logicdir)/logic.c $(logicdir)/logic.h board.o error.o $(GCLFAGS)

factory.o : $(factorydir)/factory.c $(factorydir)/factory.h board.o error.o
	$(CC) -c $(factorydir)/factory.c $(factorydir)/factory.h board.o error.o $(GCLFAGS)

board.o : $(boarddir)/board.c $(boarddir)/board.h error.o
	$(CC) -c $(boarddir)/board.c $(boarddir)/board.h error.o $(GCLFAGS)

error.o : $(errordir)/error.c $(errordir)/error.h
	$(CC) -c $(errordir)/error.c $(errordir)/error.h $(GCLFAGS)


clean : 
	rm **.o
	rm main

