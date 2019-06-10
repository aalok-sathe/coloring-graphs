
#include <iostream>
#include <cstdlib>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "before init!" << endl;

    char* testpath = "../../test/input/g1.in";

    BaseGraph g;

    cout << "loading graph from " << testpath << endl;
    g.load_txt(testpath);

    g.Tarjans();

    cout << "graph size: " << g.size() << endl;

    cout << "reached EOF tester" << endl;

    return 0;
}
