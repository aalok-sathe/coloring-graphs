#!/bin/bash


default: build

package: setup.py
	python3 setup.py sdist bdist_wheel

install: deps package
	echo "installing"
	python3 setup.py install --user

deps:
	python3 utils/install.py
	python3 -m pip install --user -r requirements.txt
	echo "please make sure you have SWIG installed"

build: cpp py

cpp:
	python3 setup.py build_ext --inplace
	#$(MAKE) -C "./libcolgraph" "build"

py:

test: build
	echo "running tests"
	python3 test.py #/graphtest.py

trigger:
	python3 utils/insertversion.py
	date | cat > .pipeline.trigger

clean: FORCE
	find . -name "*.pyc" -type f -delete
	find . -name "__pycache__" -type f -delete
	$(MAKE) -C "./libcolgraph" "clean"
	python3 setup.py clean
	rm -rf build dist *.egg-info


FORCE: ;
