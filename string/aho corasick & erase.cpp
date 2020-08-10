#include <bits/stdc++.h>
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i >= u; i--)
#define N 1000005
#define maxc 1000000007
#define ll long long
#define mid (r + l)/2


using namespace std;

int n, k, pos[N], kmp[N], trie[N][26], numNode = 1, dd[N];
string S[N];
vector<int> g[N];
void add(string s, int id)
{
    int p = 1;
    for (auto c : s)
    {
        int ch = c - 'a';
        if (trie[p][ch] == 0)
            trie[p][ch] = ++numNode;
        p = trie[p][ch];
    }
    pos[id] = p;
}
void buildAho()
{
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        FOR(i, 0, 25)
            if (trie[u][i])
            {
                int v = trie[u][i];
                int tmp = kmp[u];
                while (tmp != 0 && trie[tmp][i] == 0)
                    tmp = kmp[tmp];
                if (tmp == 0)
                    kmp[v] = 1;
                else
                    kmp[v] = trie[tmp][i];
                q.push(v);
            }
    }
}
void buildGraph()
{
    FOR(i, 2, numNode)
        g[kmp[i]].PB(i);
}
int tin[N], tout[N], tt;
void DFS(int u)
{
    tin[u] = ++tt;
    for (auto v : g[u])
        DFS(v);
    tout[u] = tt;
}
struct BIT
{
    ll t[N];
    void upd(int x, ll val)
    {
        for (; x < N; x += (x & -x))
            t[x] += val;
    }
    ll get(int x)
    {
        ll ans = 0;
        for (; x; x -= (x & -x))
            ans += t[x];
        return ans;
    }
}t;
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("INP.TXT", "r", stdin);
    cin >> n >> k;
    FOR(i, 1, k)
    {
        cin >> S[i];
        add(S[i], i);
    }
    buildAho();
    buildGraph();
    DFS(1);
    FOR(i, 1, k)
    {
        t.upd(tin[pos[i]], 1);
        t.upd(tout[pos[i]]+1, -1);
        dd[i] = 1;
    }
    FOR(i, 1, n)
    {
        char c; cin >> c;
        if (c == '?')
        {
            string s; cin >> s;
            //cerr<<s<<'\n';
            ll  res = 0;
            int p = 1;
            for (auto c : s)
            {
                int ch = c - 'a';
                if (trie[p][ch])
                    p = trie[p][ch];
                else
                {
                    p = kmp[p];
                    while (p != 0 && trie[p][ch] == 0)
                        p = kmp[p];
                    if (p == 0) p = 1;
                    else p = trie[p][ch];
                }
                res += t.get(tin[p]);
            }
            cout <<res<<'\n';
        }
        else
        {
            int x; cin >> x;
            //cerr<<x<<endl;
            if (c == '+' && dd[x] == 0)
            {
                t.upd(tin[pos[x]], 1);
                t.upd(tout[pos[x]]+1, -1);
                dd[x] = 1;
            }
            else if (c == '-' && dd[x] == 1)
            {
                t.upd(tin[pos[x]], -1);
                t.upd(tout[pos[x]]+1, 1);
                dd[x] = 0;
            }
        }
    }
}
