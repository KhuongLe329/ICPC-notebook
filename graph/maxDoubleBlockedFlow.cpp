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
#define taskname "PATROL"
//#define BeztDonkey

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

template <typename T> inline void Cin(T &x)
{
    register char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
}

const int maxN = 1004, maxM = 3e5 + 7, max2M = maxM << 1, Inf = 1e5 + 1, d = 1;

struct TEdge
{
    int u, v, cf;
} e[max2M];
int h[maxN], head[maxN], current[maxN], link[max2M], n, m, s, t, _s, _t, u, v;

struct TDinic
{
    int s, t, n;
    inline void Layering()
    {
        memset(h, -1, n << 2);
        h[t] = 0;
        queue<int> q({t});
        while (!q.empty())
        {
            int u = q.front(), v, hv = h[u] + 1; q.pop();
            for (int i = head[u]; i != -1; i = link[i])
            {
                if (e[i ^ 1].cf == 0 || h[v = e[i ^ 1].u] != -1) continue;
                h[v] = hv;
                if (v == s) return;
                q.push(v);
            }
        }
    }
    inline int Discharge(int u, int flowIn)
    {
        if (u == t) return flowIn;
        int flowOut = 0, v, hv = h[u] - 1;
        for (auto &i = current[u]; i != -1; i = link[i])
        {
            if (h[v = e[i].v] != hv || e[i].cf == 0) continue;
            int q = Discharge(v, min(e[i].cf, flowIn));
            e[i].cf -= q;
            e[i ^ 1].cf += q;
            flowIn -= q;
            flowOut += q;
            if (flowIn == 0) break;
        }
        return flowOut;
    }
    inline int Run()
    {
        int flowVal = 0;
        while (Layering(), h[s] != -1)
        {
            copy(head, head + n + 1, current);
            flowVal += Discharge(s, Inf);
        }
        return flowVal;
    }
} Dinic;

#define PushFront(u, i) { link[i] = head[u]; head[u] = i; }
#define AddEdge(u, v, c) { PushFront(u, m); e[m++] = {u, v, c}; PushFront(v, m); e[m++] = {v, u, 0}; }
#define AddEdges(u, v) { AddEdge(u, v, Inf/*c - d*/); AddEdge(_s, v, d); AddEdge(u, _t, d); }

void Inp()
{
    int _m;
    Cin(n); Cin(_m);
    Dinic.s = _s = n + 2;
    Dinic.t = _t = n + 3;
    Dinic.n = n + 4;
    memset(head, -1, Dinic.n << 2);
    m = 0;
    AddEdges(s = 0, 1);
    AddEdges(n, t = n + 1);
    while (--_m >= 0)
    {
        Cin(u); Cin(v);
        AddEdges(u, v);
    }
    AddEdge(t, s, Inf);
}

void Refine()
{
    Dinic.s = t;
    Dinic.t = s;
    Dinic.n = n + 2;
    memset(head, -1, Dinic.n << 2);
    for (int i = 0; i < m - 2; i += 6)
    {
        e[i].cf = Inf;//= c - d
        //int f = e[i ^ 1].cf + d; e[i ^ 1].cf = f - d;
        PushFront(e[i].u, i);
        PushFront(e[i ^ 1].u, i ^ 1);
    }
}

void Solve()
{
    Dinic.Run();
    int ans = e[1].cf + d;
    Refine();
    ans -= Dinic.Run();
    cout << ans;
}

int main()
{
    #ifdef BeztDonkey
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

    Inp();
    Solve();


    #ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;

}
