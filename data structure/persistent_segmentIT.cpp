#include<bits/stdc++.h>
#define ll       long long
#define pb       emplace_back

using namespace std;

template<typename T> inline void Cin(T &x)
{
    register char c;
    bool neg = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-') neg = 1;
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    if (neg) x = -x;
}
template<typename T, typename... Ts> inline void Cin(T& x, Ts&... xs) { Cin(x); Cin(xs...); }
template<typename T> inline void Out(const T x) { if (x > 9) Out(x / 10); putchar(x % 10 + '0'); }
template<typename T> inline void Cout(const T x) { if (x < 0) putchar('-'), Out(-x); else Out(x); }
template<typename T> inline void Cout(const T x, const char c) { Cout(x); putchar(c); }
template<typename T, typename... Ts> inline void Cout(const T x, const char c, const Ts... xs) { Cout(x); putchar(c); Cout(xs...); }

typedef pair<int, int> pii;
const int N = int(1e5) + 7;
const ll inf = (ll)1e18;
#define int      int64_t

int pos, i, j;
vector<int> v;
struct TLine {
    ll x, y;
    inline TLine(int x = 0, ll y = 0) : x(x), y(y) {}
    inline ll Get(int pos) { return (ll)x * v[pos - 1] + y; }
};
struct TMinIT {
    int l, r, m;
    TMinIT *lef, *rig;
    TMinIT() {}
    TLine cur;
};
typedef TMinIT* PMinIT;
void Build(PMinIT node, int l, int r) {
    node -> l = l, node -> r = r, node -> m = (l + r) >> 1;
    if(l == r) return;
    node -> lef = new TMinIT();
    Build(node -> lef, l, node -> m);
    node -> rig = new TMinIT();
    Build(node -> rig, node -> m + 1, r);
}
inline PMinIT _Add(PMinIT node, TLine val)
{
    if (node -> l >= i && node -> r <= j)
    {
        ll lval = val.Get(node -> l), lcur = node -> cur.Get(node -> l);
        ll rval = val.Get(node -> r), rcur = node -> cur.Get(node -> r);
        if (lcur <= lval && rcur <= rval) return node;
        PMinIT res = new TMinIT();
        res -> l = node -> l, res -> r = node -> r, res -> m = node -> m;
        res -> lef = node -> lef, res -> rig = node -> rig; res -> cur = node -> cur;
        if (lcur >= lval && rcur >= rval) {
            res -> cur = val;
            return res;
        }
        ll mval = val.Get(node -> m), mcur = node -> cur.Get(node -> m);
        if (lcur <= lval && mcur <= mval) {
            res -> rig = _Add(node -> rig, val);
            return res;
        }
        if (lcur >= lval && mcur >= mval) {
            res -> rig = _Add(node -> rig, node -> cur); res -> cur = val;
            return res;
        }
        if (rcur <= rval && mcur <= mval) {
            res -> lef = _Add(node -> lef, val); return res;
        }
        if (rcur >= rval && mcur >= mval) {
            res -> lef = _Add(node -> lef, node -> cur); res -> cur = val;
            return res;
        }
        return res;
    }
    PMinIT res = new TMinIT();
    res -> l = node -> l, res -> r = node -> r, res -> m = node -> m;
    res -> lef = node -> lef, res -> rig = node -> rig; res -> cur = node -> cur;
    if (node -> l <= j && node -> m >= i) res -> lef = _Add(node -> lef, val);
    if (node -> m < j && node -> r >= i) res -> rig = _Add(node -> rig, val);
    return res;
}
inline PMinIT Add(PMinIT node, int l, int r, const TLine &val)
{ if (l > r) return node; i = l; j = r; return _Add(node, val); }
inline ll _Query(PMinIT node)
{
    if (node -> l == node -> r) return node -> cur.Get(pos);
    if (pos <= node -> m) return min(node -> cur.Get(pos), _Query(node -> lef));
    return min(node -> cur.Get(pos), _Query(node -> rig));
}
inline ll Query(PMinIT node, int p) { pos = p; return _Query(node); }
PMinIT ver[N];
int n, d[N], res[N], vv[N], aa[N];
vector<pii> a[N];

void DFS(int u, int par) {
    for(pii nxt: a[u]) {
        int y = nxt.first, c = nxt.second;
        if(y == par) continue;
        d[y] = d[u] + c;
        res[y] = Query(ver[u], vv[y]) + d[y] * v[vv[y] - 1] + aa[y];
        ver[y] = Add(ver[u], 1, int(v.size()), TLine(-d[y], res[y]));
        DFS(y, u);
    }
}

int32_t main() {
    ios_base::sync_with_stdio();
    cin.tie(0), cout.tie(0);
    #define Task      "harbingers"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    Cin(n);
    for(int i = 1; i < n; ++i) {
       int u, v, c; Cin(u, v, c);
       a[u].pb(v, c); a[v].pb(u, c);
    }
    for(int i = 2; i <= n; ++i) {
       Cin(aa[i], vv[i]);
       v.pb(vv[i]);
    }
    sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 2; i <= n; ++i) vv[i] = lower_bound(v.begin(), v.end(), vv[i]) - v.begin() + 1;
    ver[1] = new TMinIT();
    Build(ver[1], 1, int(v.size()));
    DFS(1, 1);
    for(int i = 2; i <= n; ++i) Cout(res[i], ' ');
}
