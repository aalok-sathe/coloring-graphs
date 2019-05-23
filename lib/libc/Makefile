# makefile
# use to compile and test the assembler ASM for the STACK computer and
# its various components

DEBUG_FLAG= #-g -Wall
CFLAGS= #-g -Wall

.SUFFIXES: .cpp .o

.cpp.o:
	g++ $(CFLAGS) -c $<

TESTER: tester.o Graph.o Vertex.o
	g++ -o TESTER Graph.o Vertex.o

Graph.o: Vertex.h Graph.h

Vertex.o: Vertex.h

brute:
	g++ *.cpp

clean:
	/bin/rm -f main *.o core
