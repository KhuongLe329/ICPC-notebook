#include <bits/stdc++.h>
using namespace std;
using ll  = long long;
using Vi  = vector<int>;
using Pii = pair<int,int>;
#define mp make_pair
#define pb push_back
#define x  first
#define y  second
#define rep(i,b,e) for(int i=(b); i<(e); i++)
#define each(a,x)  for(auto& a : (x))
#define all(x)     (x).begin(),(x).end()
#define sz(x)      int((x).size())
#define tem template<class t,class u,class...w> auto
#define pri(x,y,z) tem operator<<(t&o,u a)->decltype(z,o) { o << *x; y; z; return o << x[1]; }
pri("{}",, a.print())
pri("()",, o << a.x << ", " << a.y)
pri("[]", auto d=""; for (auto i : a) (o << d << i, d = ", "), all(a))
void DD(...) {}
tem DD(t s, u a, w... k) {
    for (int b=1; cerr << *s++, *s && *s - b*44;) b += 2 / (*s*2 - 81);
    cerr << ": " << a; DD(s, k...);
}
#ifdef LOC
#define deb(...) DD("[,\b :] "#__VA_ARGS__, __LINE__, __VA_ARGS__), cerr << endl
#else
#define deb(...)
#endif
#define DBP(...) void print() { DD(#__VA_ARGS__, __VA_ARGS__); }

struct ALCS {
	string A, B;
	vector<Vi> ih;

	ALCS() {}

	ALCS(string s, string t) : A(s), B(t) {
		int n = sz(A), m = sz(B);
		vector<Vi> iv(n+1, Vi(m+1));
		ih.resize(n+1, Vi(m+1));
		iota(all(ih[0]), 0);
		rep(l, 1, n+1) rep(j, 1, m+1) {
			if (A[l-1] != B[j-1]) {
				ih[l][j] = max(iv[l][j-1], ih[l-1][j]);
				iv[l][j] = min(iv[l][j-1], ih[l-1][j]);
			} else {
				ih[l][j] = iv[l][j-1];
				iv[l][j] = ih[l-1][j];
			}
		}
	}

	int operator()(int i, int j, int k) {
		int ret = 0;
		rep(q, j, k) ret += (ih[i][q+1] <= j);
		return ret;
	}

	string recover(int i, int j, int k) {
		string ret;
		while (i > 0 && j < k) {
			if (ih[i][k--] <= j) {
				ret.pb(B[k]);
				while (A[--i] != B[k]);
			}
		}
		reverse(all(ret));
		return ret;
	}
};

void run() {
	string s; cin >> s;
	ALCS alcs(s, s);
	int bestMid = -1, best = -1;

	rep(mid, 0, sz(s)) {
		int alt = alcs(mid, mid, sz(s));
		if (alt > best) {
			bestMid = mid;
			best = alt;
		}
	}

	string ans = alcs.recover(bestMid, bestMid, sz(s));
	cout << best*2 << '\n';
	if (best > 0) cout << ans << ans << '\n';
}

int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(10);
	int t; cin >> t;
	rep(i, 0, t) {
		cout << "Case #" << i+1 << ": ";
		run();
	}
    return 0;
}
