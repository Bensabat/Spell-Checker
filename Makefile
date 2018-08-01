CXX      = g++
CXXFLAGS = -Wextra -Wall -pedantic -std=c++14

SRC  = david/src/main.cc david/src/node.cc david/src/damereau-levenshtein.cc
EXEC = TextMiningCompiler

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

rm:
	rm $(EXEC) $(EXEC2)