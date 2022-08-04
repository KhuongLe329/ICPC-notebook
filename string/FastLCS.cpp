/*
    https://codeforces.com/gym/103652/problem/F
*/
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
//#define int         int64_t

using namespace std;

const int N = (int)3e3 + 3;
const int M = N / 64 + 1;
const int nAlpha = 'z' - 'a';
const int mod = 998244353;
typedef pair<int, int> pii;
typedef long double ld;
typedef unsigned long long ull;

struct Bitset {
    ull t[M];
    Bitset() {memset(t, 0, sizeof t);}
    void set(int p) {t[p >> 6] |= 1llu << (p & 63);}
    void clr() {memset(t, 0, sizeof t);}
    Bitset& shift() {
        ull last = 0llu;
        for(int i = 0; i < M; ++i) {
            ull cur = t[i] >> 63;
            (t[i]<<= 1) |= last; last = cur;
        }
        return *this;
    }
    int count() {
        int res = 0;
        for(int i = 0; i < M; ++i)
            res += __builtin_popcountll(t[i]);
        return res;
    }
    Bitset& operator = (const Bitset& rhs) {
        memcpy(t, rhs.t, sizeof t); return *this;
    }
    Bitset& operator &= (const Bitset& rhs) {
        for(int i = 0; i < M; ++i) t[i] &= rhs.t[i];
        return *this;
    }
    Bitset& operator |= (const Bitset& rhs) {
        for(int i = 0; i < M; ++i) t[i] |= rhs.t[i];
        return *this;
    }
    Bitset& operator ^= (const Bitset& rhs) {
        for(int i = 0; i < M; ++i) t[i] ^= rhs.t[i];
        return *this;
    }
    friend Bitset operator - (const Bitset& lhs, const Bitset& rhs) {
        ull last = 0; Bitset res;
        for(int i = 0; i < M; ++i){
            ull cur = (lhs.t[i]<rhs.t[i]+last);
            res.t[i] = lhs.t[i]-rhs.t[i]-last;
            last = cur;
        }
        return res;
    }
} p[nAlpha + 1], f, g;

string s, res;
int n, ans, cur, pos;
int dp[N][N], trace[N][N];

int fastLCS(int la, int b, int lb) {
    p[s[la] - 'a'].set(la - 1);
    f.clr();
    for(int i = 0; i < lb; ++i) {
        g = f, g |= p[s[b + i] - 'a'];
        f.shift(); f.set(0);
        f = g - f, f ^= g, f &= g;
    }
    return f.count();
}

void solve() {
    cin >> s;
    n = s.size(), s = ' ' + s;
    for(int i = 0; i <= nAlpha; ++i)
        p[i].clr();
    ans = 0;
    for(int i = 1; i < n; ++i) {
        cur = fastLCS(i, i + 1, n - i);
        if(ans < cur) ans = cur, pos = i;
    }
    cout << ans * 2 << '\n';
    if(ans) {
        for(int i = 1; i <= pos; ++i) {
            fill(dp[i], dp[i] + n - pos + 1, 0);
            fill(trace[i], trace[i] + n - pos + 1, 0);
        }
        for(int i = 1; i <= pos; ++i) {
            for(int j = 1; j + pos <= n; ++j) {
                if(s[i] == s[j + pos]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    trace[i][j] = 1;
                } else {
                    if(dp[i - 1][j] > dp[i][j - 1]) {
                        dp[i][j] = dp[i - 1][j];
                        trace[i][j] = 2;
                    } else {
                        dp[i][j] = dp[i][j - 1];
                        trace[i][j] = 3;
                    }
                }
            }
        }
        int i = pos, j = n - pos;
        res = "";
        while(i > 0 && j > 0) {
            if(trace[i][j] == 1) {
                res += s[i];
                --i, --j;
            } else if(trace[i][j] == 2) --i;
            else --j;
        }
        reverse(res.begin(), res.end());
        cout << res << res << '\n';
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
    int T; cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
