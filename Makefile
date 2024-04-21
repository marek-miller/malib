LIBNAME= malib

ASM= nasm
ASM_FLAGS=	-f elf64 -g -F dwarf -w+all -w-reloc-rel-dword

CC= gcc
CC_FLAGS=	-g -O0 -Wall -Wextra

DEPS= malib.h

.PHONY: all clean clean-test build build-test test

all: build build-test

clean: clean-test
	rm -f *.o *.a
	rm -f malib-run

%.o: %.s
	${ASM} ${ASM_FLAGS} -o $@ $< 

%.o: %.c
	${CC} ${CC_FLAGS} -o $@ -c $< -I./

build: ${DEPS} malib.o main.o
	ar cr lib${LIBNAME}.a malib.o
	ranlib lib${LIBNAME}.a
	ld -o malib-run main.o lib${LIBNAME}.a


# Testing
TEST_DRIVE=	${LIBNAME}-test
TEST_OBJS=	test.o

build-test: build ${TEST_OBJS}
	${CC} ${CC_FLAGS} -o ${TEST_DRIVE} ${TEST_OBJS} -L./ -l${LIBNAME}

test: build-test
	 ./${TEST_DRIVE}

clean-test:
	rm -f ${TEST_DRIVE}

