//
// Created by Alex on 28.05.2019.
//
//Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
//Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.


#include <vector>
#include <set>
#include <utility>
#include <list>
#include <iostream>
#include <climits>

using std::vector;
using std::set;
using std::pair;
using std::make_pair;
using std::list;
using std::cin;
using std::cout;

using  Edges = pair<unsigned int , unsigned int>;

class Graph {
public:
    explicit Graph(unsigned _size);
    void addEdge(unsigned from, unsigned to, unsigned weight);
    void Relax(unsigned vertex, vector<Edges> &vertices) const;
    unsigned getSize() const;

private:
    unsigned size;
    vector<list<Edges>> edges;
};

int Dijkstra(Graph const &graph, int from, int to) {

    vector<bool> used(graph.getSize(), false);
    vector<unsigned> path(graph.getSize(), INT_MAX);

    path[from] = 0;
    set<Edges> queue;
    queue.emplace(make_pair(0, from));

    while (!queue.empty()) {
        unsigned int v = (queue.begin())->second;
        queue.erase(queue.begin());
        used[v] = true;

        // Релаксация
        vector<Edges> paths;
        graph.Relax(v, paths);
        for (Edges c : paths) {
            if (path[c.first] > path[v] + c.second) {
                if (path[c.first] != INT_MAX)
                    queue.erase(make_pair(path[c.first], c.first));
                path[c.first] = path[v] + c.second;
                queue.emplace(pair<int, int>(path[c.first], c.first));
            }
        }
    }

    return ((path[to] != INT_MAX) ? (static_cast<int>(path[to])) : (-1));
}

int main() {
    std::ios::sync_with_stdio(false);
    unsigned int n;
    unsigned int m;
    cin >> n >> m;
    Graph graph(n);
    for (unsigned int i = 0; i < m; i++) {
        unsigned int s;
        unsigned int t;
        unsigned int w;
        cin >> s >> t >> w;
        graph.addEdge(s, t, w);
    }
    unsigned from;
    unsigned to;
    cin >> from >> to;

    cout << Dijkstra(graph, from, to);

    return 0;
}

Graph::Graph(unsigned int _size) :
        size(_size),
        edges(_size, list<Edges>()) {}


void Graph::addEdge(unsigned from, unsigned to, unsigned weight)
{
    edges[from].push_back(make_pair(to, weight));
    edges[to].push_back(make_pair(from, weight));
}


unsigned Graph::getSize() const
{
    return size;
}


void Graph::Relax(unsigned vertex, vector<Edges> &vertices) const
{
    vertices.clear();
    for (const Edges &i : edges[vertex])
        vertices.push_back(i);
}