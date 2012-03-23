all: simul
	./simul

simul: simul.o block.o buffer.o
	g++ simul.o block.o buffer.o -o simul

simul.o: simul.cpp block.h buffer.h
	g++ -std=c++0x -c simul.cpp

block.o: block.cpp block.h
	g++ -std=c++0x -c block.cpp
	
buffer.o: buffer.cpp buffer.h block.h
	g++ -std=c++0x -c buffer.cpp