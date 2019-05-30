## install via pip

    python3 -m pip install libcolgraph

## manual installation instructions

1. install [`swig`](http://swig.org/)

2. clone the repository
  - `git clone https://github.com/aalok-sathe/coloring-graphs`

3. go into the repository
  - `cd coloring-graphs`

4. make
  - `make` and use within the directory (or use by adding directory to `PYTHONPATH`)
    ```bash
    $ python3
    >>> import libcolgraph
    >>> g = libcolgraph.BaseGraph()
    ```
    
    ```bash
    $ python3 test.py
    ```
    
  OR
  - `make install` to install system-wide for your user
