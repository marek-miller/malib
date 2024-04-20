PROG= malib

ASM= nasm
ASM_FLAGS=	-f elf64 -g -F dwarf -w+all

CC= gcc
CC_FLAGS=	-no-pie -Wall -Wextra

OBJS= main.o

.PHONY: all clean test

%.o: %.s
	${ASM} ${ASM_FLAGS} -o $@ $< 

%.o: %.c
	${CC} ${CC_FLAGS} -o $@ -c $< 

main: main.o
	ld -o ${PROG} ${OBJS}

test:

all: main test

clean:
	rm -f *.o
