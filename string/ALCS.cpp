/*
    https://codeforces.com/gym/103652/problem/F
    copied from teapotd
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

struct ALCS {
	string A, B;
	vector<vector<int>> ih;

	ALCS() {}

	ALCS(string s, string t) : A(s), B(t) {
		int n = A.size(), m = B.size();
		vector<vector<int>> iv(n+1, vector<int>(m+1));
		ih.resize(n+1, vector<int>(m+1));
		iota(ih[0].begin(), ih[0].end(), 0);
		for(int l = 1; l <= n; ++l) {
            for(int j = 1; j <= m; ++j) {
                if (A[l-1] != B[j-1]) {
                    ih[l][j] = max(iv[l][j-1], ih[l-1][j]);
                    iv[l][j] = min(iv[l][j-1], ih[l-1][j]);
                } else {
                    ih[l][j] = iv[l][j-1];
                    iv[l][j] = ih[l-1][j];
                }
            }
		}
	}

	int operator()(int i, int j, int k) {
		int ret = 0;
		for(int q = j; q < k; ++q)
            ret += (ih[i][q+1] <= j);
		return ret;
	}

	string recover(int i, int j, int k) {
		string ret;
		while (i > 0 && j < k) {
			if (ih[i][k--] <= j) {
				ret.push_back(B[k]);
				while (A[--i] != B[k]);
			}
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};

void solve() {
    string s; cin >> s;
	ALCS alcs(s, s);
	int bestMid = -1, best = -1;

	for(int mid = 0; mid < (int)s.size(); ++mid) {
		int alt = alcs(mid, mid, (int)s.size());
		if (alt > best) {
			bestMid = mid;
			best = alt;
		}
	}

	string ans = alcs.recover(bestMid, bestMid, s.size());
	cout << best*2 << '\n';
	if (best > 0) cout << ans << ans << '\n';
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
