#!/bin/bash


default: build


install: deps build
	echo "installing"
	echo '# Added by libcolgraph (https://github.com/aalok-sathe/coloring-graphs)'
	echo "export PYTHONPATH=$(PWD):$(PYTHONPATH)" >> ~/.bashrc
	echo "export PYTHONPATH=$(PWD):$(PYTHONPATH)" >> ~/.bash_profile
	source ~/.bashrc
	source ~/.bash_profile

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
	PYTHONDONTWRITEBYTECODE=True python3 test/graphtest.py

clean: FORCE
	find . -name "*.pyc" -type f -delete
	find . -name "__pycache__" -type f -delete
	$(MAKE) -C "./libcolgraph/libcc" "clean"
	# python3 setup.py clean
	# rm -rf build dist *.egg-info


FORCE: ;
