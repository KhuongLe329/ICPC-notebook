  
#include <bits/stdc++.h>
#define Task        "sort"
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

const int N = int(2e5) + 7;
const int logN = 18;
int n, lg[N], a[N], M[N][logN + 1], m[N][logN + 1];

int GetM(int l, int r) {
    int x = lg[r - l + 1];
    return max(M[l][x], M[r - (1 << x) + 1][x]);
}
int Getm(int l, int r) {
    int x = lg[r - l + 1];
    return min(m[l][x], m[r - (1 << x) + 1][x]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i]; M[i][0] = m[i][0] = a[i];
        if(i != 1) {
            if(i == (1 << (lg[i - 1] + 1))) lg[i] = lg[i - 1] + 1;
            else lg[i] = lg[i - 1];
        }
    }
    for(int j = 1; j <= logN; ++j) {
       for(int i = 1; i <= n; ++i) {
          M[i][j] = max(M[i][j - 1], M[min(i + (1 << (j - 1)), n)][j - 1]);
          m[i][j] = min(m[i][j - 1], m[min(i + (1 << (j - 1)), n)][j - 1]);
       }
    }
    int pre = 1, res = 1;
    for(int i = 1; i <= n; ++i) {
        if(GetM(pre, i) <= Getm(i + 1, n)) {
            ++res; pre = i + 1;
        }
    }
    cout << res;
}
