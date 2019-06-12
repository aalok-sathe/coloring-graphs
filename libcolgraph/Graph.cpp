#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"


/*******************************************************************************
***************************** GRAPH ********************************************
*******************************************************************************/

template <typename V>
Graph<V>::
Graph() {}


template <typename V>
Graph<V>::
~Graph() {}


template <typename V>
long
Graph<V>::
size()
{
    return vertices.size();
}


template <typename V>
V&
Graph<V>::
get_vertex(long name)
{
    return *vertices.at(name);
}


template <typename V>
V&
Graph<V>::
get_some_vertex()
{
    for (auto& pair : vertices)
        return *pair.second;
    throw std::out_of_range("graph is empty");
}


template <typename V>
const GraphVertexIterator<V>*
Graph<V>::
get_vertices()
{
    if (true)
        throw std::logic_error("not implemented");
    return __iter__();
}


template <typename V>
const GraphVertexIterator<V>*
Graph<V>::
__iter__()
{
    if (true)
        throw std::logic_error("not implemented");
    return new GraphVertexIterator<V>({ vertices.begin(), size() });
}

/*******************************************************************************
***************************** BASEGRAPH ****************************************
*******************************************************************************/


BaseGraph::
BaseGraph()
    : Graph<BaseVertex>()
{}


void
BaseGraph::
add_vertex(long name)
{
    BaseVertex* v = new BaseVertex(name);
    this->vertices.insert(std::pair<long, BaseVertex*>(name, v));
}


void
BaseGraph::
make_edge(long a, long b)
{
    typename std::unordered_map<long, BaseVertex*>::iterator it;
    BaseVertex * va, * vb;

    it = vertices.find(a);
    if (it != vertices.end())
        va = it->second;
    else
        throw std::out_of_range("");

    it = vertices.find(b);
    if (it != vertices.end())
        vb = it->second;
    else
        throw std::out_of_range("");

    vb->add_neighbor(*va);
    va->add_neighbor(*vb);
}


void
BaseGraph::
load_txt(char* path)
{
    std::ifstream file(path);
    int n;
    file >> n;

    for (int i=0; i<n; i++)
        this->add_vertex((long)i);

    int value;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            file >> value;
            if (value)
                vertices[i]->add_neighbor(*vertices[j]);
        }
}


ColoringGraph*
BaseGraph::
build_coloring_graph(int k)
{
    // TODO: make recursive backtracking based search
    ColoringGraph* cg = new ColoringGraph(k, this);
    for (long coloring=0; coloring<pow(k, size()); coloring++)
        if (is_valid_coloring(coloring, k))
            cg->add_vertex(coloring);
        else
            continue;

    return cg;
}


int
BaseGraph::
get_vertex_color(long coloring, long name, int k)
{
    return (coloring / (long)pow(k, (size()-name-1))) % k;
}


bool
BaseGraph::
is_valid_coloring(long coloring, int k)
{
    for (auto& pair : vertices)
    {
        long vname = pair.first;
        int vcol = get_vertex_color(coloring, vname, k);

        BaseVertex* v = pair.second;
        for (auto it = v->neighbors.begin(); it != v->neighbors.end(); it++)
            if (vcol == get_vertex_color(coloring, *it, k))
                return false;
    }

    return true;
}


const BaseGraphVertexIterator*
BaseGraph::
get_vertices()
{
    return __iter__();
}


const BaseGraphVertexIterator*
BaseGraph::
__iter__()
{
    return new BaseGraphVertexIterator(vertices.begin(), size());
}


/*******************************************************************************
***************************** COLORINGGRAPH ************************************
*******************************************************************************/


ColoringGraph::
ColoringGraph(int k, BaseGraph* bg)
    : colors(k), base(bg)
{
    for (int i=0; i<bg->size(); i++)
    {
        std::vector<long> v;
        for (int j=0; j<colors; v.push_back(j++*pow(colors, i)));
        precompexp.push_back(v);
    }
}


void
ColoringGraph::
add_vertex(long name)
{
    ColoringVertex* vertex = new ColoringVertex(name, colors, this);
    vertices.insert(std::pair<long, ColoringVertex*>(name, vertex));
}


const ColoringGraphVertexIterator*
ColoringGraph::
get_vertices()
{
    return __iter__();
}


const ColoringGraphVertexIterator*
ColoringGraph::
__iter__()
{
    return new ColoringGraphVertexIterator(vertices.begin(), size());
}


/*******************************************************************************
***************************** GraphVertexIterator*******************************
*******************************************************************************/


template <typename V>
V
GraphVertexIterator<V>::
next()
{
    if (this->len--)
        return *(this->it++->second);

    throw std::out_of_range("");
}


template <typename V>
V
GraphVertexIterator<V>::
__next__()
{
    return this->next();
}


template <typename V>
bool
GraphVertexIterator<V>::
hasnext()
{
    return (this->len > 0);
}


template <typename V>
GraphVertexIterator<V>*
GraphVertexIterator<V>::
__iter__()
{
    return this;
}



/*******************************************************************************
********************************** MetaGraph ***********************************
*******************************************************************************/


// template<>
// Graph<MetaVertex>::
// ~Graph()
// {};


