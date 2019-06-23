## coloring-graphs
[![pipeline status](https://aalok-sathe.gitlab.io/coloring-graphs/build.svg?v=2825177572518850315)](https://gitlab.com/aalok-sathe/coloring-graphs/)

a coloring graphs library written in C++ for speedy computation and wrapped in
Python for ease of development and extension!

### what
this library provides support to construct graphs, their coloring graphs, and
biconnected component metagraphs.
a coloring graph is a graph representing all the valid colorings of a graph.
each vertex of a coloring graph represents a coloring of the base graph.
two colorings are considered adjacent if they differ in only one vertex's color.

in this project, we represent a coloring as an integer, which, when converted to
base k (for a k-coloring), is a number of length |V| and represents the vertex-wise
colors [0,k) for each vertex.

the library is under development, being written using Python and C/C++.
the web application uses the library to provide useful GUI for quick drawing and
graph construction.
in the future, we plan to develop a supplemental subsection of the library containing
useful graph algorithms and ability to run simulations to test structural graph theoretic
conjectures about graph coloring and coloring graphs.
for documentation, feel free to take a look inside `libcolgraph/` and read the docstrings.
for questions, reach out.

### screenshot of the web GUI

  [Clockwise]
  A 7 vertex BaseGraph that is a hexagon with a central vertex and a missing 'spoke'
  leads to a quite complex ColoringGraph with k=4 colors. You can see the formation of
  polyps at the edges. The structure of the resultant ColoringGraph is shown in the
  Meta ColoringGraph produced by a run of modified Tarjan's algorithm for biconnected
  components. The central 'mothership' can be seen, adjacent to which there are cut
  vertices, and finally the stray singular coloring vertices at the tips of polyps.

  <img src="https://i.imgur.com/TusisoA.png" />


### usage
- as a module

  plot a BaseGraph, its ColoringGraph, and the Meta
  ColoringGraph generated by Tarjans. you would need to
  have a graph formatted in an adjacency matrix file.
  opens plots in new browser windows.

  basic usage:
  ```
    colgraphplot [PATH_TO_FILE] [-k COLORS]
    ---
    options:
      usage: colgraphplot [-h] [-k COLORS] [-v] [--no-bg] [--no-cg] [--no-mbg]
                     [--no-mcg]
                     INPUT_GRAPH

      positional arguments:
        INPUT_GRAPH           read in BaseGraph from adjacency matrix file

      optional arguments:
        -h, --help            show this help message and exit
        -k COLORS, --colors COLORS
                              number of colors to use to create ColoringGraph
        -v, --verbosity       set output verbosity
        --no-bg               hide BaseGraph?
        --no-cg               hide ColoringGraph?
        --no-mbg              hide meta BaseGraph?
        --no-mcg              hide meta ColoringGraph?
  ```

  launch web GUI [WIP]:
  ```
    colgraphweb [OPTIONS]
  ```
  currently under development.



- as a library

    ```python
    import libcolgraph

    bg = libcolgraph.BaseGraph()
    bg.load_txt('./in/hexmod.in')

    cg = bg.build_coloring_graph(4)

    print('bg {} led to a cg {}'.format(bg, cg))

    for v in cg.get_vertices():
        # do something
        pass
    ```


### installation

- for installation from source
    refer to [detailed install instructions](INSTALL.md)


- [pypi](https://pypi.org/project/libcolgraph/)

    ```bash
    python3 -m pip install libcolgraph [--user] [--upgrade]
    ```

    things to note:
    - currently a binary wheel is available only for [`manylinux`](https://www.python.org/dev/peps/pep-0513/)
      distributions e.g. centOS, Debian family, RedHat family, etc.
    - if your distribution is not `manylinux`-supported, then pip
      will need to compile locally using `swig` and `setuptools`.
      in that case, make sure you have `setuptools` and
      [swig](http://www.swig.org/download.html) installed, as they
      will be needed for compilation.
    - in the future we will release wheels for MacOS as well. these
      might not be as frequently maintained, however, so your best
      bet would be to compile locally using `swig`.


### contribute

see [contributing guide](CONTRIBUTING.md)

### help

full documentation coming soon


### who

Coloring Graphs lab, University of Richmond. Multiple contributors.
(C) 2017-2019
