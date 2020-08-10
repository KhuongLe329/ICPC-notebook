struct TTree {
    vector<vector<int>> pre, adj;
    vector<int> sz, vis, big;
    int n;
    void init(int _n) { n = _n;
        pre.resize(n + 1), adj.resize(n + 1); big.resize(n + 1);
        sz.resize(n + 1), vis.resize(n + 1);
    }
    void add(int u, int v) {
        pre[u].pb(v); pre[v].pb(u);
    }
    int findcentroid(int u) {
        function<void(int, int)> dfs = [&](int u, int par) {
            sz[u] = 1; big[u] = -1;
            for(int v: pre[u]) {
                if(vis[v] || v == par) continue;
                dfs(v, u); sz[u] += sz[v];
                if(big[u] == -1 || sz[big[u]] < sz[v]) big[u] = v;
            }
        };
        dfs(u, -1);
        int sum = sz[u];
        while(sz[big[u]] << 1 >= sum && big[u] != -1) u = big[u];
        return u;
    }
    int divide(int u) {
        u = findcentroid(u);
        vis[u] = 1; int v;
        for(int v: pre[u]) {
            if(vis[v]) continue;
            v = divide(v);
            adj[u].pb(v);
        }
        return u;
    }
};
