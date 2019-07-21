#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;


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
    if (!file.is_open())
        throw std::runtime_error("");

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




void BaseGraph::setup_recursion_matrix(int k)
{
    // std::cout << "method called" << std::endl;
    vertices.find(0)->second->block_bits = (1 << k) - 1;
    // std::cout << "base block: " << vertices.find(0)->second->block_bits << std::endl;
    for (int i = 1; i < vertices.size(); i++)
    {
        // std::cout << "for loop 1, iteration: " << i << std::endl;
        vertices.find(i)->second->block_bits = (vertices.find(i-1)->second->block_bits << k);
        // std::cout << vertices.find(i)->second->block_bits << std::endl;
    }

    int128_t temp = 1;
    for (int i = 0; i < vertices.size(); i++)
    {
        // std::cout << "for loop 2, iteration: " << i << std::endl;
        BaseVertex* current = vertices.find(i)->second;
        for (long name : current->neighbors)
        {
            current->adjacency_bits |= (temp << (name * k));
            // std::cout << current->adjacency_bits << std::endl;
        }
        // std::cout << "updating adjacency with self" << std::endl;
        current->adjacency_bits |= (temp << (current->name * k));
        // std::cout << current->adjacency_bits << std::endl;
    }


    for (int i = 0; i < vertices.size(); i++)
    {
        // std::cout << "for loop 3, iteration: " << i << std::endl;
        BaseVertex* current = vertices.find(i)->second;
        temp = current->adjacency_bits;

        for (int j = 0; j < k; j++)
        {
            // std::cout << "inner for loop 3, iteration: " << i << ", " << j << std::endl;
            recursion_matrix.push_back(temp | current->block_bits);
            // std::cout << "getting added to matrix: " << (temp | current->block_bits) << std::endl;
            // std::cout << "temp before shift: " << temp << std::endl;
            temp <<= 1;
            // std::cout << "temp after shift: " << temp << std::endl;
        }
    }
    // std::cout << "method returning" << std::endl;
}

ColoringGraph*
BaseGraph::
build_coloring_graph(int k)
{
    std::cerr << "generating ColoringGraph with k=" << k << std::endl;


    ColoringGraph* cg = new ColoringGraph(k, this);

    if (size())
        find_all_colorings(k, cg);

    return cg;    
}




void
BaseGraph::
find_all_colorings(int k, ColoringGraph* cg)
{
    setup_recursion_matrix(k);

    int128_t state[k * size()];
    int128_t assignment[k * size()];
    int vertex[k * size()];
    int color[k * size()];

    state[0] = (1 << (k * size())) -1;
    assignment[0] = 0;
    vertex[0] = 0;
    color[0] = -1;

    int128_t negation_gadget = ((1 << k * size()) - 1);

    int depth = 0;
    while (depth >= 0)
    {
        // std::cout << std::endl << "top of while loop, depth = " << depth
        //           << ", state = " << state[depth] << std::endl;
        color[depth]++;

        // std::cout << "trying vertex " << vertex[depth] << " with color " << color[depth] << std::endl;

        if (depth == size())
        {
            // std::cout << "1" << std::endl;
            cg->add_vertex(encode(assignment[depth], k));
            // std::cout << "coloring graph size: " << cg->size() << std::endl;
            depth--;

        }

        else if (color[depth] == k)
        {
            // std::cout << "2" << std::endl;
            depth--;
        }



        else if (bit_test(state[depth], vertex[depth] * k + color[depth]))
        {
            // std::cout << "3" << std::endl;
            int vertex_color_index = vertex[depth] * k + color[depth];

            state[depth + 1] = state[depth] & (recursion_matrix[vertex_color_index] ^ negation_gadget);
            assignment[depth + 1] = assignment[depth];
            bit_set(assignment[depth + 1], vertex_color_index);

            int next_vertex = pick_next_vertex(state[depth + 1], assignment[depth + 1], depth);
            if (next_vertex == -1)
            {
                depth--;
            }
            else
            {
                vertex[++depth] = next_vertex;
                color[depth] = -1;
            }
        }

    }
}

int
BaseGraph::
pick_next_vertex(int128_t state, int128_t assignment, int depth)
{
    return depth + 1;
}


