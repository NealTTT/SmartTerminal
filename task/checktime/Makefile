SOURCES := $(wildcard *.c)
OBJECTS := ${SOURCES:%.c=%.o}
VPATH = $(OUTPUTDIR)

all : ${OBJECTS}

%.o : %.c
	$(CC) -o ${OUTPUTDIR}/$@ -c $< $(CFLAGS)

clean :