CC      = gcc
SRC     = ./src
BIN     = ./bin
TESTS   = ./tests
TEST_LIB = ./tlib
CFLAGS  = -I./include -Wall -Wextra

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)

TEST_SRCS = $(wildcard $(TESTS)/*.c)
TEST_OBJS = $(TEST_SRCS:$(TESTS)/%.c=$(BIN)/%.o)

TLIB_SRCS = $(wildcard $(TEST_LIB)/*.c)
TLIB_OBJS = $(TLIB_SRCS:$(TEST_LIB)/%.c=$(BIN)/%.o)

TARGET = mysh
TEST = test_mysh

# Makes everything besides tests
all: $(TARGET) test

test: $(TEST)

$(TARGET): $(OBJS) | $(BIN)
	$(CC) $(OBJS) -o $(TARGET)

$(TEST): $(TEST_OBJS) $(TLIB_OBJS) $(filter-out $(BIN)/main.o, $(OBJS)) | $(BIN)
	$(CC) $^ -o $@

$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(TESTS)/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(TEST_LIB)/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -f $(BIN)/* $(TEST) 

.PHONY: all clean test