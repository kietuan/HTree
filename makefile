CXX = g++
FLAG = -pedantic-errors -Werror -Wall -Wextra -Weffc++ -g -O0 -std=c++11
file =

one:
	$(CXX)  -I . $(FLAG) main.cpp -o main.o
	./main.o
	rm $(file).o

all: 
	$(CXX)  -I . $(FLAG) *.cpp -o main.o
	./main.o
	rm $(file).o


run: main
	./main

clean:
	rm *.o
