CC = g++
CFLAGS = -Wall -std=c++14 -lncurses
.SUFFIXES : .cc .o

#NCURSES_INCLUDE=/usr/local/opt/ncurses/include
#NCURSES_LIB=/usr/local/opt/ncurses/lib

SRCS = battleshipApp.cc
OBJS := ${SRCS:cc=o} 
PROGS := ${SRCS:.cc=}

all: ${OBJS}

%.o : %.cc Makefile
	    ${CC} -lncurses ${CFLAGS} $< -o $@ 

clean:
	    rm -f ${PROGS} ${OBJS}


