CC=g++
CFLAGS=-Wall -Wextra -g -std=c++17
EXE=siv
OBJ=main.o
LIBS=-lsfml-graphics -lsfml-window -lsfml-system


.PHONY: all

all: $(EXE)

clean:
	rm $(EXE) $(OBJ)

run: $(EXE)
	./$(EXE) test.png

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

main.o: main.cpp
	$(CC) -c $(CFLAGS) $? -o $@