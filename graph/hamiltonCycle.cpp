#include <bits/stdc++.h>
#define taskname "HC"

using namespace std;

const int maxN = 109;

int deg[maxN], p[maxN], n, m, Begin, u, v;
vector<int> adj[maxN], _adj[maxN];
bool outpath[maxN], avail[maxN];

void Inp()
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v;
        if (n > 1 && u == v) continue;
        _adj[u].push_back(v);
        _adj[v].push_back(u);
    }
    for (int u = 0; u < n; ++u)
    {
        auto &_v = _adj[u];
        if (_v.empty()) continue;
        auto &v = adj[u];
        sort(_v.begin(), _v.end());
        v.push_back(_v[0]);
        for (auto it = _v.begin() + 1; it != _v.end(); ++it)
            if (*it != *(it - 1)) v.push_back(*it);
    }
}

inline bool Minimize(int &a, int b)
{
    return b < a ? (a = b, 1) : 0;
}

inline int Greedy(int s)
{
    for (int u = 0; u < n; ++u) deg[u] = adj[u].size();
    fill_n(outpath, n, 1);
    int res = 0;
    while (true)
    {
        outpath[s] = 0;
        int x = -1, degx = maxN;
        for (auto it = adj[s].begin(); it != adj[s].end(); ++it)
            if (outpath[*it] && Minimize(degx, --deg[*it])) x = *it;
        if (x == -1) break;
        s = x;
        ++res;
    }
    return res;
}

void Init()
{
    int tmp = -1;
    for (int u = 0; u < n; ++u)
    {
        int _tmp = Greedy(u);
        if (_tmp >= tmp) tmp = _tmp, Begin = u;
    }
    for (int u = 0; u < n; ++u) deg[u] = adj[u].size();
    /*int tmp = maxN;
    for (int u = 0; u < n; ++u)
        if (Minimize(tmp, deg[u])) Begin = u;*/
    fill_n(outpath, n, 1);
    p[0] = Begin;
}

inline bool CheckConnect(int i)
{
    copy(outpath, outpath + n, avail);
    stack<int> s;
    avail[Begin] = 0; s.push(Begin);
    while (!s.empty())
    {
        int u = s.top(); s.pop();
        ++i;
        for (int v : adj[u])
            if (avail[v]) avail[v] = 0, s.push(v);
    }
    return i == n;
}

inline void Attemp(int i)
{
    if (!CheckConnect(i - 1)) return;
    auto &V = adj[p[i - 1]];
    sort(V.begin(), V.end(), [](int u, int v)
    {
        if (outpath[u] != outpath[v]) return outpath[u];
        return deg[u] < deg[v];
    });
    for (int u : V)
    {
        if (i < n && u == Begin) continue;
        if (!outpath[u]) break;
        p[i] = u;
        outpath[u] = 0;
        for (int v : adj[u]) --deg[v];
        if (u == Begin)
        {
            for (int i = 0; i <= n; ++i) cout << p[i] << ' ';
            exit(0);
        }
        Attemp(i + 1);
        outpath[u] = 1;
        for (int v : adj[u]) ++deg[v];
        if (deg[u] == 1) break;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

    Inp();
    Init();
    Attemp(1);
    return 0;

}
