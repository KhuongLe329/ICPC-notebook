const int N = int(2e5) + 7;
const int logN = 18;
int n, lg[N], a[N], M[N][logN + 1], m[N][logN + 1];
// usage
int GetM(int l, int r) {
    int x = lg[r - l + 1];
    return max(M[l][x], M[r - (1 << x) + 1][x]);
}
int Getm(int l, int r) {
    int x = lg[r - l + 1];
    return min(m[l][x], m[r - (1 << x) + 1][x]);
}
//prepare
for(int i = 1; i <= n; ++i) {
    M[i][0] = m[i][0] = a[i];
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
