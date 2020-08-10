#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

struct TWO_SAT{
    TWO_SAT() {}
    vector<vector<int>> e;
    int cnt, k;
    vector<int> num, low, lab, st;
    TWO_SAT(int n) {
        e.resize(n * 2);
        num.resize(e.size());
        low.resize(e.size());
        lab.resize(e.size());
        cnt = k = 0;
    }
    void add(int x, int tx, int y, int ty){
        x = x << 1 ^ tx;
        y = y << 1 ^ ty;
        e[x ^ 1].pb(y);
        e[y ^ 1].pb(x);
    }
    void dfs(int x){
        num[x] = low[x] = ++cnt;
        st.pb(x);
        for (int y : e[x]) if (!lab[y]){
            if (num[y]) low[x] = min(low[x], num[y]);
            else {
                dfs(y);
                low[x] = min(low[x], low[y]);
            }
        }
        if (num[x] == low[x]){
            ++k;
            while(1){
                int y = st.back();
                st.pop_back();
                lab[y] = k;
                if (x == y) break;
            }
        }
    }
    vector<int> solve(){
        for (int x = 0; x < e.size(); ++x) if (!num[x]) dfs(x);
        int n = e.size() >> 1;
        vector<int> ans(n);
        for (int x = 0; x < n; ++x){
            if (lab[x << 1 ^ false] == lab[x << 1 ^ true]) return vector<int>(0);
            ans[x] = lab[x << 1 ^ false] > lab[x << 1 ^ true];
        }
        return ans;
    }
};
/// x != y -> add(x, 1, y, 1), add(x, 0, y, 0)
int n, m, x, y;

#define Task     "test"

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> m;
    TWO_SAT G = TWO_SAT(m);
    bool tx, ty;
    for(int i = 1; i <= n; ++i) {
        cin >> x >> y; tx = ty = 1;
        if(x < 0) tx = 0, x = -x;
        if(y < 0) ty = 0, y = -y;
        G.add(x - 1, tx, y - 1, ty);
    }
    auto ans = G.solve();
    vector<int> res;
    for(int i = 0; i < ans.size(); ++i) if(ans[i]) res.pb(i + 1);
    if(ans.empty()) cout << "NO\n";
    else {
        cout << "YES\n";
        cout << res.size() << '\n';
        for(int x: res) cout << x << ' ';
    }
}
