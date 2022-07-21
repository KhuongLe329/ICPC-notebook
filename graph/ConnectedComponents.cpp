int n, m, u, v, res;
vector<bool> num;
vector<int> z;
vector<vector<int>> a, r;
 
void DFS(int u)
{
    num[u] = 1;
    for(int v: a[u])
        if(!num[v]) DFS(v);
    z.pb(u);
}
 
void RDFS(int u)
{
    num[u] = 0;
    for(int v: r[u])
        if(num[v]) RDFS(v);
}
 
void Enter()
{
     Cin(n, m);
     a.resize(n + 1), r.resize(n + 1);
     while(m --) {
        Cin(u, v);
        a[u].pb(v), r[v].pb(u);
     }
     num.resize(n + 1, 0);
     for(int i = 1; i <= n; ++i)
        if(!num[i]) DFS(i);
}
 
void Solve()
{
     res = 0;
     while(!z.empty()) {
         int u = z.back();
         z.pop_back();
         if(!num[u]) continue;
         RDFS(u);
         ++res;
     }
     cout << res;
}