long
BaseGraph::
encode(int128_t assignment, int k)
{
    int base = 1;
    long sum = 0;

    for (int i = 0; i < size(); i++)
    {
        for (int color = 0; color < k; color++)
        
        {
            if ((assignment & 1) == 1)
                sum += (color * base);
            assignment >>= 1;
        }
        base *= k;
    }
    return sum;
}


// void
// BaseGraph::
// find_all_colorings(int current, int k, ColoringGraph* cg,
//                    std::vector<int> coloring)
// {
//     while(true)
//     {
//         load_next_coloring(current, k, coloring);

//         if (coloring.at(current) >= k or current >= size())
//             break;

//         if (current == size()-1)
//             cg->add_vertex(encode(coloring, k));
//         else
//             find_all_colorings(current+1, k, cg, coloring);
//     }

// }

// void
// BaseGraph::
// load_next_coloring(int current, int k, std::vector<int>& coloring)
// {
//     while (true)
//     {
//         coloring[current]++;

//         if (coloring.at(current) > k)
//             return;

//         int i = 0;
//         while(i<size())
//         {
//             if (vertices.find(current)->second->neighbors.find(i)
//                 != vertices.find(current)->second->neighbors.end()
//                 && coloring.at(current) == coloring.at(i))
//                 {
//                     break;
//                     // std::cout << "conflict for current=" << current
//                     //           << " with color=" << coloring[current]
//                     //           << " and neighbor=" << i
//                     //           << " with color=" << coloring.at(i) << '\n';
//                 }
//             i++;
//         }

//         if (i >= size())
//             return;
//     }
// }


// long
// BaseGraph::
// encode(std::vector<int>& coloring, int k)
// {
//     long value = 0;
//     for (int i=0; i < size(); i++)
//         value = value*k + coloring.at(i);

//     return value;
// }


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

    return true and size();
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
    if (this->len-- > 0)
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


MetaGraph::
MetaGraph()
    : Graph<MetaVertex>()
{}


void
MetaGraph::
add_vertex(long name)
{
    MetaVertex* mv = new MetaVertex(name);
    vertices.insert(std::pair<long, MetaVertex*>(name, mv));
}


MetaVertex*
MetaGraph::
add_vertex()
{
    long name = size();
    add_vertex(name);
    return vertices[name];
}


// // template <typename V>
// void
// MetaGraph::
// add_vertex(MetaVertex* m)
// {
//     m->name = size();
// 	vertices.insert(std::pair<long, MetaVertex*>(m->name, m));
// }


