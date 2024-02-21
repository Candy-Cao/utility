#include <bits/stdc++.h>
using namespace std;

typedef list<int>::iterator iterType;
class LRUCache {
public:
    list<int> cache;
    map<int, iterType> hash;
    LRUCache() {};
    void put(int x) {
        if (hash.count(x) == 0) {
            cache.push_front(x);
            hash[x] = cache.begin();
        }
        else {
            iterType iter = hash[x];
            cache.erase(iter);
            cache.push_front(x);
            hash[x] = cache.begin();
        }
    }

    void print() {
        for (auto i = cache.begin(); i != cache.end(); i++) {
            cout << *i << (i != (--(cache.end())) ? " " : "\n");
        }
    }
};

int main() {
    LRUCache lru;
    int n = 0;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        lru.put(arr[i]);
    }
    lru.print();
    return 0;
}