struct TFlow {
    const int infFlow = int(1e9 + 7);
    struct TEdge {
        int u, v, cf;
        TEdge() {u = v = cf = 0;}
        TEdge(int u, int v, int cf): u(u), v(v), cf(cf) {}
    };
    int s, t, n, FlowVal;
    vector<TEdge> e;
    vector<vector<int>> a;
    vector<int> h;
    vector<vector<int>::iterator> p;
    TFlow() {}
    TFlow(int s, int t, int n): s(s), t(t), n(n) {
         e.clear(); a.resize(n + 1); h.resize(n + 1); p.resize(n + 1);
    }
    void AddEdge(int u, int v, int cf) {
        a[u].pb(e.size()); e.pb(u, v, cf);
        a[v].pb(e.size()); e.pb(v, u, 0);
    }
    void BFS() {
        fill(h.begin(), h.end(), n);
        h[t] = 0; queue<int> q; q.push(t);
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int i: a[u]) {
                i ^= 1;
                int v = e[i].u;
                if(e[i].cf == 0 || h[v] < n) continue;
                h[v] = h[u] + 1;
                if(v == s) return;
                q.push(v);
            }
        }
    }
    int DFS(int u, int In) {
        if(u == t) return In;
        int Out = 0, i, v, q;
        for(; p[u] != a[u].end(); ++p[u]) {
            i = *p[u], v = e[i].v;
            if(e[i].cf == 0 || h[v] != h[u] - 1) continue;
            q = DFS(v, min(In, e[i].cf));
            Out += q; In -= q;
            e[i].cf -= q, e[i ^ 1].cf += q;
            if(In == 0) return Out;
        }
        return Out;
    }
    int GetMaxFlow() {
        FlowVal = 0;
        while(BFS(), h[s] < n) {
            for(int u = 0; u < n; ++u) p[u] = a[u].begin();
            for(int u = 0; u < n; ++u) FlowVal += DFS(s, infFlow);
        }
        return FlowVal;
    }
};
