#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<climits>
#include<cstring>
#include<iomanip>
#include<string>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<deque>
#include<algorithm>
#include<functional>
#include<chrono>
//#include<windows.h>
//#include<direct.h>
#include<random>
#include<sstream>

#define y0 asdahsdlkahsdad
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define taskname "F"
//#define BeztDonkey

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

template <typename T> inline void Cin(T &x)
{
    register char c;
    bool neg = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-') neg = 1;
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    if (neg) x = -x;
}

const int maxN = 1e5 + 2;
const ll LInf = 1e18;

int sz[maxN], a[maxN], b[maxN], n, u, v;
ll ans[maxN];
vector<int> adj[maxN];

inline void Build(int u, int p)
{
    sz[u] = 1;
    bool chk = 0;
    for (int &v : adj[u])
        if (v == p) v = adj[u].back(), chk = 1;
        else Build(v, u), sz[u] += sz[v];
    if (chk) adj[u].pop_back();
}

bool Guess = 0;
struct TLine
{
    mutable ll x, y, p;
    inline bool operator < (const TLine &l) const & { return Guess ? p < l.p : x < l.x; }
};
struct TConvexLine : multiset<TLine>
{
    inline ll Div(ll a, ll b) { ll q = a / b; return q - ((a ^ b) < 0 && a - b * q); }
    inline bool InterSect(iterator a, iterator b)
    {
        if (b == end()) return a->p = LInf, 0;
        if (a->x == b->x) a->p = a->y > b->y ? LInf : -LInf;
        else a->p = Div(a->y - b->y, b->x - a->x);
        return a->p >= b->p;
    }
    inline void Add(ll x, ll y)
    {
        auto c = insert({x, y, 0}), b = c++, a = b;
        while (InterSect(b, c)) c = erase(c);
        if (a != begin() && InterSect(--a, b)) InterSect(a, b = erase(b));
        while ((b = a) != begin() && (--a)->p >= b->p) InterSect(a, erase(b));
    }
    inline ll Query(ll p)
    {
        Guess = 1; auto l = lower_bound({0, 0, p}); Guess = 0;
        return l->x * p + l->y;
    }
} *vec[maxN];

inline void Visit(int u)
{
    int MaxChild = 0;
    for (int v : adj[u])
        if (sz[MaxChild] < sz[v]) MaxChild = v;
    if (MaxChild) Visit(MaxChild), vec[u] = vec[MaxChild];
    else vec[u] = new TConvexLine;
    for (int v : adj[u])
        if (v != MaxChild)
        {
            Visit(v);
            for (auto &l : *vec[v]) vec[u]->Add(l.x, l.y);
        }
    if (MaxChild) ans[u] = -vec[u]->Query(a[u]);
    else ans[u] = 0;
    vec[u]->Add(-b[u], -ans[u]);

}

int main()
{
    #ifdef BeztDonkey
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen(taskname".inp", "r", stdin);
    //freopen(taskname".out", "w", stdout);

    Cin(n);
    for (int i = 1; i <= n; ++i) Cin(a[i]);
    for (int i = 1; i <= n; ++i) Cin(b[i]);
    for (int i = 1; i < n; ++i) Cin(u), Cin(v), adj[u].push_back(v), adj[v].push_back(u);
    Build(1, 1);
    Visit(1);
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';

    #ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;

}
