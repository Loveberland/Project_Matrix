# write by claude

GREEN  := $(shell tput -Txterm setaf 2)
RED := $(shell tput -Txterm setaf 1)
RESET  := $(shell tput -Txterm sgr0)

CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP
ASFLAGS = $(CFLAGS)
LDFLAGS =

TARGET = $(OUT_DIR)/calculator
SRC_DIR = src
OUT_DIR = out

# source code
SRCS_C := $(filter-out $(SRC_DIR)/t_%.c, $(wildcard $(SRC_DIR)/*.c))
SRCS_S := $(wildcard $(SRC_DIR)/*.S)

# object file
OBJS_C := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS_C))
OBJS_S := $(patsubst $(SRC_DIR)/%.S, $(OUT_DIR)/%.o, $(SRCS_S))
OBJS := $(OBJS_C) $(OBJS_S)

DEPS := $(OBJS:.o=.d)

# test file
TEST_SRCS := $(wildcard $(SRC_DIR)/t_*.c)
TEST_BINS := $(patsubst $(SRC_DIR)/t_%.c, $(OUT_DIR)/t_%, $(TEST_SRCS))

TEST_DEPS := $(filter-out $(OUT_DIR)/main.o, $(OBJS))

.PHONY: all run test clean

all: $(TARGET)

# create out/ directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

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
$(OUT_DIR)/t_%: $(SRC_DIR)/t_%.c $(TEST_DEPS) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# run all test file
test: $(TEST_BINS)
	@echo ""
	@pass=0; fail=0; \
	for t in $(TEST_BINS); do \
		echo "--- $$t ---"; \
		if ./$$t; then \
			echo "$(GREEN) PASS$(RESET)"; pass=$$((pass+1)); \
		else \
			echo "$(RED) FAIL$(RESET) (exit $$?)"; fail=$$((fail+1)); \
		fi; \
		echo ""; \
	done; \
	echo "------------------------------"; \
	echo "result: $$pass passed, $$fail failed"; \
	[ $$fail -eq 0 ]

# run 
run: $(TARGET)
	./$(TARGET)

-include $(DEPS)

# clear all output file
clean:
	rm -rf $(OUT_DIR)
