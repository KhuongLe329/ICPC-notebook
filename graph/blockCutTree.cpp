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
