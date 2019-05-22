#!/bin/bash

install: deps
	echo "installing"

deps:
	python3 -m pip install --user -r requirements.txt

test: clean
	echo "running tests"
	PYTHONDONTWRITEBYTECODE=True python3 test/graphtest.py

clean: FORCE
	find . -name "*.pyc" -type f -delete
	find . -name "__pycache__" -type f -delete


FORCE:
