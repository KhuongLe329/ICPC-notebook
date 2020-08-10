/*
   alien trick, 1D1D optimization
*/
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
//#define int         int64_t

using namespace std;
typedef pair<int, int> pii;

const int N = (int)3e5 +  2;

int a[N], n, k, cnt[N];
ll s[N], f[N], cur, inf;

ll cost(int l, int r) {
	if(l >= r) return inf;
	return s[r] + s[l] - s[(l + 1 + r) >> 1] - s[(l + r) >> 1] + cur;
}

int lo, hi, mi, x, oldk;
vector<pii> v;
bool check(ll mid) {
    cur = mid; v.clear(); v.pb(0, 0);
    for(int p, i = 1; i <= n; ++i) {
       p = (--lower_bound(v.begin(), v.end(), pii(i + 1, 0)))->se;
       f[i] = f[p] + cost(p, i);
       cnt[i] = cnt[p] + 1;
       for(int j = v.size() - 1; j >= 0; --j) {
            tie(x, oldk) = v[j];
            if(x > i && f[i] + cost(i, x) < f[oldk] + cost(oldk, x)) v.pop_back();
            else {
                lo = x + 1, hi = n + 1;
                while(lo < hi) {
                    mi = lo + hi >> 1;
                    if(f[i] + cost(i, mi) <= f[oldk] + cost(oldk, mi)) hi = mi;
                    else lo = mi + 1;
                }
                if(hi <= n) v.pb(hi, i);
                break;
            }
       }
       if(v.empty()) v.pb(0, i);
    }
    return cnt[n] > k;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    inf = cost(0, n) + 10;
    ll low = 0, mid, high = cost(0, n) + 10;
    while(low <= high) {
        mid = (low + high) / 2;
        if(check(mid)) low = mid + 1;
        else high = mid - 1;
    }
    check(high);
    cout << f[n] - 1ll * k * high;
}
