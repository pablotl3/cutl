CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O0


SRC_DIR = examples
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
BIN = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC))


.PHONY: all run clean


all: $(BIN)


$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -I .


run: $(BIN)
	@-echo "\n" && ./bin/1_general_structure
	@-echo "\n" && ./bin/2_assertions
	@-echo "\n" && ./bin/3_special_functions
	@-echo "\n" && ./bin/4_error_handling


clean:
	rm -rf $(BIN_DIR)/*
