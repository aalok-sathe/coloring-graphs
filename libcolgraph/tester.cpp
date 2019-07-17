
#include <iostream>
#include <cstdlib>
#include "Graph.h"


#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;

int main(int argc, char *argv[])
{
    cout << "before init!" << endl;

    // char* testpath = "../test/input/g1.in";
    // char* testpath = "../in/square.in";
    // char* testpath = "../in/smolgraph.in";
    // char* testpath = "../in/hexmod.in";
    // char* testpath = "../in/line.in";
    // char* testpath = "../in/3ring.in";
    // char* testpath = "../in/3star.in";
    // char* testpath = "../in/polypbg.in";
    // char* testpath = "../in/polypbgtriangle.in";
    // char* testpath = "../in/floatingedge.in";
    char* testpath = "../in/triangle.in";


    BaseGraph* bg = new BaseGraph();

    cout << "loading graph from " << testpath << endl;
    bg->load_txt(testpath);

    cout << "graph size: " << bg->size() << endl << endl;

    cout << "building matrix. k=? " << endl << endl;
    int k;
    cin >> k;

    bg->setup_recursion_matrix(k);
    // int bitsize = 32;
    // for (int i = 0; i < bg->vertices.size()*k; i++)
    // {
    //     int128_t temp = bg->recursion_matrix[i];

    //     for (int j = 0; j< bitsize; j++)
    //     {
    //         cout << (temp >> (bitsize-1-j)) % 2;
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    ColoringGraph* cg = bg->build_coloring_graph(k);

    cout << "coloring graph size: " << cg->size() << endl;

    cout << "reached EOF tester" << endl;

    // MetaGraph* mbg = bg->tarjans();

    // cout << "metagraph size: " << mbg->size() << endl;

    // for (auto& p : mbg->vertices)
    // {
    //     MetaVertex* mv = p.second;
    //     std::cout << "\nmetavertex " << mv->get_name()
    //               << " contents: " << "\t";
    //     for (long v : mv->vertices)
    //         std::cout << v << ' ';
    // }
    // std::cout << "\n";

    return 0;
}


































