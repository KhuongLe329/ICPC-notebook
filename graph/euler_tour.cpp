#include <bits/stdc++.h>
#define taskname "ET"

//#define Bang
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int maxN = 1e5 + 9, maxM = 1e5 + 9;

int deg[maxN], n, m;
struct TEdge
{
    int u, v;
    bool del;
} edges[maxM];
vector<TEdge*> adj[maxN];
vector<int> ans;

void Inp()
{
    cin >> n >> m;
    TEdge* e = edges;
    for (int i = 0; i < m; ++i)
    {
        cin >> e->u >> e->v; e->del = 0;
        ++deg[e->u]; ++deg[e->v];
        adj[e->u].push_back(e);
        adj[e->v].push_back(e);
        ++e;
    }
}

bool EulerTour()
{
    for (int u = 0; u < n; ++u)
        if (deg[u] & 1) return 0;
    return 1;
}

inline void DFS(int u, int id)
{
    while (!adj[u].empty())
        if (adj[u].back()->del) adj[u].pop_back();
        else
        {
            TEdge* e = adj[u].back();
            e->del = 1;
            adj[u].pop_back();
            DFS(e->u + e->v - u, e - edges);
        }
    if (id >= 0) ans.push_back(id);
}

int main()
{
    #ifdef Bang
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

    Inp();
    if (!EulerTour()) cout << "NO";
    else
    {
        DFS(edges->u, -1);
        if (ans.size() == m)
        {
            cout << "YES" << '\n';
            for (int x : ans) cout << x << ' ';
        }
        else cout << "NO";
    }

    #ifdef Bang
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;
}
