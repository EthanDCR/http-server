# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude -L/usr/local/lib -lraylib -lm -lpthread -ldl -lGL

# Source and executable
SRC = $(wildcard src/*.c)
EXEC = bin/$(shell basename "$(PWD)")

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Target to run the game
run: $(EXEC)
	./$(EXEC)

# Clean up build files
clean:
	rm -f $(EXEC)
