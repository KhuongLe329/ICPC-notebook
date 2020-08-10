// VOI 2020
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
//#define int         int64_t
 
using namespace std;
 
const int N = int(5e4) + 5;
const int inf = (int)2e9 + 2;
 
struct TEdge {
    int u, v, w;
    TEdge() {u = v = w = 0;}
    TEdge(int u, int v, int w): u(u), v(v), w(w) {}
    bool operator<(const TEdge& o) const& {return w < o.w;}
};
vector<int> val, ed[3][N];
vector<TEdge> e[3];
int n, m, s, t, res = inf, cmd, u, v, w, f[N];
 
struct dsu_save {
    int u, par;
    dsu_save() {u = par = 0;}
    dsu_save(int u, int par): u(u), par(par) {}
};
 
struct dsu {
	vector<int> par;
	vector<dsu_save> change;
	void init(int n) {
		par = vector<int>(n + 5, 0);
		iota(par.begin(), par.end(), 0);
	}
	int find_set(int x) {
		if (par[x] != x) {
			change.pb(x, par[x]);
			par[x] = find_set(par[x]);
		}
		return par[x];
	}
	int unite(int x, int y) {
	  int res = 0, pre;
		pre = change.size();
		x = find_set(x), y = find_set(y);
        res += change.size() - pre;
		if (x != y) {
			change.pb(x, par[x]);
			par[x] = y; ++res;
		}
		return res;
	}
	void rollback() {
        par[change.back().u] = change.back().par;
        change.pop_back();
	}
} dsu;
 
void DP(int l, int r, int optl, int optr) { /// added < l && < optl && f[r] >= f(mid) >= f(l)
    if(r < l) return;
    int mid = (l + r) >> 1, cnt = 0, pre, u, v;
    for(int i = l; i <= mid; ++i) {
        for(int j: ed[1][i]) cnt += dsu.unite(e[1][j].u, e[1][j].v);
    } u = -1, v = 0;
    for(int i = optl; i <= optr; ++i) {
        for(int j: ed[2][i]) cnt += dsu.unite(e[2][j].u, e[2][j].v);
        pre = dsu.change.size();
        u = dsu.find_set(s), v = dsu.find_set(t);
        cnt += dsu.change.size() - pre;
        if(u == v) {f[mid] = i; break;}
    }
    if(u == v) res = min(val[f[mid]] + val[mid], res);
    else f[mid] = val.size() - 1;
    while(cnt --) dsu.rollback(); cnt = 0;
    for(int i = l; i <= mid; ++i) {
        for(int j: ed[1][i]) cnt += dsu.unite(e[1][j].u, e[1][j].v);
    }
    DP(mid + 1, r, optl, f[mid]);
    while(cnt --) dsu.rollback(); cnt = 0;
    for(int i = optl; i < f[mid]; ++i) {
        for(int j: ed[2][i]) cnt += dsu.unite(e[2][j].u, e[2][j].v);
    }
    DP(l, mid - 1, f[mid], optr);
    while(cnt --) dsu.rollback(); cnt = 0;
}
 
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> m >> s >> t;
    for(int i = 1; i <= m; ++i) {
        cin >> cmd >> u >> v >> w;
        e[cmd].pb(u, v, w); val.pb(w);
    } val.pb(0);
    sort(val.begin(), val.end()); val.erase(unique(val.begin(), val.end()), val.end());
    for(int i = 0; i < e[1].size(); ++i) {
        e[1][i].w = lower_bound(val.begin(), val.end(), e[1][i].w) - val.begin();
        ed[1][e[1][i].w].pb(i);
    }
    for(int i = 0; i < e[2].size(); ++i) {
        e[2][i].w = lower_bound(val.begin(), val.end(), e[2][i].w) - val.begin();
        ed[2][e[2][i].w].pb(i);
    }
    dsu.init(n);
    DP(0, (int)val.size() - 1, 0, (int)val.size() - 1);
    cout << res;
}
