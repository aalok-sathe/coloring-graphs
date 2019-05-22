#!/bin/bash

install: deps
	echo "installing"

deps:
	python3 -m pip install --user -r requirements.txt

test: FORCE
	echo "running tests"
	python3 test/graphtest.py


FORCE:
