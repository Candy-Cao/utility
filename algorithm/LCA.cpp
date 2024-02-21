#include <bits/stdc++.h>
using namespace std;

class LCA {
public:
    int n;
    int root;
    int num;
    vector<int> depth;
    vector<vector<int>> parent;

    LCA(vector<vector<int>> graph, int _root):
        n(graph.size()),
        root(_root),
        num(static_cast<int>(ceil(log2(n)))),
        depth(n, 0),
        parent(num, vector<int>(n, -1))
    {
        queue<int> q;
        q.push(root);
        // bfs求出parent数组的第一行，以及depth数组
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u: graph[v]) {
                if (u == parent[0][v]) {
                    continue;
                }
                parent[0][u] = v;
                depth[u] = depth[v] + 1;
                q.push(u);
            }
        }
        //接下来通过倍增计算parent数组剩余部分
        for (int k = 0; k < num - 1; k++) {
            for (int i = 0; i < n; i++) {
                if (parent[k][i] == -1) {
                    parent[k + 1][i] = -1;
                }
                else {
                    parent[k + 1][i] = parent[k][parent[k][i]];
                }
            }
        }
    }

    int getLCA(int u, int v) {
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        for (int k = 0; k < num; k++) {
            if ((depth[v] - depth[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if (u == v) {
            return u;
        }
        for (int k = num - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};


//还有一个tarjan算法可以用离线的方式计算lca;参考灵神leetcode2646题解。