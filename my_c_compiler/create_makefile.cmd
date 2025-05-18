@echo off
echo Generating Makefile...

(
    echo CC = gcc
    echo CFLAGS = -Wall -Iinclude
    echo SRC = src/main.c src/lexer.c src/parser.c
    echo OUT = build/compiler.exe
    echo.
    echo all: $(OUT)
    echo.
    echo $(OUT): $(SRC)
    echo ^	if not exist build mkdir build
    echo ^	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
    echo.
    echo run: all
    echo ^	$(OUT) test/input.c
    echo.
    echo clean:
    echo ^	del /q build\*.exe
) > Makefile

echo Makefile created successfully.