// template <typename V>
void
MetaGraph::
remove_vertex(MetaVertex* m)
{
    std::unordered_set<long>::iterator it;
	for (it = m->neighbors.begin(); it != m->neighbors.end(); it++)
	{
        // std::cerr << "disconn. " << "\n";
		m->disconnect(vertices[*it]);
	}
    // std::cerr << "done removing all nbrs" << "\n";

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


ColoringGraph*
MetaGraph::
rebuild_partial_graph()
{
    ColoringGraph* cg = new ColoringGraph(colors, base);

    // first, survey metavertices to find out
    // 1. the largest sized vertex and
    // 2. if there are at least two distinct sizes of vertices

    // keep track of the largest (maximal) sized metavertex, this would
    // be the mothership
    int largest = 1;
    if (size())
        largest = get_some_vertex().size();
    // are there even two different vertices with not the same size?
    bool distinctsizes = false;
    for (auto& p : vertices)
    {
        MetaVertex* v = p.second;
        distinctsizes = (v->size() == largest) ? distinctsizes : true;
        largest = (v->size() > largest) ? v->size() : largest;
    }

    if (distinctsizes)
        for (auto& p : vertices)
        {
            MetaVertex* mv = p.second;
            if (mv->size() == largest)
                continue;
            for (const long& v : mv->vertices)
                cg->add_vertex(v);
        }

    return cg;
}



/*******************************************************************************
******************************** ALGORITHMS ************************************
*******************************************************************************/



MetaGraph*
ColoringGraph::
tarjans()
{
    MetaGraph* mg = Graph<ColoringVertex>::tarjans();
    mg->colors = colors;
    mg->base = base;

    return mg;
}


template <typename V>
MetaGraph*
Graph<V>::
tarjans()
{
    //*****************************
    // Declare helper variables and structures

    MetaGraph* mg =  new MetaGraph();

    std::cerr << "INFO: initialized empty metagraph" << std::endl;

    long next, root, child;
    typename std::list<long>::iterator current, found_cut_vertex;
    typename std::list<long> list;
    typename std::stack<MetaVertex*> cut_vertex_stack;
    typename std::set<MetaVertex*> cut_vertex_set;

    std::cerr << "INFO: initialized local variables" << std::endl;

    //*****************************
    // Main body of the method


    // For loop ensures all vertices
    // will be processed in case the
    // graph is disconnected
    for (auto& v : this->vertices)
    {
        std::cerr << std::endl << "INFO: processing vertex " << v.first
                  << " at line " << __LINE__ << std::endl;

        next = v.first;
        list.clear();
        while(!cut_vertex_stack.empty())
            cut_vertex_stack.pop();
        cut_vertex_set.clear();


        if (vertices[next]->depth == -1)
        {
            // If vertex has not been
            // visited, set up that
            // vertex as a root for DFS
            root = next;
            vertices[next]->depth = 0;
            list.push_back(next);
            current = list.begin();

            std::cerr << "INFO: vertices[root]->nt->hasnext()="
                      << vertices[root]->nt->hasnext() << " for root="
                      << *current
                      << "so entering block to create standalone MV "
                      << std::endl;

            if (!vertices[root]->nt->hasnext())
            {
                std::cerr << "INFO: !vertices[root]->nt->hasnext() "
                          << "so creating standalone MV " << root << std::endl;
                MetaVertex* rootmv = mg->add_vertex();
                rootmv->identity = root;
                rootmv->depth = vertices[root]->depth;
                rootmv->vertices.insert(root);
                continue;
                std::cerr << "INFO: SHOULD NEVER SEE THIS!!! PAST CONTINUE "
                          << std::endl;

            }


            std::cerr << "INFO: vertices[next]->depth == -1 "
                      << "so adding to the current state list" << std::endl;
        }
        else
            continue;


        while (true)
        {
            std::cerr << std::endl << "INFO: top of while loop; current="
                      << vertices[*current]->get_name() << '\t' << __LINE__
                      << std::endl;

            bool execif = true;
            try
            {
                std::cerr << "DEBUG: try to get next neighbor of "
                          << vertices[*current]->name
                          << " at line " << __LINE__ << "\n";
                child = vertices.find(vertices[*current]->get_next_neighbor())->first;
            }
            catch (std::out_of_range& e)
            {
                execif = false;
                std::cerr << "DEBUG: no more neighbors of "
                          << vertices[*current]->name
                          << " at line " << __LINE__ << "\n";
            }


            if (execif and vertices[child]->depth == -1)
            {
                // if the DFS found another child,
                // go down that path
                list.push_back(child);
                vertices[child]->parent = current;
                vertices[child]->depth = vertices[*current]->depth + 1;

                std::cerr << "INFO: new child " << child << " of vertex "
                          << vertices[*current]->get_name()
                          << ". depth of child set to "
                          << vertices[child]->depth << std::endl;

                current = list.end();
                current--;
            }

            else
            {
                vertices[*current]->lowpoint = std::min(
                        vertices[*current]->lowpoint,
                        vertices[child]->depth
                    );

                if (vertices[*current]->nt->hasnext())
                {
                    std::cerr << "INFO: " << vertices[*current]->name
                              << " might have more children; continue "
                              << " lowpoint set to "
                              << vertices[*current]->lowpoint
                              << " at line " << __LINE__ << "\n";
                    continue;
                }

                // Break if the root has no more children
                if (vertices[*current]->name == vertices[root]->name)
                    break;

                vertices[*vertices[*current]->parent]->lowpoint =
                    std::min(
                        vertices[*vertices[*current]->parent]->lowpoint,
                        vertices[*current]->lowpoint
                    );

                std::cerr << "`current` stats: "
                          << vertices[*current]->name << "\n"
                          << "\tlowpoint=" << vertices[*current]->lowpoint
                          << "\tdepth=" << vertices[*current]->depth
                          << std::endl;

                if (vertices[*vertices[*current]->parent] == vertices[root]
                    or vertices[*current]->lowpoint
                       >= vertices[*vertices[*current]->parent]->depth
                   )
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

                    std::cerr << "DEBUG: constructing a blank metavertex at "
                              << __LINE__ << "\n";
                    MetaVertex* main = mg->add_vertex();

                    // Splice the vertices from the DFS list
                    // into the component
                    // TODO
                    // main->vertices.splice(main->vertices.begin(),
                    //                       list,
                    //                       current,
                    //                       list.end());
                    main->vertices.insert(current, list.end());
                    // Also add the cut vertex itself
                    std::cerr << "DEBUG: add cut vertex " << *found_cut_vertex
                              << "to metavertex " << main->name << "at line "
                              << __LINE__ << "\n";
                    main->vertices.insert(*found_cut_vertex);


                    //**********************************************
                    // Connect component to cut vertices

                    // Any vertices on the stack with greater
                    // depth than the cut vertex in question
                    // were found after that cut vertex.
                    // Thus, they are part of the component.
                    // So we connect them to the component.

                    if (!cut_vertex_stack.empty())
                        std::cerr << "DEBUG: cut vertex stack top depth="
                                  << cut_vertex_stack.top()->depth
                                  << ", found cut vertex depth="
                                  << vertices[*found_cut_vertex]->depth
                                  << " before while loop at " << __LINE__
                                  << "\n";
                    while (!cut_vertex_stack.empty() and
                           // cut_vertex_stack.top()->depth
                           // > vertices[*found_cut_vertex]->depth)// and
                           main->vertices.find(cut_vertex_stack.top()->identity)
                           != main->vertices.end())
                    {
                        main->connect(cut_vertex_stack.top());
                        std::cerr << "INFO: connecting " << main->name
                                  << " and " << cut_vertex_stack.top()->name
                                  << "\n";

                        if (cut_vertex_stack.top()->identity
                            != *found_cut_vertex)
                            cut_vertex_stack.pop();
                        else
                            break;

                        std::cerr << "INFO: popping stuff from stack.\n";
                    }


                    // This if statement creates a MetaVertex
                    // object for the cut vertex if one
                    // does not already exist.
                    if (!cut_vertex_stack.empty() and
                         cut_vertex_stack.top()->identity ==
                          vertices[*found_cut_vertex]->name)
                    {
                        main->connect(cut_vertex_stack.top());
                    }
                    else
                    {
                        MetaVertex* cut = mg->add_vertex();

                        cut->identity = vertices[*found_cut_vertex]->name;
                        cut->depth = vertices[*found_cut_vertex]->depth;
                        cut->vertices.insert(vertices[*found_cut_vertex]->name);

                        main->connect(cut);

                        // Add the cut vertex to the stack
                        std::cerr << "INFO: adding MetaVertex " << cut->name
                                  << "to the stack at " << __LINE__ << "\n";
                        cut_vertex_stack.push(cut);
                    }

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

        int count = 0;
        vertices[root]->reset_neighbor_track();
        while (count < 2)
        {
            try
            {
                long nbr = vertices[root]->get_next_neighbor();
                if (*vertices[nbr]->parent == root)
                    count++;
            }
            catch (std::out_of_range& e)
            {
                break;
            }
        }

        if (count < 2 and size() > 1)
        {
            std::cerr << "INFO: count < 2" << std::endl;
            if (true or !cut_vertex_stack.empty())
            {
                MetaVertex* mv = cut_vertex_stack.top();
                std::cerr << "INFO: got metavrtx from cutvertex stack" << std::endl;

                std::cerr << "INFO: trying to remove" << std::endl;

                cut_vertex_stack.pop();
                mg->remove_vertex(mv);

                std::cerr << "INFO: done processing count < 2 case" << std::endl;
            }

        }

    } // end of main for-loop

    std::cerr << "INFO: about to return now" << std::endl;

    return mg;
}


#endif