// template <typename V>
void
MetaGraph::
add_vertex(MetaVertex* m)
{
    m->name = size();
	vertices.insert(std::pair<long, MetaVertex*>(m->name, m));
}


// template <typename V>
void
MetaGraph::
remove_vertex(MetaVertex* m)
{
	for (auto& n : m->neighbors)
	{
		m->disconnect(vertices[n]);
	}

	vertices.erase(m->name);
}


const MetaGraphVertexIterator*
MetaGraph::
get_vertices()
{
    return __iter__();
}


const MetaGraphVertexIterator*
MetaGraph::
__iter__()
{
    return new MetaGraphVertexIterator(vertices.begin(), size());
}



/*******************************************************************************
******************************** ALGORITHMS ************************************
*******************************************************************************/


template <typename V>
MetaGraph*
Graph<V>::tarjans()
{

    //*****************************
    // Declare helper variables and structures

    MetaGraph* mg =  new MetaGraph();

    long next, root, child;
    typename std::list<long>::iterator current, found_cut_vertex;
    typename std::list<long> list;
    typename std::stack<MetaVertex*> cut_vertex_stack;

    //*****************************
    // Main body of the method


    // For loop ensures all vertices
    // will be processed in case the
    // graph is disconnected
    for (auto& v : this->vertices)
    {
        next = v.first;
        list.clear();
        while(!cut_vertex_stack.empty())
            cut_vertex_stack.pop();

        if (vertices[next]->depth == -1)
        {
            // If vertex has not been
            // visited, set up that
            // vertex as a root for DFS
            root = next;
            vertices[next]->depth = 0;
            list.push_back(next);
            current = list.begin();
        }

        while (true)
        {

            child = vertices.find(vertices[*current]->get_next_neighbor())->first;

            if (vertices[child]->depth == -1)
            {
                // if the DFS found another child,
                // go down that path
                list.push_back(child);
                vertices[child]->parent = current;
                vertices[child]->depth = vertices[*current]->depth + 1;
                current++;
            }

            else
            {
                // if (current->hasNext())
                // {
                //     current->lowpoint = std::min(current->lowpoint, child->depth);
                //     break;
                // }

                // Break if the root has no more children
                if (vertices[*current]->name == vertices[root]->name)
                    break;

                vertices[*vertices[*current]->parent]->lowpoint =
                    std::min(
                        vertices[*vertices[*current]->parent]->lowpoint,
                        vertices[*current]->lowpoint
                    );

                if (vertices[*vertices[*current]->parent] == vertices[root]
                    or vertices[*current]->lowpoint
                       >= vertices[*vertices[*current]->parent]->depth
                   )
                // if ((*current)->parent->name == root-name ||
                //     (*current)->lowpoint >= (*current)->parent->depth)
                {
                    // If DFS ever gets back to the
                    // root, everything left in the list
                    // is a biconnected component.
                    // OR
                    // If the parent is a cut vertex,
                    // everything in the list after current
                    // is a biconnected component.




                    //**********************************************
                    // Create biconnected component


                    // Store this since we'll be using it a lot
                    found_cut_vertex = vertices[*current]->parent;

                    // This MetaVertex will store all vertices
                    // in the biconnected component
                    MetaVertex* main = new MetaVertex();

                    // Splice the vertices from the DFS list
                    // into the component
                    // TODO
                    main->vertices.splice(main->vertices.begin(),
                                          list,
                                          current,
                                          list.end());
                    // Also add the cut vertex itself
                    main->vertices.push_back(*found_cut_vertex);



                    //**********************************************
                    // Connect component to cut vertices

                    // Any vertices on the stack with greater
                    // depth than the cut vertex in question
                    // were found after that cut vertex.
                    // Thus, they are part of the component.
                    // So we connect them to the component.
                    while (cut_vertex_stack.top()->depth
                           > vertices[*found_cut_vertex]->depth)
                    {
                        main->connect(cut_vertex_stack.top());
                        cut_vertex_stack.pop();
                    }


                    // This if statement creates a MetaVertex
                    // object for the cut vertex if one
                    // does not already exist.
                    if (cut_vertex_stack.top()->name != vertices[*found_cut_vertex]->name)
                    {
                        MetaVertex* cut = new MetaVertex(vertices[*found_cut_vertex]);
                        mg->add_vertex(cut);
                        main->connect(cut);
                        // Add the cut vertex to the stack
                        cut_vertex_stack.push(cut);
                    }

                    else
                    {
                        main->connect(cut_vertex_stack.top());
                    }

                    // Add the new component to the MetaGraph
                    mg->add_vertex(main);

                    // The cut vertex is the parent,
                    // so we return the DFS to it
                    current = found_cut_vertex;
                }

                else
                {
                    current = vertices[*current]->parent;
                }

            }

        } // end of while-loop

        ////////////////////////
        // Reset root nt (current will be the root)
        // while root has next neighbor
        //  count++
        // if count < 2
        //  remove from metagraph and disconnect from all neighbors
        //  (root metavertex will be on top of the cut vertex stack)
        ////////////////////////

    } // end of main for-loop

    return mg;
}





#endif
