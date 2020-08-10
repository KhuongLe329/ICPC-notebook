/// template 1
int operator*(const pii& x, const pii& y) {return x.fi * y.se - y.fi * x.se;}
pii operator-(const pii& x, const pii& y) {return {x.fi - y.fi, x.se - y.se};}
int ccw(const pii& a, const pii& b, const pii& c) {return (c - b) * (b - a);}
vector<pii> hull; int sz, low, high, mid, type, ptr, res; /// type = 1 -> dec a, -1 -> inc a
void init(int _type) {type = _type, hull.clear(), sz = ptr = 0;}
void push(const pii& p) {
    for(; sz > 1 && ccw(hull[sz - 2], hull[sz - 1], p) * type >= 0; hull.pop_back(), --sz);
    hull.pb(p); ++sz;
}
int val(int i, int x) {return (i < sz && i >= 0)? hull[i].fi * x + hull[i].se: -inf;}
int get(int x) {
    if(hull.empty()) return -inf;
    low = 0, high = sz - 1;
    while(low <= high) {
        mid = (low + high) >> 1;
        if(val(mid, x) <= val(mid + 1, x)) low = mid + 1;
        else high = mid - 1;
    }
    return max(val(low, x), val(high, x));
}

/// template 2
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
#define int         int64_t

using namespace std;

const int N = 2003;

int n, res, maxf, f[N][N], a[N], b[N];

struct TLine {
    int a, b;
    TLine() {}
    TLine(int a, int b): a(a), b(b) {}
    int Get(int x) {return a * x + b;}
};
struct CHT {
    vector<TLine> cvh; int l, r, mid, ans, ind;
    void clear() {cvh.clear(); ind = 0;}
    bool Bad(const TLine& d, const TLine& e, const TLine& f) {
        /// intersection(d, e) has x-coordinate(e.b - d.b) / (e.a - d.a) = x1
        /// intersection(d, f) has x-coordinate(f.b - d.b) / (f.a - d.a) = x2
        /// true if x1 < x2 /// Convexhull get Max
        return (e.b - d.b) * (f.a - d.a) < (f.b - d.b) * (e.a - d.a);
    }
    void add(const TLine& line) {
        int cur = cvh.size();
        while(cur && cvh[cur - 1].a == line.a && cvh[cur - 1].b < line.b) cvh.pop_back(), --cur;
        if(cur == 0 || cvh[cur - 1].a < line.a) {
            while(cur >= 2 && Bad(cvh[cur - 2], cvh[cur - 1], line)) cvh.pop_back(), --cur;
            cvh.pb(line);
        }
    }
    int Get(int x) {
        l = 0, r = cvh.size() - 1;
        while(l <= r) {
            mid = (l + r) >> 1;
            if(mid == cvh.size() - 1) l = mid, r = mid - 1;
            else if(cvh[mid].Get(x) < cvh[mid + 1].Get(x)) l = mid + 1;
            else r = mid - 1;
        }
        ans = LLONG_MIN;
        if(r >= 0 && r <= cvh.size() - 1) ans = max(ans, cvh[r].Get(x));
        if(l >= 0 && l <= cvh.size() - 1) ans = max(ans, cvh[l].Get(x));
        return ans;
    }
} row, col[N];

int sqr(int x) {return x * x;}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i], a[i] += a[i - 1];
    for(int i = 1; i <= n; ++i) cin >> b[i], b[i] += b[i - 1];
    res = 0;
    for(int i = 1; i <= n; ++i) {
        row.clear();
        for(int j = 1; j <= n; ++j) {
            maxf = -sqr(a[i - 1]) - sqr(b[j - 1]);
            if(j > 1 && i > 1) {
                col[j - 1].add(TLine(2 * a[i - 1], f[i - 1][j - 1] - sqr(a[i - 1])));
                row.add(TLine(2 * b[j - 1], f[i - 1][j - 1] - sqr(b[j - 1])));
                maxf = max({maxf, row.Get(b[j - 1]) - sqr(b[j - 1]),
                           col[j - 1].Get(a[i - 1]) - sqr(a[i - 1])});
            }
            f[i][j] = maxf + (a[i] - a[i - 1]) * (b[j] - b[j - 1]);
            res = max(res, f[i][j] - sqr(a[n] - a[i]) - sqr(b[n] - b[j]));
            //cout << f[i][j] << ' ';
        }
        //cout << '\n';
    }
    cout << res;
}
