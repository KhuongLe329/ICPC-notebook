#include<bits/stdc++.h>
 
using namespace std;
#define taskname "COT2"
#define pb	push_back
typedef long double ld;
typedef long long ll;
const int maxn = 4e4 + 5;
const int logn = log2(maxn) + 1;
const int block = sqrt(maxn * 2);
const int maxq = 1e5 + 5;
vector<int> v[maxn];
int n , m , a[maxn] , P[maxn][logn] , st[maxn] , fn[maxn] , id[maxn * 2] , h[maxn];
pair<int,int> Ca[maxn];
 
struct query
{
    int l , r , Lca , id;
    bool operator < (const query & other)const &
    {
        if(l / block == other.l / block)
            return r < other.r;
        return l / block < other.l / block;
    }
}Q[maxq];
 
inline void enter()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)cin >> a[i];
    for(int i = 1 ; i < n ; ++i)
    {
        int x , y;cin >> x >> y;
        v[x].pb(y);v[y].pb(x);
    }
}
 
inline void compress()
{
    for(int i = 1 ; i <= n ; ++i)
        Ca[i] = {a[i] , i};
    sort(Ca + 1 , Ca + n + 1);
    int cnt = 0;
    for(int i = 1 ; i <= n ; ++i){
        if(Ca[i].first == Ca[i - 1].first)a[Ca[i].second] = cnt;
        else a[Ca[i].second] = ++cnt;
//        cout << Ca[i].first << " " << Ca[i].second << endl;
    }
//    for(int i = 1 ; i <= n ; ++i)cout << a[i] << endl;
}
 
inline void dfs(int u , int par)
{
    static int nTime = 0;
    st[u] = ++nTime;
    id[nTime] = u;
    for(int c : v[u])
    {
        if(c == par)continue;
        P[c][0] = u;h[c] = h[u] + 1;
        for(int i = 1 ; i < logn ; ++i)
            P[c][i] = P[P[c][i - 1]][i - 1];
        dfs(c , u);
    }
    fn[u] = ++nTime;
    id[nTime] = u;
}
 
inline int LCA(int u , int v)
{
    if(h[u] < h[v])swap(u , v);
    int k = h[u] - h[v];
    for(int i = logn - 1 ; i >= 0 ; --i)
        if(k & (1 << i))u = P[u][i];
    if(u == v)return u;
    for(int i = logn - 1 ; i >= 0 ; --i)
        if(P[u][i] != P[v][i])u = P[u][i] , v = P[v][i];
    return P[u][0];
}
 
int chk[maxn] , lpt = 1 , hpt = 0 , chk1[maxn];
int res = 0 , ans[maxq];
 
inline void add(int x)
{
    if((chk1[x] == 1) && (--chk[a[x]] == 0))res--;
    else if((chk1[x] == 0) && (++chk[a[x]] == 1))res++;
    chk1[x] ^= 1;
}
 
int qr(int L , int H , int LCA)
{
    while(lpt < L)add(id[lpt++]);
    while(lpt > L)add(id[--lpt]);
    while(hpt < H)add(id[++hpt]);
    while(hpt > H)add(id[hpt--]);
    if(id[lpt] != LCA && id[hpt] != LCA)add(LCA);
    int tmpres = res;
    if(id[lpt] != LCA && id[hpt] != LCA)add(LCA);
    return tmpres;
}
 
inline void solve()
{
    dfs(1 , 0);
    for(int i = 1 ; i <= m ; ++i)
    {
        int u , v;cin >> u >> v;
        if(st[u] > st[v])swap(u , v);
        int Lca = LCA(u , v);
        Q[i].id = i;Q[i].Lca = Lca;
        if(Lca == u)Q[i].l = st[u] , Q[i].r = st[v];
        else Q[i].l = fn[u] , Q[i].r = st[v];
    }
//    cout << st[2];
    sort(Q + 1 , Q + m + 1);
    lpt = Q[1].l;hpt = lpt - 1;
    for(int i = 1 ; i <= m ; ++i){
        ans[Q[i].id] = qr(Q[i].l , Q[i].r , Q[i].Lca);
//        cout << Q[i].l << " " << Q[i].r << endl;
    }
    for(int i = 1 ; i <= m ; ++i)cout << ans[i] << '\n';
}
 
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	if(fopen(taskname".INP","r"))
        freopen(taskname".INP", "r",stdin) ,
        freopen(taskname".OUT", "w",stdout);
    enter();compress();solve();
}
