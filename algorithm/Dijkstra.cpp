#include <bits/stdc++.h>
using namespace std;

//G:所有权都为正数的带权连通简单图,求出所有顶点到起点的最短距离；
//若顶点u, v之间没有边，graph[u][v] = graph[v][u] = MAXN;
//graph[u][u] = 0
#define MAXN 100000
vector<int> Dijkstra(vector<vector<int>> &graph, int index) {
    int n = graph.size();
    vector<int> book(n, 0);
    int count = 0;
    vector<int> dist(n, MAXN);
    dist[index] = 0;

    while (count < n) {
        int near_po = -1;
        int distance = MAXN;
        for (int u = 0; u < n; u++) {
            if (!book[u] && dist[u] < distance) {
                distance = dist[u];
                near_po = u;
            }
        }
        if (near_po == -1) {
            break;
        }
        book[near_po] = 1;

        for (int v = 0; v < n; v++) {
            if (!book[v] && graph[near_po][v] != MAXN) {
                dist[v] = min(dist[v], graph[near_po][v] + dist[near_po]);
            }
        }
        count++;
    }
    return dist;
}


// 定义一个表示无穷大的常数，用于初始化距离数组
const int INF = INT_MAX;

// 使用邻接矩阵表示图
class Graph {
public:
    Graph(int vertices);
    void addEdge(int source, int destination, int weight);
    void dijkstra(int source);

private:
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix;
};

Graph::Graph(int vertices) : vertices(vertices) {
    // 初始化邻接矩阵，所有边的权重设为无穷大
    adjacencyMatrix.resize(vertices, std::vector<int>(vertices, INF));
}

void Graph::addEdge(int source, int destination, int weight) {
    // 添加边
    adjacencyMatrix[source][destination] = weight;
    adjacencyMatrix[destination][source] = weight;  // 如果是有向图，则不需要这行
}

void Graph::dijkstra(int source) {
    std::vector<int> distance(vertices, INF);  // 存储从源点到各顶点的最短距离
    std::vector<bool> visited(vertices, false);  // 标记顶点是否已访问

    // 源点到自身的距离为0
    distance[source] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        int minDistance = INF;
        int minVertex;

        // 选取未访问的顶点中距离最小的顶点
        for (int j = 0; j < vertices; ++j) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                minVertex = j;
            }
        }

        visited[minVertex] = true;

        // 更新距离数组
        for (int k = 0; k < vertices; ++k) {
            if (!visited[k] && adjacencyMatrix[minVertex][k] != INF) {
                int newDistance = distance[minVertex] + adjacencyMatrix[minVertex][k];
                if (newDistance < distance[k]) {
                    distance[k] = newDistance;
                }
            }
        }
    }

    // 输出最短路径
    std::cout << "Vertex\tDistance from Source" << std::endl;
    for (int i = 0; i < vertices; ++i) {
        std::cout << i << "\t" << distance[i] << std::endl;
    }
}

int main() {
    vector<vector<int>> graph {
        {0, 4, MAXN, 2, MAXN, MAXN},
        {4, 0, 3, MAXN, 3, MAXN},
        {MAXN, 3, 0, MAXN, MAXN, 2},
        {2, MAXN, MAXN, 0, 3, MAXN},
        {MAXN, 3, MAXN, 3, 0, 1},
        {MAXN, MAXN, 2, MAXN, 1, 0}
        };
    auto dist = Dijkstra(graph, 0);
    for (auto d: dist) {
        cout << d << " ";
    }
    cout << endl;
    return 0;
}