CC      = gcc
SRC     = ./src
BIN     = ./bin
CFLAGS  = -I./include -Wall -Wextra

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)
TARGET = mysh

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CC) $(OBJS) -o $(TARGET)

$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -f $(BIN)/*

.PHONY: all clean