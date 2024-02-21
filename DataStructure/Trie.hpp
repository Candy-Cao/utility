#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 26

struct Node {
    Node* childs[MAX_SIZE] = {};
    int isEnd = -1; //-1标志非叶节点
};

class Trie {
    Node root;
    int cnt = 0;
    void dfs(Node *r) {
        if (!r) {
            return ;
        }
        for (auto *c: r->childs) {
            dfs(c);
        }
        delete r;
    }
public:
    ~Trie() {
        for (auto *c: root.childs) {
            dfs(c);
        }
    }
    inline int norm(char x) { return x - 'a'; }
    int add(const string &s) {
        auto *pcur = &root;
        for (int i = 0; i < s.length(); i++) {
            if (!pcur->childs[norm(s[i])]) {
                pcur->childs[norm(s[i])] = new Node;
            }
            pcur = pcur->childs[norm(s[i])];
        }
        if (pcur->isEnd < 0) {
            pcur->isEnd = cnt++;
        }
        return pcur->isEnd;
    }

    int find(const string &s) {
        auto *pcur = &root;
        for (int i = 0; i < s.length(); i++) {
            if (!pcur->childs[norm(s[i])]) {
                return -1;
            }
            pcur = pcur->childs[norm(s[i])];
        }
        return pcur->isEnd;
    }
};
