/*
  link: https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-queries-on-the-graph/problem
*/

#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
//#define int         int64_t

using namespace std;

const int N = 1e5 + 7;
const int inf = 1e9 + 1;
typedef pair<int, int> pii;

int lab[N], num[N], low[N];
pii e[N];
bool del[N], bridge[N];
vector<int> adj[N];
int n, m, q, u, v, Time;

int find(int u) {return lab[u] < 0? u: lab[u] = find(lab[u]);}
void join(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    if(lab[u] > lab[v]) swap(lab[u], lab[v]);
    lab[u] += lab[v], lab[v] = u;
}

void dfs(int u) {
    num[u] = low[u] = ++Time;
    for(int& i: adj[u]) {
        if(del[i]) continue;
        int v = e[i].fi ^ e[i].se ^ u;
        del[i] = 1;
        if(num[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= num[v]) bridge[i] = 1;
            else join(u, v);
        } else {
            join(u, v);
            low[u] = min(low[u], num[v]);
        }
    }
}

struct TTree {
    vector<vector<int>> adj, p;
    vector<int> st, in, out, h, par, cost;
    vector<pii> val;
    int n, lgN, cnt;
    TTree(int n = 0): n(n) {
        h.resize(n + 2);
        adj.resize(n + 2);
        in.resize(h.size());
        out.resize(h.size());
        par.resize(h.size());
        lgN = log2(n) + 3; cnt = 0;
        p.resize(n + 2, vector<int>(lgN, 0));
        cost.resize(h.size());
    }
    void add(int u, int v) {
        adj[u].pb(v), adj[v].pb(u);
    }
    void dfs(int u) {
        in[u] = ++cnt;
        for(int i = 1; i < lgN; ++i) p[u][i] = p[p[u][i - 1]][i - 1];
        for(int v: adj[u]) {
            if(v == p[u][0]) continue;
            h[v] = h[u] + 1;
            p[v][0] = u;
            dfs(v);
        }
        out[u] = cnt;
    }
    int LCA(int u, int v) {
        if(h[u] < h[v]) swap(u, v);
        for(int i = lgN - 1; i >= 0; --i)
            if(h[u] - (1 << i) >= h[v])
                u = p[u][i];
        if(u == v) return u;
        for(int i = lgN - 1; i >= 0; --i)
            if(p[u][i] != p[v][i])
                u = p[u][i], v = p[v][i];
        return p[u][0];
    }
    int isPar(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }
    int get(int u, int v, int x, int y) {
        val = {pii(in[u], u), pii(in[v], v), pii(in[x], x), pii(in[y], y)};
        sort(val.begin(), val.end());
        for(int i = 1; i < 4; ++i) {
            cnt = LCA(val[i].se, val[i - 1].se);
            val.pb(in[cnt], cnt);
        }
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());
        st.clear();
        for(auto& cur: val) {
            while(st.size() && out[st.back()] < cur.fi) st.pop_back();
            if(st.size()) par[cur.se] = st.back(), cost[cur.se] = h[cur.se] - h[st.back()];
            else par[cur.se] = -1;
            st.pb(cur.se);
        }
        int res = 0, cur, nxt, a = LCA(u, v), b = LCA(x, y);
        cur = u;
        while(cur != a) cost[cur] = 0, cur = par[cur];
        cur = v;
        while(cur != a) cost[cur] = 0, cur = par[cur];
        cur = x;
        while(cur != b) res += cost[cur], cur = par[cur];
        cur = y;
        while(cur != b) res += cost[cur], cur = par[cur];
        for(auto& cur: val) par[cur.se] = -1, cost[cur.se] = 0;
        return res;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> m >> q;
    fill(lab, lab + n + 1, -1);
    for(int i = 0; i < m; ++i) {
        cin >> u >> v;
        e[i] = pii(u, v);
        adj[u].pb(i), adj[v].pb(i);
    }
    dfs(1);
    fill(low, low + n + 1, -1);
    Time = 0;
    for(int i = 1; i <= n; ++i) {
        if(low[find(i)] == -1) low[find(i)] = ++Time;
        low[i] = low[find(i)];
    }
    TTree tree(Time);
    for(int i = 0; i < m; ++i) {
        if(bridge[i]) {
            e[i].fi = low[e[i].fi], e[i].se = low[e[i].se];
            tree.add(e[i].fi, e[i].se);
        }
    }
    tree.dfs(1);
    int x, y;
    while(q --) {
        cin >> u >> v >> x >> y;
        u = low[u], v = low[v], x = low[x], y = low[y];
        cout << tree.get(u, v, x, y) << '\n';
    }
}
