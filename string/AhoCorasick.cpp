/*
  spoj 's problem
*/
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

typedef pair<int, int> pii;
const int N = int(2e3) + 7;
const int L = 1 << 17 | 1;

struct TNode {
    bool seen;
    int matchFail, fail;
    vector<int> matches;
    map<char, int> nxt;
    TNode() {
        seen = matchFail = fail = 0;
        matches.clear(); nxt.clear();
    }
    TNode(int matchFail, int fail): matchFail(matchFail), fail(fail) {}
} trie[L];
string t, s;
int n, ans[N], numNode = 0, root;

void Add(string s, int ID) {
    int ptr = root;
    for(char c: s) {
       int& cur = trie[ptr].nxt[c];
       if(cur == 0) cur = ++numNode;
       ptr = cur;
    }
    trie[ptr].matches.pb(ID);
}

int Target(int x, char c) {
    while(x && !trie[x].nxt.count(c)) x = trie[x].fail;
    return x ? trie[x].nxt[c]: root;
}

void Build() {
    queue<int> Q;
    for(Q.push(root); !Q.empty(); Q.pop()) {
        int top = Q.front();
        for(map<char, int>::iterator it = trie[top].nxt.begin(); it != trie[top].nxt.end(); ++it) {
            char c = it -> fi;
            int ptr = it -> se, f;
            trie[ptr].fail = f = Target(trie[top].fail, c);
            trie[ptr].matchFail = trie[f].matches.empty()? trie[f].matchFail: f;
            Q.push(ptr);
        }
    }
}

void Search(string s) {
    int cur = root;
    for(auto c: s) {
        cur = Target(cur, c);
        for(int ptr = cur; ptr && !trie[ptr].seen; ptr = trie[ptr].matchFail) {
            trie[ptr].seen = 1;
            for(int x: trie[ptr].matches) ans[x] = 1;
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    root = ++numNode; cin >> t >> n;
    for(int i = 1; i <= n; ++i) cin >> s, Add(s, i);
    Build(), Search(t);
    for(int i = 1; i <= n; ++i) cout << (ans[i] == 0? "N\n": "Y\n");
}
