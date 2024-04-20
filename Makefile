LIBNAME= malib

ASM= nasm
ASM_FLAGS=	-f elf64 -g -F dwarf -w+all

CC= gcc
CC_FLAGS=	-no-pie -Wall -Wextra

.PHONY: all clean clean-test build build-test test

all: build build-test

clean: clean-test
	rm -f *.o *.a
	rm -f malib-run


%.o: %.s
	${ASM} ${ASM_FLAGS} -o $@ $< 

%.o: %.c
	${CC} ${CC_FLAGS} -o $@ -c $< 

build: malib.o main.o
	ar cr lib${LIBNAME}.a $<
	ranlib lib${LIBNAME}.a
	ld -o malib-run main.o lib${LIBNAME}.a


# Testing
TEST_DRIVE=	${LIBNAME}-test
TEST_OBJS=	test.o

build-test: ${TEST_OBJS}
	${CC} ${CC_FLAGS} -o ${TEST_DRIVE} ${TEST_OBJS} -I./ -L./ -l${LIBNAME} 

test: build-test
	@./${TEST_DRIVE}

clean-test:
	rm -f ${TEST_DRIVE}

