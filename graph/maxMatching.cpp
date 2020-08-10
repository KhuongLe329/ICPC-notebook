#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

const int N = (int)202;
typedef pair<int, int> pii;

struct MaxMatching {
    int nx, ny;
    vector<vector<int>> adj;
    vector<int> S, match, lv;
    bool found;
    MaxMatching() {}
    MaxMatching(int nx, int ny): nx(nx), ny(ny), adj(nx + 1), match(ny + 1), lv(ny + 1) {}
    void add(int x, int y) {adj[x].pb(y);}
    bool layering() {
        fill(lv.begin(), lv.end(), 0);
        queue<int> q;
        for(int x: S) {
            for(int y: adj[x])
                if(lv[y] == 0) lv[y] = 1, q.push(y);
        }
        for(; q.size(); q.pop()) {
            int y = q.front(), x, lvy = lv[y] + 1;
            if((x = match[y]) == 0) return 1;
            for(int y: adj[x])
                if(lv[y] == 0) lv[y] = lvy, q.push(y);
        }
        return 0;
    }
    void augmentmatching(int x, int lvx) {
        for(int y: adj[x]) {
            if(lv[y] == lvx + 1) {
                lv[y] = 0;
                if(match[y] == 0) found = 1;
                else augmentmatching(match[y], lvx + 1);
                if(found) {match[y] = x; return;}
            }
        }
    }
    int get() {
        for(int i = 1; i <= nx; ++i) S.pb(i);
        while(layering()) {
            for(auto it = S.rbegin(); it != S.rend(); ++it) {
                found = 0;
                augmentmatching(*it, 0);
                if(found) *it = S.back(), S.pop_back();
            }
        }
        return nx - (int)S.size();
    }
};

int n, m, x, y, id[N][33], node[2];
vector<int> v[N];

void ListPrime(int x, vector<int>& v) {
    for(int i = 2; i * i <= x; ++i) {
        while(x % i == 0) x /= i, v.pb(i);
    }
    if(x > 1) v.pb(x);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        cin >> x;
        ListPrime(x, v[i]);
        for(int j = 0; j < int(v[i].size()); ++j) id[i][j] = ++node[i & 1];
    }
    MaxMatching g(node[1], node[0]);
    for(int i = 1; i <= m; ++i) {
        cin >> x >> y;
        if(y & 1) swap(x, y);
        for(int j = 0; j < (int)v[x].size(); ++j) {
            for(int k = 0; k < (int)v[y].size(); ++k) {
                if(v[x][j] == v[y][k]) g.add(id[x][j], id[y][k]);
            }
        }
    }
    cout << g.get();
}
