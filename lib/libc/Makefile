# makefile
# use to compile and test the assembler ASM for the STACK computer and
# its various components

DEBUG_FLAG= -g -Wall
CFLAGS= -std=gnu++11 -g -Wall

.SUFFIXES: .cpp .o

.cpp.o:
	g++ $(CFLAGS) -c $<

TESTER: tester.o Graph.o Vertex.o
	g++ -o TESTER tester.o Graph.o Vertex.o

Graph.o: Graph.h Vertex.h

Vertex.o: Vertex.h

brute:
	g++ $(CFLAGS) *.cpp

clean:
	/bin/rm -f main *.o core
