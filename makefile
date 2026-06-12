# find OS
ifeq ($(OS), Windows_NT)
	PLATFORM := Windows
	EXE := .exe
	DEL := rmdir /s /q
	MKDIR := mkdir
	SHELL := cmd.exe
else
	UNAME_S := $(shell uname -s 2>/dev/null)
	ifeq ($(UNAME_S), Linux)
		PLATFORM := Linux
		DEL := rm -rf
		MKDIR := mkdir -p
	else
		PLATFORM := Unknown
		DEL :=
		MKDIR :=
	endif
endif

# initial color
ifeq ($(PLATFORM), Windows)
	GREEN :=
	RED :=
	RESET :=
else
	GREEN  := $(shell tput -Txterm setaf 2)
	RED := $(shell tput -Txterm setaf 1)
	RESET := $(shell tput -Txterm sgr0)
endif

CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP
ASFLAGS = $(CFLAGS)
LDFLAGS =

SRC_DIR = src
OUT_DIR = out

# platform specific setting
ifeq ($(PLATFORM), Windows)
	TARGET := $(OUT_DIR)/calculator.exe
	SRC_S := $(filter-out $(SRC_DIR)/calculate_asm.S, $(wildcard $(SRC_DIR)/*.S))
else
	TARGET = $(OUT_DIR)/calculator
	SRC_S := $(filter-out $(SRC_DIR)/calculate_asm_win.S, $(wildcard $(SRC_DIR)/*.S))
endif

# C source code
SRCS_C := $(filter-out $(SRC_DIR)/t_%.c, $(wildcard $(SRC_DIR)/*.c))

# object files
OBJS_C := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS_C)) 
OBJS_S := $(patsubst $(SRC_DIR)/%.S, $(OUT_DIR)/%.o, $(SRC_S))
OBJS := $(OBJS_C) $(OBJS_S)

DEPS := $(OBJS:.o=.d)

# test file
TEST_SRCS := $(wildcard $(SRC_DIR)/t_*.c)
TEST_BINS := $(patsubst $(SRC_DIR)/t_%.c, $(OUT_DIR)/t_%$(EXE), $(TEST_SRCS))

TEST_DEPS := $(filter-out $(OUT_DIR)/main.o, $(OBJS))

.PHONY: all run test clean

all: $(TARGET)

# create out/ directory
$(OUT_DIR):
	$(MKDIR) $(OUT_DIR)

# link all object file to binary file
$(TARGET): $(OBJS) | $(OUT_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# compile .c -> .o
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# compile .S -> .o
$(OUT_DIR)/%.o: $(SRC_DIR)/%.S | $(OUT_DIR)
	$(CC) $(ASFLAGS) -c $< -o $@

# build test binary file
$(OUT_DIR)/t_%$(EXE): $(SRC_DIR)/t_%.c $(TEST_DEPS) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@

ifeq ($(PLATFORM), Windows)
test: $(TEST_BINS)
	@setlocal EnableDelayedExpansion & \
	set pass=0& set fail=0& \
	for %%t in ($(subst /,\,$(TEST_BINS))) do ( \
		echo --- RUN %%t --- & \
		%%t & \
		(if !errorlevel! equ 0 ( set /a pass+=1 & echo  PASS ) else ( set /a fail+=1 & echo  FAIL )) & \
		echo --- END %%t --- & \
		echo. \
	) & \
	echo ------------------------------ & \
	echo result: !pass! passed, !fail! failed & \
	cmd /c exit !fail!
run: $(TARGET)
	$(subst /,\,$(TARGET))
else
test: $(TEST_BINS)
	@echo ""
	@pass=0; fail=0; \
	for t in $(TEST_BINS); do \
		echo "--- RUN $$t ---"; \
		if ./$$t; then \
			echo "$(GREEN) PASS$(RESET)"; pass=$$((pass+1)); \
		else \
			echo "$(RED) FAIL$(RESET) (exit $$?)"; fail=$$((fail+1)); \
		fi; \
		echo "--- END $$t ---"; \
		echo ""; \
	done; \
	echo "------------------------------"; \
	echo "result: $$pass passed, $$fail failed"; \
	[ $$fail -eq 0 ]
run: $(TARGET)
	./$(TARGET)
endif

-include $(DEPS)

# clear all output file
clean:
	$(DEL) $(OUT_DIR)
