#include<bits/stdc++.h>
#define For(i, a, b)  for(int i = a; i <= b; ++i)
#define Ford(i, a, b) for(int i = a; i >= b; --i)
#define FileName      "test"
#define ll            long long
#define ld            long double
#define ull           unsigned long long
#define pb            push_back
#define X             first
#define Y             second
//#define Karma

using namespace std;

template <typename T> inline void Cin(T &x)
{
    char c;
    T sign = 1;
    x = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-')
            sign = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= sign;
}

typedef pair<int, int> pii;
typedef pair<ll, int> plli;
const int N = 1e5 + 7;
const int M = 1e5;
const ll Cmax = 1e18 + 7;

int n, x, y, sz[N];
ll a[N], b[N], res[N];
vector<int> adj[N];
vector<int>* g[N];

struct Line
{
    ll a, b;
    Line(ll a = 0, ll b = Cmax): a(a), b(b) {}
    ll GetVal(ll x)
    {
        return a * x + b;
    }
};

struct TSegmentMin
{
    Line cur;
    TSegmentMin* left;
    TSegmentMin* right;
    TSegmentMin(Line cur = Line(), TSegmentMin* left = NULL, TSegmentMin* right = NULL): cur(cur), left(left), right(right) {}
};

TSegmentMin* f[N];

TSegmentMin* Update(TSegmentMin* p, int l, int r, int x, int y, Line val)
{
    if(l > y || r < x || l > r) return p;
    int mid = (l + r) >> 1;
    TSegmentMin* res = p ? new TSegmentMin(p -> cur, p -> left, p -> right): new TSegmentMin();
    if(x <= l && r <= y)
    {
        ll lval = val.GetVal(l);
        ll rval = val.GetVal(r);
        ll lcur = res -> cur.GetVal(l);
        ll rcur = res -> cur.GetVal(r);
        if(lcur >= lval && rcur >= rval)
        {
            res -> cur = val;
            return res;
        }
        if(lcur <= lval && rcur <= rval)
        {
            return res;
        }
        ll mval = val.GetVal(mid);
        ll mcur = res -> cur.GetVal(mid);
        if(lcur >= lval && mcur >= mval)
        {
            res -> right = Update(res -> right, mid + 1, r, x, y, res -> cur);
            res -> cur = val;
            return res;
        }
        if(lcur <= lval && mcur <= mval)
        {
            res -> right = Update(res -> right, mid + 1, r, x, y, val);
            return res;
        }
        if(mcur >= mval && rcur >= rval)
        {
            res -> left = Update(res -> left, l, mid, x, y, res -> cur);
            res -> cur = val;
            return res;
        }
        if(mcur <= mval && rcur <= rval)
        {
            res -> left = Update(res -> left, l, mid, x, y, val);
            return res;
        }
    }
    res -> left = Update(res -> left, l, mid, x, y, val);
    res -> right = Update(res -> right, mid + 1, r, x, y, val);
    return res;
}

ll Query(TSegmentMin* p, int l, int r, int x)
{
    if(l > x || r < x || !p) return Cmax;
    ll res = p -> cur.GetVal(x);
    if(l == r) return res;
    res = min(res, Query(p -> left, l, (l + r) >> 1, x));
    res = min(res, Query(p -> right, (l + r) >> 1 | 1, r,  x));
    return res;
}

void DFS(int u, int p)
{
    int big = 0;
    sz[u] = 1;
    for(int v: adj[u])
    {
        if(v == p) continue;
        DFS(v, u);
        sz[u] += sz[v];
        if(!big || sz[big] < sz[v]) big = v;
    }
    if(big)
    {
        f[u] = f[big];
        g[u] = g[big];
        for(int v: adj[u])
        {
            if(v == big || v == p) continue;
            for(int x: *g[v])
            {
                g[u] -> pb(x);
                f[u] = Update(f[u], -M, M, -M, M, Line(b[x], res[x]));
            }
        }
        res[u] = Query(f[u], -M, M, a[u]);
    }
    else g[u] = new vector<int>();
    g[u] -> pb(u);
    f[u] = Update(f[u], -M, M, -M, M, Line(b[u], res[u]));
}

void Enter()
{
    Cin(n);
    For(i, 1, n) Cin(a[i]);
    For(i, 1, n) Cin(b[i]);
    For(i, 1, n - 1)
    {
        Cin(x);
        Cin(y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
}

void Solve()
{
    DFS(1, 1);
    For(i, 1, n) cout << res[i] << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef Karma
    freopen(FileName".inp", "r", stdin);
    freopen(FileName".out", "w", stdout);
#endif // Karma

    Enter();
    Solve();

    return 0;
}
