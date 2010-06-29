###########################################################################
#
# $Makefile - 02/20/03 - Greg Naughton$
#
# Makefile for Robohack - 0.07
#
###########################################################################

EXE_NAME = robohack
CC = gcc
CFLAGS = -c -g -Wall
SRC = src
O = obj

LIBS =	$(SRC)/structs.h \
	$(SRC)/globals.h \
	$(SRC)/defs.h \
	$(SRC)/robohack.h

OBJS = 	$(O)/robohack.o \
	$(O)/mng_bullets.o \
	$(O)/mng_explosions.o \
	$(O)/mng_slots.o \
	$(O)/trk_interact.o \
	$(O)/handle_movement.o \
	$(O)/paint_stuff.o \
	$(O)/initialize.o \
	$(O)/cleanup.o

all: dirs $(OBJS)
	$(CC) -g $(OBJS) -o $(EXE_NAME) -lcurses

$(O)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	@if [ ! -d $(O) ]; then rm -f $(O); mkdir $(O); fi

clean:
	rm -rf $(O) 
	rm -f $(EXE_NAME) 
	rm -f .rh_debug_log
	rm -f highscores.dat


