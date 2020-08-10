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
