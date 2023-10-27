CC=gcc
maindir=src
logicdir=libs/game/logic
factorydir=libs/game/factory
boarddir=libs/board
errordir=libs/error

main : $(maindir)/main.c logic.o board.o factory.o
	$(CC) $(maindir)/main.c -o main logic.o board.o factory.o -ljansson

logic.o : $(logicdir)/logic.h $(logicdir)/logic.c board.o error.o
	$(CC) -c $(logicdir)/logic.c $(logicdir)/logic.h board.o error.o

factory.o : $(factorydir)/factory.c $(factorydir)/factory.h board.o error.o
	$(CC) -c $(factorydir)/factory.c $(factorydir)/factory.h board.o error.o

board.o : $(boarddir)/board.c $(boarddir)/board.h error.o
	$(CC) -c $(boarddir)/board.c $(boarddir)/board.h error.o

error.o : $(errordir)/error.c $(errordir)/error.h
	$(CC) -c $(errordir)/error.c $(errordir)/error.h


clean : 
	rm **.o

