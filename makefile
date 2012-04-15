all: simul
		./simul

simul: simul.o block.o buffer.o test_for_distribution.o outputs.o
	g++ simul.o block.o buffer.o test_for_distribution.o outputs.o -o simul

simul.o: simul.cpp block.h buffer.h test_for_distribution.h
	g++ -std=c++0x -c simul.cpp

outputs.o: outputs.cpp outputs.h
	g++ -std=c++0x -c outputs.cpp

test_for_distribution.o: test_for_distribution.cpp test_for_distribution.h
	g++ -std=c++0x -c test_for_distribution.cpp

block.o: block.cpp block.h
	g++ -std=c++0x -c block.cpp
	
buffer.o: buffer.cpp buffer.h block.h
	g++ -std=c++0x -c buffer.cpp