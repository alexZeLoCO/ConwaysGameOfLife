CC=gcc
maindir=src
logicdir=libs/game/logic
factorydir=libs/game/factory
boarddir=libs/board
errordir=libs/logging/error
logdir=libs/logging/log
mediadir=libs/media
GCFLAGS=-g
LIBS=$(shell pkg-config --libs jansson)
CFLAGS=$(shell pkg-config --cflags jansson)

main : $(maindir)/main.c logic.o board.o factory.o media.o log.o
	$(CC) $(maindir)/main.c -o main logic.o board.o factory.o media.o log.o $(LIBS) $(CFLAGS) $(GCFLAGS)

logic.o : $(logicdir)/logic.h $(logicdir)/logic.c board.o error.o media.o
	$(CC) -c $(logicdir)/logic.c $(logicdir)/logic.h board.o error.o media.o $(GCFLAGS)

media.o : $(mediadir)/media.h $(mediadir)/media.c board.o
	$(CC) -c $(mediadir)/media.c $(mediadir)/media.h board.o $(GCFLAGS)

factory.o : $(factorydir)/factory.c $(factorydir)/factory.h board.o error.o log.o
	$(CC) -c $(factorydir)/factory.c $(factorydir)/factory.h board.o error.o log.o $(GCFLAGS)

board.o : $(boarddir)/board.c $(boarddir)/board.h error.o
	$(CC) -c $(boarddir)/board.c $(boarddir)/board.h error.o $(GCFLAGS)

error.o : $(errordir)/error.c $(errordir)/error.h
	$(CC) -c $(errordir)/error.c $(errordir)/error.h $(GCFLAGS)

log.o : $(logdir)/log.c $(logdir)/log.h
	$(CC) -c $(logdir)/log.c $(logdir)/log.h $(GCFLAGS)


clean : 
	rm **.o; rm **.h.gch; rm output/*.ppm; rm main;

