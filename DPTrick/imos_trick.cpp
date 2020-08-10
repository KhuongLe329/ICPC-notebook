/// atcoder problem F ARC

#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
#define int         int64_t

using namespace std;

typedef pair<int, int> pii;
const int N = 5003;
const int M = 202;
const int inf = int(1e18);

int n, m, l, r, iTicket, a[N], b[M][N], f[N][N];
set<int> s;
set<int>::iterator p;
vector<int> cur;

void Update(int x) {
    iTicket = x;
    sort(cur.begin(), cur.end(), [](const int& i, const int& j) {
            return b[iTicket][i] > b[iTicket][j];
         });
    s.clear(); s.insert(0); s.insert(n + 1);
    for(int i: cur) {
        p = s.upper_bound(i);
        r = (*p); l = *(p = prev(p)) + 1;
        f[l][i] += b[iTicket][i];
        f[l][r] -= b[iTicket][i];
        f[i + 1][i] -= b[iTicket][i];
        f[i + 1][r] += b[iTicket][i];
        s.insert(i);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 2; i <= n; ++i) cin >> a[i], a[i] += a[i - 1];
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j)
            cin >> b[j][i];
    }
    cur.clear(); cur.resize(n); iota(cur.begin(), cur.end(), 1);
    for(int i = 1; i <= m; ++i) Update(i);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            f[i][j] += f[i][j - 1];
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            f[i][j] += f[i - 1][j];
    } int res = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n; ++j) {
            res = max(res, f[i][j] - a[j] + a[i]);
        }
    }
    cout << res;
}
