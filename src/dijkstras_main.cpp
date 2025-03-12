#include "dijkstras.h"

int main(int argc, char const *argv[])
{
    string file_name = argv[1];
    Graph graph;
    file_to_graph(file_name, graph);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);
    for (int i = 0; i < graph.numVertices; ++i)
        print_path(extract_shortest_path(distances, previous, i), distances[i]);
    return 0;
}
