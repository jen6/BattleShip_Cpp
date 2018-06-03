CC = g++
CFLAGS = -Wall -std=c++14
.SUFFIXES : .cc .o

#NCURSES_INCLUDE=/usr/local/opt/ncurses/include
#NCURSES_LIB=/usr/local/opt/ncurses/lib

SRCS = util.cc ship.cc aircraft.cc battleship.cc cruiser.cc destroyer.cc defenser.cc service.cc

OBJS := ${SRCS:cc=o} 
PROGS := ${SRCS:.cc=}
TEST = pane_test.cc

all: ${OBJS}

%.o: %.cc Makefile
	${CC} -o $@ ${CFLAGS} -c $<


#${PROGS} : % : %.o Makefile
#	    ${CC} $< -o $@ 

clean:
	    rm -f ${PROGS} ${OBJS}

test: ${OBJS}
	${CC} ${CFLAGS} $(TEST) ${OBJS} 


