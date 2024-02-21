#include <iostream>
#include <vector>
#include <climits>

/*cop from chatGPT, to be confirm*/
const int INF = INT_MAX;

class Graph {
public:
    Graph(int vertices);
    void addEdge(int source, int destination, int weight);
    void primMST();

private:
    int vertices;
    std::vector<std::vector<int>> graph;
};

Graph::Graph(int vertices) : vertices(vertices) {
    graph.resize(vertices, std::vector<int>(vertices, 0));
}

void Graph::addEdge(int source, int destination, int weight) {
    graph[source][destination] = weight;
    graph[destination][source] = weight;  // 如果是无向图，则需要这行
}

void Graph::primMST() {
    std::vector<int> parent(vertices, -1);  // 用于存储最小生成树的父节点
    std::vector<int> key(vertices, INF);    // 用于存储顶点的权重
    std::vector<bool> inMST(vertices, false); // 用于标记顶点是否在最小生成树中

    key[0] = 0; // 选择第一个顶点作为起始点

    for (int count = 0; count < vertices - 1; ++count) {
        int u = -1; // 用于选择顶点
        for (int v = 0; v < vertices; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < vertices; ++v) {
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // 输出最小生成树的边
    std::cout << "Edge\tWeight" << std::endl;
    for (int i = 1; i < vertices; ++i) {
        std::cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << std::endl;
    }
}

int main() {
    int vertices = 5;
    Graph graph(vertices);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 4, 6);
    graph.addEdge(3, 4, 7);

    std::cout << "Minimum Spanning Tree:" << std::endl;
    graph.primMST();

    return 0;
}
