/*
  OPTCUT spoj
*/
#include<bits/stdc++.h>
#define For(i, a, b)  for(int i = a; i <= b; ++i)
#define Ford(i, a, b) for(int i = a; i >= b; --i)
#define ll            long long
#define pb            push_back
 
const int N = 2e3 + 7;
 
using namespace std;
 
int n, m, a[N], pos[N][N], dp[N][N], c[N][N];
 
void Init()
{
    cin >> n;
    For(i, 1, n)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    For(i, 1, n)
    For(j, i, n)
    c[i][j] = a[j] - a[i - 1];
}
 
void Solve()
{
     fill_n(&dp[0][0], N * N, 1e9 + 1);
     For(i, 1, n) dp[i][i] = 0, pos[i][i] = i;
     For(len, 2, n)
     {
         For(i, 1, n - len + 1)
         {
             int j = i + len - 1;
             For(k, pos[i][j - 1], pos[i + 1][j])
             {
                 m = c[i][j] + dp[i][k - 1] + dp[k][j];
                 if(m < dp[i][j])
                 {
                     dp[i][j] = m;
                     pos[i][j] = k;
                 }
             }
         }
     }
     cout << dp[1][n];
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //READ; WRITE;
    Init();
    Solve();
}
