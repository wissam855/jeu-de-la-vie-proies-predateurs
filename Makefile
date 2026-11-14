# Makefile du projet : jeu de la vie proies/predateurs
# make       : compile le programme
# make run   : compile puis lance le programme
# make clean : efface les fichiers de compilation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXE = simulation

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -f src/*.o $(EXE) $(EXE).exe

.PHONY: run clean
