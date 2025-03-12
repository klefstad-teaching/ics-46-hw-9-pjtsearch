#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous)
{
    int n = G.numVertices;
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);
    previous = vector(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    distances[source] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        for (auto neighbor : G[u])
        {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int> &distances, const vector<int> &previous, int destination)
{
    deque<int> res;
    int curr = destination;
    res.push_front(curr);
    while (previous[curr] != -1)
    {
        curr = previous[curr];
        res.push_front(curr);
    }
    return {res.begin(), res.end()};
}

void print_path(const vector<int> &v, int total)
{
    for (auto vertex : v)
    {
        cout << vertex << " ";
    }
    cout << endl
         << "Total cost is " << total << endl;
}