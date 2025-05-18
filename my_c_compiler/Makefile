CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/lexer.c src/parser.c src/ast.c
OBJ = $(SRC:.c=.o)
EXEC = build/compiler.exe

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build directory
clean:
	del /f /q $(OBJ) $(EXEC)

# Rule to run the compiled program
run: $(EXEC)
	./$(EXEC) test/input.c
