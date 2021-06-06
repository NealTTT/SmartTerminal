DEBFLAGS = -g

PRJ_HOME := $(shell pwd)
SOURCES := $(wildcard *.c)
OBJECTS := ${SOURCES:%.c=%.o}
INCPATH := -I$(PRJ_HOME)/ -I/home/neal/workspace/kernel/include

export CFLAGS += $(INCPATH) $(DEBFLAGS) -lpthread
export CC = arm-linux-gnueabihf-gcc
export OUTPUTDIR = $(PRJ_HOME)/output

PROGRAM = smart_terminal
VPATH = ${OUTPUTDIR}

.PHONY : all
all : ${PROGRAM}

${PROGRAM} : ${OBJECTS} ochecktime
	$(CC) -o $@ ${OUTPUTDIR}/*.o $(CFLAGS)
%.o : %.c
	$(CC) -o ${OUTPUTDIR}/$@ -c $< $(CFLAGS)

ochecktime :
	@$(MAKE) -C task/checktime/

.PHONY : clean
clean :
	$(RM) ${OUTPUTDIR}/*.o *.o ${PROGRAM} 