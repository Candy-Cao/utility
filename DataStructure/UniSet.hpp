#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000
class UniSet {
public:
    UniSet() {
        for (int i = 1; i < arr.size(); i++) {
            arr[i] = i;
        }
    }
    int getParent(int ind) {
        if (arr[ind] == ind) {
            return ind;
        }
        return arr[ind] = getParent(arr[ind]);
    }
    void merge(int i, int j) {
        int pi = getParent(i);
        int pj = getParent(j);
        arr[pj] = pi;
    }
    void init(vector<vector<int>> &paths) {
        for (auto &path: paths) {
            merge(path[0], path[1]);
        }
    }
private:
    array<int, MAXN> arr;
};