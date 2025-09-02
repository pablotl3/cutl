CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O0


SRC_DIR = examples
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
BIN = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC))



.PHONY: all clean


all:
	@echo "Hello"
	$(foreach b,$(BIN),$(MAKE) $(b))



$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -I .


clean:
	rm -rf $(BIN_DIR)/*
