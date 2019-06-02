//
// Created by Alex on 28.05.2019.
//
//Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
//Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

#include <vector>
#include <queue>
#include <list>
#include <iostream>

using std::vector;
using std::queue;
using std::list;
using std::cin;
using std::cout;

class Graph{
public:
    Graph(unsigned int verticesNumber);
    void addEdge(int from, int to);
    void getNextVertices(int vertex, vector<int> & vertices) const;
    int countPaths(int from, int to);

private:
    struct Vertex{
        int depth;
        int paths;
    };

    unsigned int verticesNumber;

    vector<list<int> > out;
};

int main()
{
    unsigned int v;
    cin >> v;
    Graph graph(v);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        graph.addEdge(a, b);
    }

    int from;
    int to;
    cin >> from >> to;
    cout << graph.countPaths(from, to);
}


Graph::Graph(unsigned int verticesNumber): verticesNumber(verticesNumber), out(verticesNumber)
{}

void Graph::addEdge(int from, int to)
{
    for(int i : out[from])
        if(i == to)
            return;

    out[to].push_back(from);
    out[from].push_back(to);
}

void Graph::getNextVertices(int vertex, vector<int> & vertices) const
{
    for(int i : out[vertex])
        vertices.push_back(i);
}

int Graph::countPaths(int from, int to)
{
    vector<Vertex> condition(verticesNumber);
    queue<int> q;
    q.push(from);
    condition[from].paths = 1;

    while(!q.empty()){
        vector<int> nextVertices;
        int v = q.front();
        q.pop();
        getNextVertices(v, nextVertices);

        for(int i : nextVertices){
            if(condition[i].paths == 0){
                q.push(i);
                condition[i].depth = condition[v].depth + 1;
                condition[i].paths = condition[v].paths;
            }
            else if(condition[i].depth == condition[v].depth + 1){
                condition[i].paths += condition[v].paths;
            }
        }
    }
    return condition[to].paths;
}
