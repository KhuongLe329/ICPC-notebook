int Ind[N], Head[N], l[N], h[N], p[N][logN];
int d[N], st[M], pos[N], nChil[N], cost[N], cpos[N], c[N];
int n, u, v, nChain, nBase;
struct Edges
{
    int u, v;
} e[N];
vector<int> a[N];
string s;
 
struct Tsegment
{
    inline void Build(int x, int low, int high)
    {
        l[x] = low;
        h[x] = high;
        if(low == high)
        {
            st[x] = cpos[low];
            return;
        }
        int mid = low + high >> 1;
        Build(2 * x, low, mid);
        Build(2 * x + 1, mid + 1, high);
        int lef = x << 1, rig = lef + 1;
        if(st[lef] < st[rig]) st[x] = st[rig];
        else st[x] = st[lef];
    }
    inline void Update(int x, int u, int val)
    {
        if(l[x] > u || h[x] < u)
            return;
        if(l[x] == u && h[x] == u)
            {st[x] = val; return;}
        Update(2 * x, u, val);
        Update(2 * x + 1, u, val);
        int lef = x << 1, rig = lef + 1;
        if(st[lef] < st[rig]) st[x] = st[rig];
        else st[x] = st[lef];
    }
    inline int Query(int x, int low, int high)
    {
        if(l[x] > high || h[x] < low)
            return 0;
        if(l[x] >= low && h[x] <= high)
            return st[x];
        int res1 = Query(2 * x, low, high);
        int res2 = Query(2 * x + 1, low, high);
        if(res1 > res2) return res1;
        return res2;
    }
} IT;
 
struct HLD
{
    inline void ResetTree()
    {
        For(i, 1, n) a[i].clear();
        fill_n(Head, n + 1, 0);
        fill_n(st, M, 0);
        //fill_n(&p[0][0], N * logN, 0);
        nChain = 1; nBase = 0;
    }
    inline void DFS(int u)
    {
        nChil[u] = 1;
        for(int v: a[u])
        {
            if(v == p[u][0])
                continue;
            p[v][0] = u;
            d[v] = d[u] + 1;
            DFS(v);
            nChil[u] += nChil[v];
        }
    }
    inline void PreLCA()
    {
        p[1][0] = 1; d[1] = 0;
        DFS(1);
        For(i, 1, logN - 1)
        {
            For(j, 1, n)
            p[j][i] = p[p[j][i - 1]][i - 1];
        }
    }
    inline int LCA(int u, int v)
    {
        if(d[u] < d[v])
            swap(u, v);
        int log = log2(d[u]);
        Ford(i, log, 0)
        {
            if(d[u] - (1 << i) >= d[v])
                u = p[u][i];
        }
        if(u == v)
            return u;
        Ford(i, log, 0)
        {
            if(p[u][i] != p[v][i])
            {
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }
    inline void hld(int u, int c)
    {
        if(Head[nChain] == 0)
            Head[nChain] = u;
        Ind[u] = nChain;
        pos[u] = ++nBase;
        cpos[nBase] = c;
        int spec = -1;
        for(int v: a[u])
        {
            if(v == p[u][0])
                continue;
            if(spec == -1 || nChil[spec] < nChil[v])
                spec = v;
        }
        if(spec != -1) hld(spec, cost[spec]);
        for(int v: a[u])
        {
            if(v == p[u][0] || v == spec)
                continue;
            ++nChain;
            hld(v, cost[v]);
        }
    }
    inline int GoLCA(int u, int v)
    {
        if(u == v) return 0;
        int uchain = Ind[u];
        int vchain = Ind[v];
        int res = 0;
        while(1)
        {
            if(uchain == vchain)
            {
                if(u == v) return res;
                int k = IT.Query(1, pos[v] + 1, pos[u]);
                if(k > res) res = k;
                return res;
            }
            int k = IT.Query(1, pos[Head[uchain]], pos[u]);
            if(k > res) res = k;
            u = p[Head[uchain]][0];
            uchain = Ind[u];
        }
        return res;
    }
    inline int Query()
    {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        int res1 = GoLCA(u, lca);
        int res2 = GoLCA(v, lca);
        if(res1 > res2) return res1;
        return res2;
    }
} Tree;
 
void Enter()
{
    cin >> n;
    Tree.ResetTree();
    For(i, 1, n - 1)
    {
        cin >> e[i].u >> e[i].v >> c[i];
        a[e[i].u].pb(e[i].v);
        a[e[i].v].pb(e[i].u);
    }
    Tree.PreLCA();
    cost[1] = 0;
    For(i, 1, n - 1)
    {
        if(e[i].u != p[e[i].v][0]) swap(e[i].u, e[i].v);
        cost[e[i].v] = c[i];
    }
    Tree.hld(1, 0);
}
 
void Solve()
{
    IT.Build(1, 1, n);
    while(cin >> s)
    {
        if(s[0] == 'D')
            return;
        if(s[0] == 'C')
            {cin >> u >> v;IT.Update(1, pos[e[u].v], v);}
        else
            cout << Tree.Query() << '\n';
    }
}
