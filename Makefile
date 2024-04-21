NAME	= malib

SRC	= src
INCLUDE	= include
BUILD	= build
DEPS	= $(INCLUDE)/malib.h
OBJ	= $(BUILD)/obj
BIN	= $(BUILD)/bin
TEST	= test

LIB	= lib$(NAME).a
LIB_SRCS= $(NAME).s
LIB_OBJS= $(NAME).o

EXE	= $(NAME)
EXE_SRCS= main.s
EXE_OBJS= main.o

MKDIR	= mkdir
RM	= rm -f
RMDIR	= rm -rf

AS	= nasm
ASFLAGS	= -f elf64 -g -F dwarf -w+all -w-reloc-rel-dword

CC	= gcc
CFLAGS	= -Wall -Wextra -g -I$(INCLUDE)

AR	= ar
RANLIB	= ranlib
LD	= ld
LDFLAGS	=
LDLIBS	=

.PHONY: all clean

all: $(BUILD)/$(EXE)

run: $(BUILD)/$(EXE)
	@time -p $(BUILD)/$(EXE)

$(BUILD)/$(EXE): $(OBJ)/$(EXE_OBJS) $(BUILD)/$(LIB)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD)/$(LIB): $(OBJ)/$(LIB_OBJS)
	$(AR) cr $@ $^
	$(RANLIB) $@

$(OBJ)/%.o: $(SRC)/%.s | $(OBJ)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ) $(BIN):
	$(MKDIR) $@

clean: test-clean
	$(RMDIR) $(OBJ) $(BIN)


# Testing

TEST_BUILD	= $(BUILD)/$(TEST)
TEST_EXE	= test-$(NAME)
TEST_SRCS	= test.c
TEST_OBJS	= test.o
TEST_CFLAGS	= $(CFLAGS) -g -O0
TEST_LDFLAGS	= $(LDFLAGS)
TEST_LDLIBS	= $(LDLIBS) -lm

.PHONY: test test-clean

test: $(TEST_BUILD)/$(TEST_EXE)
	@time -p $(TEST_BUILD)/$(TEST_EXE) && echo OK

$(TEST_BUILD)/$(TEST_EXE): $(TEST_BUILD)/$(TEST_OBJS) $(BUILD)/$(LIB)
	$(CC) $(TEST_LDFLAGS) $^ -o $@ $(TEST_LDLIBS)

$(TEST_BUILD)/%.o: $(TEST)/%.c | $(TEST_BUILD)
	$(CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_BUILD):
	$(MKDIR) $@

test-clean:
	$(RM) $(TEST_BUILD)/*.o
