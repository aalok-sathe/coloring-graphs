
# coding: utf-8

# In[ ]:


import matplotlib
matplotlib.use('TKAgg')
from matplotlib import pyplot as plt

from tqdm import tqdm
import networkx as nx


# In[ ]:


from libcolgraph import *


# ### Let's define some functions to generate particular kinds of graphs

# #### 1. 'wheel graph' (n): 
# this kind of graph has $n$ vertices, one of them a 'central' vertex. $n-1$ vertices form a ring, and the central vertex connects to each of the $n-1$ vertices to complete the spokes of the wheel.

# In[ ]:


def wheelgraph(n):       
    '''
    this kind of graph has $n$ vertices, one of them a 'central' vertex. $n-1$ vertices form a ring, 
    and the central vertex connects to each of the $n-1$ vertices to complete the spokes of the wheel.
    g = BaseGraph()     
    for i in range(n):                                            
        g.add_vertex(i)                                          
    for a, b in zip(range(n), [n-1, *range(n-1)]):                         
        if a != b: g.make_edge(*sorted([a, b]))                      
        g.add_vertex(n)                                                  
    for i in range(n):  
        if i != n: g.make_edge(i, n)
    return g
    '''
    g = BaseGraph()
    g.load_from_nx(nx.wheel_graph(n))
    return g


# #### 2. wheel with one missing spoke

# In[ ]:


def wheelgraphmissingspoke(n):       
    '''
    this kind of graph has $n$ vertices, one of them a 'central' vertex. $n-1$ vertices form a ring, 
    and the central vertex connects to each of the $n-1$ vertices to complete the spokes of the wheel.
    '''
    g = BaseGraph()     
    for i in range(n):                                            
        g.add_vertex(i)                                          
    for a, b in zip(range(n), [n-1, *range(n-1)]):                         
        if a != b: g.make_edge(*sorted([a, b]))                      
        g.add_vertex(n)                                                  
    for i in range(1, n):  
        if i != n: g.make_edge(i, n)
    return g


# #### 3. n-dimensional hypercube: 

# In[ ]:


def hypercubegraph(n):
    '''
    n-dimensional hypercube
    '''
    g = BaseGraph()
    g.load_from_nx(nx.hypercube_graph(n))
    return g


# ### Now we'll create a convenient way to generate sequences

# In[ ]:


def make_sequence(graphgen, *args, k=3, low=3, high=15, **kwargs):
    '''
    a function that accepts a graph generating function to generate the appropriate basegraph for parameter
    n from low to high, and then calls 'build_coloring_graph' on it with parameter k, the number of colors 
    '''
    for n in tqdm(range(low, high)):
        g = graphgen(n, *args, **kwargs)
        c = g.build_coloring_graph(k)
        yield len(c)


# ### Time for some test runs!

# Let's look at the sequence of ColoringGraph sizes (graph of vertex colorings) of 'wheel' graphs with
# 4 colors

# In[ ]:


wheel3 = [*make_sequence(wheelgraph, k=3, low=1, high=27)]


# In[ ]:


wheel3


# In[ ]:


get_ipython().magic('matplotlib inline')
plt.plot(range(3, 20), wheel3, 'bo-.')


# In[ ]:


wheel4 = [*make_sequence(wheelgraph, k=4, low=3, high=14)]


# In[ ]:


wheel4


# As you might figure out with some searching, this corresponds to [OEIS::A090860](http://oeis.org/A090860)
# with the description: 
# 
# _Number of ways of 4-coloring a map in which there is a central circle surrounded by an annulus divided into n-1 regions. There are n regions in all._

# In[ ]:


get_ipython().magic('matplotlib inline')
plt.plot(range(3, 14), wheel4, 'bo-.')


# The 5-color analogue of this isn't listed on OEIS (yet). Let us generate it anyway:

# In[ ]:


wheel5 = [*make_sequence(wheelgraph, k=5, low=3, high=12)]


# In[ ]:


wheel5


# As you might observe if you actually tried running this notebook, this is pretty time consuming to compute, so we will avoid computing the sequence to a longer length and stick to few terms. If you have plenty of time and compute power, feel free to play around with it for longer to get more terms of the sequence.

# In[ ]:


get_ipython().magic('matplotlib inline')
plt.plot(range(3, 12), wheel5, 'bo-.')


# In[ ]:


cube3_3 = [*make_sequence(hypercubegraph, k=3, low=0, high=6)]


# In[ ]:


cube3_3


# In[ ]:


get_ipython().magic('matplotlib inline')
plt.plot(range(6), cube3_3, 'bo-.')

