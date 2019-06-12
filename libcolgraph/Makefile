#!/bin/bash

####################################
########      MAKEFILE      ########
####################################


##################
####   DEFS   ####

DEBUG_FLAG= -g -Wall
CFLAGS= -std=gnu++11 -g -Wall
PYTHON = "python3"
MODULE_TARGETS = $("PYTHON ./generate_targets.py")


##################
####   BUILD  ####

default: TESTER

## CPP

.SUFFIXES: .cpp .o

.cpp.o:
	g++ $(CFLAGS) -c $<

TESTER: tester.o Graph.o Vertex.o
	g++ -o TESTER tester.o Graph.o Vertex.o

Graph.o: Graph.h Vertex.h GraphTemplates.h

Vertex.o: Vertex.h GraphTemplates.h


## SWIG

build: buildc buildpy clean_nonessential

buildc: $(wildcard MODULE_TARGETS) setup.py
	$(PYTHON) setup.py build_ext --inplace
	# $(PYTHON) setup.py install

buildpy: setup.py


##################
####   TEST   ####

test: FORCE
	./TESTER
	$(PYTHON) test.py


##################
#### CLEANUP  ####

clean: clean_nonessential clean_cpp FORCE
	rm -rf *.so

clean_nonessential: FORCE
	rm -rf build *wrap.c* __pycache__

clean_cpp: FORCE
	/bin/rm -f main *.o *.out TESTER core


##################
####   DUMMY  ####

FORCE: ;
