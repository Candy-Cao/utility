#include <bits/stdc++.h>
using namespace std;

int *buildNext(const char *P) {
    size_t m = strlen(P), j = 0;
    int *next = new int[m];
    int t = next[0] = -1;
    while (j < m - 1) {
        if (t < 0 || P[j] == P[t]) {
            t++;
            j++;
            next[j] = P[j] == P[t] ? next[t] : t;
        }
        else {
            t = next[t];
        }
    }
    return next;
}

int match(const char *T, const char *P) {
    int *next = buildNext(P);
    int n = (int)strlen(T), i = 0;
    int m = (int)strlen(P), j = 0;
    while (j < m && i < n) {
        if (j < 0 || T[i] == P[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    delete[] next; 
    return i - j;
}

vector<int> calc_max_match(string s) {
    vector<int> match(s.length());
    int c = 0;
    for (int i = 1; i < s.length(); i++) {
        char v = s[i];
        while (c && s[c] != v) {
            c = match[c - 1];
        }
        if (s[c] == v) {
            c++;
        }
        match[i] = c;
    }
    return match;
}

// KMP 模板
// 返回 text 中出现了多少次 pattern（允许 pattern 重叠）
int kmp_search(string text, string pattern) {
    vector<int> match = calc_max_match(pattern);
    int match_cnt = 0, c = 0;
    for (int i = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v) {
            c = match[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        if (c == pattern.length()) {
            match_cnt++;
            c = match[c - 1];
        }
    }
    return match_cnt;
}


int main() {
    string P = "dsf", T = "cdsddfdsf";
    cout << "please input a pattern string:";
    getline(cin, P);
    cout << "please input a target string:";
    getline(cin, T);
    cout << "first positon(begin from 0) of match is: " << match(T.c_str(), P.c_str()) << endl;
    return 0;
}