#include <bits/stdc++.h>
using namespace std;


// 树状数组模板（维护前缀最大值）
class BIT {
    vector<long long> tree;
public:
    BIT(int n) : tree(n, LLONG_MIN) {}

    void update(int i, long long val) {
        while (i < tree.size()) {
            tree[i] = max(tree[i], val);
            // tree[i] += val 维护前缀和
            i += i & -i;
        }
    }

    long long pre_max(int i) {
        long long res = LLONG_MIN;
        while (i > 0) {
            res = max(res, tree[i]);
            // res += tree[i] 维护前缀和
            i &= i - 1;
        }
        return res;
    }
};

