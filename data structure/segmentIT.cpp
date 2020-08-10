#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

const ll Cmax = (ll)1e18;
const int N = int(1e5) + 7;

vector<ll> v;
struct line
{
    ll a, b;
    line (ll a = 0, ll b = Cmax): a(a), b(b) {}
    ll GetVal(int x) {return a * v[x - 1] + b;}
};
struct TSegment
{
    int l, r, mid;
    line cur;
    TSegment* left;
    TSegment* right;

    TSegment (int l = 0, int r = 0): l(l), r(r)
    {
        mid = (l + r) >> 1;
        cur = line();
        if(l == r)
        {
            left = right = NULL;
            return;
        }
        left = new TSegment(l, mid);
        right = new TSegment(mid + 1, r);
    }

    void Update(int x, int y, line val)
    {
        if(l > y || r < x) return;
        if(x <= l && r <= y)
        {
            ll lcur = cur.GetVal(l);
            ll rcur = cur.GetVal(r);
            ll lval = val.GetVal(l);
            ll rval = val.GetVal(r);
            if(lcur >= lval && rcur >= rval) {cur = val; return;}
            if(lcur <= lval && rcur <= rval) return;
            ll mval = val.GetVal(mid);
            ll mcur = cur.GetVal(mid);
            if(lcur >= lval && mcur >= mval)
            {
                right -> Update(x, y, cur);
                cur = val;
                return;
            }
            if(lcur <= lval && mcur <= mval)
            {
                right -> Update(x, y, val);
                return;
            }
            if(mcur >= mval && rcur >= rval)
            {
                left -> Update(x, y, cur);
                cur = val;
                return;
            }
            if(mcur <= mval && rcur <= rval)
            {
                left -> Update(x, y, val);
                return;
            }
        }
        left -> Update(x, y, val);
        right -> Update(x, y, val);
    }

    ll Query(int x)
    {
        if(l > x || r < x) return Cmax;
        ll res = cur.GetVal(x);
        if(l == r) return res;
        res = min(res, left -> Query(x));
        res = min(res, right -> Query(x));
        return res;
    }
};
struct TRunner {
    int l, r;
    ll t;
    bool operator<(const TRunner& o)const& {
        return l < o.l || (l == o.l && r < o.r);
    }
} run[N];
int n, k;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "relay"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> run[i].l >> run[i].r >> run[i].t;
        v.pb(run[i].l), v.pb(run[i].r);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sort(run + 1, run + n + 1);
    ll res = Cmax, f;
    TSegment Min = TSegment(1, int(v.size()));
    for(int i = 1; i <= n; ++i) {
       run[i].l = lower_bound(v.begin(), v.end(), run[i].l) - v.begin() + 1;
       run[i].r = lower_bound(v.begin(), v.end(), run[i].r) - v.begin() + 1;
       if(v[run[i].l - 1] == 0) f = 0;
       else f = Min.Query(run[i].l);
       Min.Update(run[i].l, run[i].r, line(run[i].t, f - v[run[i].l - 1] * run[i].t));
       if(v[run[i].r - 1] == k) res = min(res, Min.Query(run[i].r));
    }
    cout << res;
}
