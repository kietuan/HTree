CXX = g++
FLAG = -pedantic-errors -Werror -Wall -Wextra -Weffc++ -g -O0
file =

standard:
	$(CXX)  -I . -std=c++11 $(file).cpp -o $(file).o
	./$(file).o
	rm $(file).o

all: 
	$(CXX)  $(FLAG) -I . -std=c++11 main.cpp ConcatStringTree.cpp -o main.o
	./main.o
	rm main.o


run: main
	./main

test: test.cpp
	$(CXX) $(FLAG)  -std=c++11 test.cpp -o test.o
	./test.o

clean:
	rm *.o
