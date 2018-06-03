CC = g++
CFLAGS = -Wall -std=c++14 -lncurses
.SUFFIXES : .cc .o

#NCURSES_INCLUDE=/usr/local/opt/ncurses/include
#NCURSES_LIB=/usr/local/opt/ncurses/lib

SRCS = pane.cc statepane.cc battleshipMap.cc inputpane.cc
OBJS := ${SRCS:cc=o} 
PROGS := ${SRCS:.cc=}
TEST = pane_test.cc

.PHONY: all
	all: ${PROGS}

${PROGS} : % : %.o Makefile
	    ${CC} -lncurses $< -o $@ 

clean:
	    rm -f ${PROGS} ${OBJS}

%.o: %.cc Makefile
	    ${CC} ${CFLAGS} -c $<

test: ${OBJS}
	${CC} ${CFLAGS} $(TEST) ${OBJS} 


