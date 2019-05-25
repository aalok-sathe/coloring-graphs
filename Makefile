#!/bin/bash


default: build

package: setup.py
	python3 setup.py sdist bdist_wheel

install: deps package
	echo "installing"
	python3 setup.py install

deps:
	python3 utils/install.py
	python3 -m pip install --user -r requirements.txt
	echo "please make sure you have SWIG installed"

build: cpp py

cpp:
	$(MAKE) -C "./libcolgraph/libcc" "build"

py:

test: clean
	echo "running tests"
	python3 test/graphtest.py

clean: FORCE
	find . -name "*.pyc" -type f -delete
	find . -name "__pycache__" -type f -delete
	$(MAKE) -C "./libcolgraph/libcc" "clean"
	python3 setup.py clean
	rm -rf build dist *.egg-info


FORCE: ;
