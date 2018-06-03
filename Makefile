CC = clang++
CFLAGS = -Wall -std=c++11
.SUFFIXES : .cc .o

#NCURSES_INCLUDE=/usr/local/opt/ncurses/include
#NCURSES_LIB=/usr/local/opt/ncurses/lib

VIEW_DIR = ./view
VIEW_SRCS = $(addprefix $(VIEW_DIR)/,pane.cc statepane.cc battleshipMap.cc inputpane.cc)
VIEW_OBJS = ${VIEW_SRCS:cc=o}

MODEL_DIR = ./model
MODEL_SRCS = $(addprefix $(MODEL_DIR)/,util.cc ship.cc aircraft.cc battleship.cc cruiser.cc destroyer.cc defenser.cc service.cc)
MODEL_OBJS = ${MODEL_SRCS:cc=o}

CONTROL_DIR = ./controller
CONTROL_SRCS = $(addprefix $(CONTROL_DIR)/,battleshipApp.cc)
CONTROL_OBJS = ${CONTROL_SRCS:cc=o}

SRCS = main.cc
OBJS := ${SRCS:cc=o} 
PROGS := ${SRCS:.cc=}

.PHONY: all
	all: ${PROGS}

${PROGS}: ${OBJS} ${VIEW_OBJS} ${CONTROL_OBJS} ${MODEL_OBJS}
	${CC} ${CFLAGS} -o $@ ${VIEW_SRCS} ${CONTROL_SRCS} ${MODEL_SRCS} ${SRCS} -lncurses

${OBJS}: ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS} 

${VIEW_OBJS}: ${VIEW_SRCS}
	${CC} ${CFLAGS} -c $< -o $@

${MODEL_OBJS}: ${MODEL_SRCS}
	${CC} ${CFLAGS} -c $< -o $@
	
${CONTROL_OBJS}: ${CONTROL_SRCS} ${MODEL_OBJS} ${VIEW_OBJS}
	${CC} ${CFLAGS} -c $< -o $@ 


clean:
	    rm -f ${PROGS} ${OBJS} ${VIEW_OBJS} ${CONTROL_OBJS} ${MODEL_OBJS}


