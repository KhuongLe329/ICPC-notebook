/*
  duathon APIO 2018
*/
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
//#define int         int64_t

using namespace std;

const int N = 2e5 + 7;
const int inf = 1e9 + 1;
typedef pair<int, int> pii;

int num[N], low[N];
pii e[N];
bool del[N];
vector<int> adj[N], st, g[N];
int n, m, Time, cnt, overall, sz[N];

void dfs(int u) {
    num[u] = low[u] = ++Time;
    st.pb(u);
    for(int& i: adj[u]) {
        if(del[i]) continue;
        int v = e[i].fi ^ e[i].se ^ u;
        del[i] = 1;
        if(num[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= num[u]) {
                g[u].pb(++cnt);
                while(1) {
                    int tmp = st.back(); st.pop_back();
                    g[cnt].pb(tmp);
                    if(tmp == v) break;
                }
            }
        } else low[u] = min(low[u], num[v]);
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
    cin >> n >> m;
    for(int u, v, i = 0; i < m; ++i) {
        cin >> u >> v;
        e[i] = pii(u, v);
        adj[u].pb(i), adj[v].pb(i);
    }
    cnt = n; ll res = 0;
    for(int i = 1; i <= n; ++i) {
        if(num[i] == 0) {
            st.clear();
            overall = -Time;
            dfs(i);
            overall += Time;
            st.clear();
            function<void(int)> dp = [&](int u) {
                sz[u] = u <= n;
                if(u > n) st.pb(u);
                for(int& v: g[u]) {
                    dp(v);
                    if(u > n) res += (ll)g[u].size() * sz[u] * sz[v];
                    sz[u] += sz[v];
                }
            };
            dp(i);
            for(int& v: st)
                res += (ll)g[v].size() * sz[v] * (overall - sz[v]);
            res -= 1ll  * overall * (overall - 1) / 2;
        }
    }
    cout << res * 2;
}

/// template 2
struct graph
{
	int n;
	vector<vector<int>> adj;
 
	graph(int n) : n(n), adj(n) {}
 
	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
 
	int add_node()
	{
		adj.push_back({});
		return n++;
	}
 
	vector<int>& operator[](int u) { return adj[u]; }
};
 
vector<vector<int>> biconnected_components(graph &adj)
{
	int n = adj.n;
 
	vector<int> num(n), low(n), art(n), stk;
	vector<vector<int>> comps;
 
	function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
	{
		num[u] = low[u] = ++t;
		stk.push_back(u);
 
		for (int v : adj[u]) if (v != p)
		{
			if (!num[v])
			{
				dfs(v, u, t);
				low[u] = min(low[u], low[v]);
 
				if (low[v] >= num[u])
				{
					art[u] = (num[u] > 1 || num[v] > 2);
 
					comps.push_back({u});
					while (comps.back().back() != v)
						comps.back().push_back(stk.back()), stk.pop_back();
				}
			}
			else low[u] = min(low[u], num[v]);
		}
	};
 
	for (int u = 0, t; u < n; ++u)
		if (!num[u]) dfs(u, -1, t = 0);
 
	// build the block cut tree
	function<graph()> build_tree = [&]()
	{
		graph tree(0);
		vector<int> id(n);
 
		for (int u = 0; u < n; ++u)
			if (art[u]) id[u] = tree.add_node();
 
		for (auto &comp : comps)
		{
			int node = tree.add_node();
			for (int u : comp)
				if (!art[u]) id[u] = node;
				else tree.add_edge(node, id[u]);
		}
 
		return tree;
	};
 
	return comps;
}
