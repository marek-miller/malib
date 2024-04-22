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

RM	= rm -f
MKDIR	= mkdir -p
RMDIR	= rm -rf

AS	= nasm
ASFLAGS	= -f elf64 -g -F dwarf -w+all -w-reloc-rel-dword -I$(INCLUDE) -I$(SRC)

CC	= gcc
CFLAGS	= -Wall -Wextra -g -I$(INCLUDE)

AR	= ar
RANLIB	= ranlib
LD	= ld
LDFLAGS	=
LDLIBS	=

.PHONY: all clean

.DEFAULT: all

all: $(BUILD)/$(EXE) test-all

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
	$(RM) $(BUILD)/$(EXE) $(BUILD)/$(LIB)
	$(RMDIR) $(OBJ) $(BIN)


# Testing

TEST_BUILD	= $(BUILD)/$(TEST)
TEST_ASFLAGS	= $(ASFLAGS)
TEST_CFLAGS	= $(CFLAGS) -g -O0
TEST_LDFLAGS	= $(LDFLAGS)
TEST_LDLIBS	= $(LDLIBS) -lm

TEST_SUITE_01		= test_unit
TEST_SUITE_01_SRCS	= test_unit.s
TEST_SUITE_01_OBJS	= $(TEST_SUITE_01_SRCS:%.s=$(TEST_BUILD)/%.o)

TEST_SUITE_02		= test_api
TEST_SUITE_02_SRCS	= test_api.c
TEST_SUITE_02_OBJS	= $(TEST_SUITE_02_SRCS:%.c=$(TEST_BUILD)/%.o)

.PHONY: test test-all test-clean

test: test-all
	@echo -n  $(TEST_BUILD)/$(TEST_SUITE_01)": "
	@$(TEST_BUILD)/$(TEST_SUITE_01) && echo OK || echo FAIL

	@echo -n  $(TEST_BUILD)/$(TEST_SUITE_02)": "
	@$(TEST_BUILD)/$(TEST_SUITE_02) && echo OK || echo FAIL

test-all: $(addprefix $(TEST_BUILD)/,$(TEST_SUITE_01) $(TEST_SUITE_02))

$(TEST_BUILD)/$(TEST_SUITE_01): $(TEST_SUITE_01_OBJS) $(BUILD)/$(LIB)
	$(LD) $(TEST_LDFLAGS) $^ -o $@

$(TEST_BUILD)/$(TEST_SUITE_02): $(TEST_SUITE_02_OBJS) $(BUILD)/$(LIB)
	$(CC) $(TEST_LDFLAGS) $^ -o $@ $(TEST_LDLIBS)

$(TEST_BUILD)/%.o: $(TEST)/%.s | $(TEST_BUILD)
	$(AS) $(TEST_ASFLAGS) $< -o $@

$(TEST_BUILD)/%.o: $(TEST)/%.c | $(TEST_BUILD)
	$(CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_BUILD):
	$(MKDIR) $@

test-clean:
	$(RMDIR) $(TEST_BUILD)
