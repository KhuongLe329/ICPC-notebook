/// factories JOI 2014
#include<bits/stdc++.h>
#include "factories.h"
#define pb      emplace_back
#define mp      make_pair
#define fi      first
#define se      second
#define ll      long long

using namespace std;

const int N = int(5e5) + 7;
const int logN = 21;
const ll oo = (ll)1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

static int in[N], out[N], h[N], p[N][logN], Ti, c[N];
ll d[N], res;
pll f[N];
vector<pii> a[N], v;
vector<int> g[N], st;

void DFS(int u) {
     in[u] = ++Ti;
     for(int i = 1; i < logN; ++i) p[u][i] = p[p[u][i - 1]][i - 1];
     for(pii adj: a[u]) {
        if(in[adj.fi]) continue;
        d[adj.fi] = d[u] + adj.se;
        p[adj.fi][0] = u, h[adj.fi] = h[u] + 1;
        DFS(adj.fi);
     }
     out[u] = Ti;
}

int LCA(int u, int v)
{
    if(h[u] < h[v]) swap(u, v);
    for(int i = logN - 1; i >= 0; --i)
        if(h[u] - (1 << i) >= h[v]) u = p[u][i];
    if(u == v) return u;
    for(int i = logN - 1; i >= 0; --i)
        if(p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    return p[u][0];
}

void Init(int n, int A[], int B[], int D[]) {
     for(int i = 0; i + 1 < n; ++i) a[A[i]].pb(B[i], D[i]), a[B[i]].pb(A[i], D[i]);
     DFS(0);
}
//fi - u, se - v
void GetAns(int u) {
     if(c[u] == 1) f[u] = mp(d[u], oo);
     else if(c[u] == 2) f[u] = mp(oo, d[u]);
     else f[u] = mp(oo, oo);
     for(int v: g[u]) {
        GetAns(v);
        res = min({res, f[v].fi + f[u].se - 2 * d[u], f[v].se + f[u].fi - 2 * d[u]});
        f[u].fi = min(f[u].fi, f[v].fi);
        f[u].se = min(f[u].se, f[v].se);
     }
}

ll Query(int S, int X[], int T, int Y[])
{
   v.clear(); st.clear();
   for(int i = 0; i < S; ++i) c[X[i]] = 1, v.pb(in[X[i]], X[i]);
   for(int i = 0; i < T; ++i) c[Y[i]] = 2, v.pb(in[Y[i]], Y[i]);
   sort(v.begin(), v.end());
   for(int i = 0; i < S + T - 1; ++i) {
      int lca = LCA(v[i].se, v[i + 1].se);
      v.pb(in[lca], lca);
   }
   v.pb(in[0], 0);
   sort(v.begin(), v.end()), v.erase(unique(v.begin(), v.end()), v.end());
   for(pii p: v) {
      g[p.se].clear();
      while(!st.empty() && out[st.back()] < p.fi) st.pop_back();
      if(st.size()) g[st.back()].pb(p.se);
      st.pb(p.se);
   }
   res = oo; GetAns(0);
   for(int i = 0; i < S; ++i) c[X[i]] = 0;
   for(int i = 0; i < T; ++i) c[Y[i]] = 0;
   return res;
}
