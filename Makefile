# Makefile du projet : jeu de la vie proies/predateurs
# make          : compile le programme
# make run      : compile puis lance le programme
# make test     : lance tous les tests de tests/
# make valgrind : verifie la memoire (Linux ou WSL)
# make clean    : efface les fichiers de compilation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXE = simulation

# pour les tests : tous les modules sauf main.c
LIB_SRC = $(filter-out src/main.c, $(SRC))
TESTS = $(wildcard tests/test_*.c)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

# compile et lance chaque fichier tests/test_*.c ; s'arrête au premier échec
test:
	@for t in $(TESTS); do \
		echo "== $$t"; \
		$(CC) $(CFLAGS) $$t $(LIB_SRC) -o test_bin || exit 1; \
		./test_bin || exit 1; \
	done
	@echo "== Tous les tests sont OK"

# vérification de la mémoire (Linux ou WSL, valgrind n'existe pas sous Windows)
valgrind: $(EXE)
	valgrind --leak-check=full --error-exitcode=1 ./$(EXE)

clean:
	rm -f src/*.o $(EXE) $(EXE).exe test_bin test_bin.exe

.PHONY: run test valgrind clean
