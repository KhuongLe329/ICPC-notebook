struct TFlow {
    struct TEdge {
        int u, v, cf;
        TEdge() {u = v = cf = 0;}
        TEdge(int u, int v, int cf): u(u), v(v), cf(cf) {}
    };
    int s, t, n, FlowVal;
    vector<TEdge> e;
    vector<vector<int>> a;
    vector<int> trace;
    TFlow() {}
    TFlow(int s, int t, int n): s(s), t(t), n(n) {
         e.clear(); a.resize(n + 1); trace.resize(n + 1);
    }
    void AddEdge(int u, int v, int cf) {
        a[u].pb(e.size()); e.pb(u, v, cf);
        a[v].pb(e.size()); e.pb(v, u, 0);
    }
    bool BFS() {
        fill(trace.begin(), trace.end(), -1);
        trace[s] = -2; queue<int> q; q.push(s);
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int i: a[u]) {
                int v = e[i].v;
                if(e[i].cf > 0 && trace[v] == -1) {
                    q.push(v), trace[v] = i;
                    if(v == t) return 1;
                }
            }
        }
        return 0;
    }
    int GetMaxFlow() {
        int delta, u, i;
        FlowVal = 0;
        while(BFS()) {
           delta = int(1e9 + 7);
           for(u = t; (i = trace[u]) >= 0; u = e[i].u)
               delta = min(delta, e[i].cf);
           for(u = t; (i = trace[u]) >= 0; u = e[i].u)
               e[i].cf -= delta, e[i ^ 1].cf += delta;
           FlowVal += delta;
        }
        return FlowVal;
    }
};
