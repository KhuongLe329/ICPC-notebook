#include <bits/stdc++.h>
#define pb          push_back
#define ll          int64_t
#define ff          first
#define ss          second
#define mp          make_pair

using namespace std;

const int N = int(1e6) + 3;
typedef pair<ll, ll> pii;
vector<int> euler(N, -1), primes;

void Genprime() {
 	for(int i = 2;i < N; ++i) {
 		if(euler[i] == -1) {
 			primes.pb(i); euler[i] = i-1;
 			for(int j = 2 * i; j < N; j += i) {
 				if(euler[j] == -1) euler[j] = j;
 				euler[j] = (euler[j] / i) * (i - 1);
 			}
 		}
 	}
}

ll Pow(ll x, ll y, ll mod = (1ll << 62)) {
    ll res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

int inverse(int x, int m) {
    if(x == 1) return 1;
    return Pow(x, euler[m] - 1, m) % m;
}

int ff(int n, int p, int q) {
    int x = 1, y = Pow(p, q);
    for(int i = 2; i <= n; ++i)
        if(i % p) x = 1ll * x * i % y;
    return x % y;
}

int f(int n, int m, int p, int q) {
    int r = n - m, x = Pow(p, q);
 	int e0 = 0, eq = 0;
 	int mul = (p == 2 && q >= 3)? 1: -1;
 	int cr = r, cm = m, carry = 0, cnt = 0;
 	while(cr||cm||carry) {
 		cnt++;
 		int rr = cr%p, rm = cm%p;
 		if(rr + rm + carry >= p) {
 			e0++;
 			if(cnt>=q)eq++;
 		}
 		carry = (carry+rr+rm)/p;
 		cr/=p; cm/=p;
 	}
 	mul = Pow(p, e0) * Pow(mul, eq);
 	int ret = (mul % x + x) % x;
 	int temp = 1;
 	for(int i = 0;;i++) {
 		ret = ((ret*ff((n/temp)%x, p, q)%x)%x*(inverse(ff((m/temp)%x, p, q), x)%x*inverse(ff((r/temp)%x, p, q), x)%x)%x)%x;
 		if(temp>n/p && temp>m/p && temp>r/p) break;
 		temp *= p;
 	}
 	return (ret % x + x) % x;
}

int nCr_mod_m(int n, int r, int m) {
    int temp = m;
    vector<int> num, rem;
    for(int i = 0; primes[i] <= m && i < int(primes.size()); i++) {
        if(m % primes[i] == 0) {
            int p = primes[i], q = 0;
            while(m % p == 0) ++q, m /= p;
            num.push_back(Pow(p, q));
            rem.push_back(f(n, r, p, q));
        }
    }
    m = temp;
    int ans = 0;
    temp = 0;
    for(int i = 0;i < int(num.size()); i++)
        ans = (ans+rem[i]*(temp = m/num[i])*inverse(temp, num[i]))%m;
    return ans;
}

ll fac[N], inv[N];
ll nCk(ll n, ll k, ll mod) {return 1ll * fac[n] * inv[k] % mod * inv[n - k] % mod;}
ll nCk2(ll n, ll k, ll mod) {
    if(n <= int(1e6)) return nCk(n, k, mod);
    ll res = inv[k];
    for(ll i = 1; i <= k; ++i) res = res * (n - k + i) % mod;
    return res;
}

ll NCK(ll n, ll k, ll mod) {
    if(mod <= int(1e6)) return nCr_mod_m(n, k, mod);
    if(n < N) return nCk(n, k, mod);
    return nCk2(n, k, mod);
}

#define Task        "flowers"

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    int t, mod, n, m, k;
    cin >> t >> mod;
    fac[0] = 1;
    for(int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = Pow(fac[N - 1], mod - 2, mod);
    for(int i = N - 2; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
    if(mod <= int(1e6)) Genprime();
    while(t --) {
        cin >> n >> m >> k;
        cout << m * Pow(m - 1, k, mod) % mod * NCK(n - 1, k, mod) % mod << '\n';
    }
}
