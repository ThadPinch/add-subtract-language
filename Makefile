# Makefile

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c99 -I include

# Source Files
SRC = src/main.c src/lexer.c src/parser.c src/ast.c src/codegen.c

# Object Files
OBJ = src/main.o src/lexer.o src/parser.o src/ast.o src/codegen.o

# Executable Name
TARGET = simple_compiler

# Default Target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compilation Rules
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Up
clean:
	rm -f $(OBJ) $(TARGET) output.c

# Phony Targets
.PHONY: all clean
