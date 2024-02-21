#include <bits/stdc++.h>
using namespace std;

// 若u, v 之间不存在边，g[u][v] = INF;
// g[u][u] = 0;
#define INF 999999999

void Floyd(vector<vector<int>> &g) {
    int n = g.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][k] + g[k][j] < g[i][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}