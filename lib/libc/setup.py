#!/usr/bin/env python3
# setup.py

from distutils.core import setup, Extension

example_module = Extension('_example', sources=['example.i',
                                                'example.c'])

if __name__ == '__main__':
    setup(name='example', ext_modules=[example_module], py_modules=['example'])
