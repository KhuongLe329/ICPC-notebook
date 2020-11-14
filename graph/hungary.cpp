#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
#define int         int64_t

using namespace std;

const int N = int(2e3) + 7;
const int inf = int(1e18);
typedef pair<int, int> pii;
#define arg __arg
long long c[N][N];
long long fx[N], fy[N];
int mx[N], my[N];
int trace[N], qu[N], arg[N];
long long d[N];
int front, rear, start, finish;
int n, m, u, v, w, k, rn;

void init() {
    for(int i = 1; i <= n; ++i) {
        fy[i] = mx[i] = my[i] = 0;
        for(int j = 1; j <= n; ++j) c[i][j] = inf;
    }
}

void addEdge(int i, int j, long long cost) {
    c[i][j] = min(c[i][j], cost);
}

inline long long getC(int i, int j) {
    return c[i][j] - fx[i] - fy[j];
}

void initBFS() {
    front = rear = 1;
    qu[1] = start;
    memset(trace, 0, sizeof trace);
    for(int j = 1; j <= n; ++j) {
        d[j] = getC(start, j);
        arg[j] = start;
    }
    finish = 0;
}

void findAugPath() {
    while (front <= rear) {
        int i = qu[front++];
        for(int j = 1; j <= n; ++j) if (!trace[j]) {
            long long w = getC(i, j);
            if (!w) {
                trace[j] = i;
                if (!my[j]) {
                    finish = j;
                    return ;
                }
                qu[++rear] = my[j];
            }
            if (d[j] > w) {
                d[j] = w;
                arg[j] = i;
            }
        }
    }
}

void subx_addy() {
    long long delta = inf;
    for(int j = 1; j <= n; ++j)
        if (trace[j] == 0 && d[j] < delta) delta = d[j];

    // xoay
    fx[start] += delta;
    for(int j = 1; j <= n; ++j)
        if (trace[j]) {
            int i = my[j];
            fy[j] -= delta;
            fx[i] += delta;
        }
        else d[j] -= delta;

    for(int j = 1; j <= n; ++j)
        if (!trace[j] && !d[j]) {
            trace[j] = arg[j];
            if (!my[j]) { finish = j; return ; }
            qu[++rear] = my[j];
        }
}

void enlarge() {
    do {
        int i = trace[finish];
        int next = mx[i];
        mx[i] = finish;
        my[finish] = i;
        finish = next;
    } while (finish);
}
vector<pii> ans;
int mincost() {
    for(int i = 1; i <= n; ++i) fx[i] = *min_element(c[i]+1, c[i]+n+1);
    for(int j = 1; j <= n; ++j) {
        fy[j] = c[1][j] - fx[1];
        for(int i = 1; i <= n; ++i) {
            fy[j] = min(fy[j], c[i][j] - fx[i]);
        }
    }
    for(int i = 1; i <= n; ++i) {
        start = i;
        initBFS();
        while (finish == 0) {
            findAugPath();
            if (!finish) subx_addy();
        }
        enlarge();
    }
    int res = 0;
    for(int i = 1; i <= rn; ++i) {
        if(!(1 <= mx[i] && mx[i] <= m)) continue;
        res += c[i][mx[i]];
        ans.pb(i, mx[i]);
    }
    return inf * (int)ans.size() - res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> m >> rn >> k; n = max(m, rn);
    init();
    for(int i = 1; i <= k; ++i) {
        cin >> u >> v >> w;
        addEdge(u, v, inf - w);
    }
    cout << mincost() << '\n';
    cout << (int)ans.size() << '\n';
    for(pii p: ans) cout << p.fi << ' ' << p.se << '\n';
}
