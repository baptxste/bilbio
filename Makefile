FLAGS = -Wall -std=c++11 -g
BINDIR = bin/
SRCDIR = src/
SRC = $(wildcard $(SRCDIR)*.cpp)
OBJ = $(patsubst src/%.cpp, bin/%.o, $(SRC))

all: ./myprogram

myprogram: $(OBJ)
	g++ $(FLAGS) -o myprogram $(OBJ)

bin/%.o: $(SRCDIR)%.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)*.o ./myprogram