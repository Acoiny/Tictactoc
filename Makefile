BINARY := tictactoc

NAME := $(BINARY)

$(shell mkdir -p bin/release)

CFLAGS = -Wall -Wextra -Werror -std=c++23 -finline-functions -march=native -Wno-unused-parameter -O3

INCFLAGS = -I hdr

SRC = $(wildcard src/*.cpp)

OBJ = $(patsubst src/%.cpp,bin/release/%.o,$(SRC))

LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system



all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

bin/release/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) $(OBJ)
