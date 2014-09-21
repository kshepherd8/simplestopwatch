SRCDIR=src
#SOURCES:=$(wildcard src/.c)
SOURCES=src/main.c src/SysTimer.c src/StopWatch.c
BINDIR=bin

default: StopWatch

StopWatch: $(SOURCES)
	clang $(SOURCES) -lrt -lncurses -Wall -o $(BINDIR)/StopWatch

clean:
	rm bin/*
