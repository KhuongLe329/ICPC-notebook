//
//  main.cpp
//  CP
//  tested on https://codeforces.com/gym/101667/attachments problem H
//  Created by Khuong Le on 2022/09/16.
//

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define pb push_back
#define ll long long
#define fi first
#define se second
//#define int int64_t

const int N = (int)2e5 + 7;

#define M_PI           3.14159265358979323846
typedef pair<int, int> pii;
typedef complex<double> base;
  
void fft(vector <base> &a, bool invert)
{
    int n = (int)a.size();
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*M_PI/len*(invert?-1:1);
        base wlen(cos(ang),sin(ang));
        for (int i=0;i<n;i+=len){
            base w(1);
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert){
        for (int i=0;i<n;i++) a[i] /= n;
    }
}
  
void multiply(const vector<int> &a,const vector<int> &b,vector<int> &res)
{
    vector <base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max((int)a.size(), (int)b.size())) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    res.resize(n);
    for (int i=0;i<n;i++) res[i] = int(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
}

int n, m, sum[N];
string s, t;

void solve(char cs, char ct) {
    vector<int> a(n + m, 0), b(m, 0), res;
    for(int i = 0; i < n; ++i) a[i] = s[i] == cs;
    for(int i = 0; i < m; ++i) b[i] = t[i] == ct;
    multiply(a, b, res);
    for(int i = m - 1; i < n + m - 1; ++i) sum[i - m + 1] += res[i];
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
    cin >> n >> m >> s >> t;
    reverse(t.begin(), t.end());
    solve('S', 'R');
    solve('R', 'P');
    solve('P', 'S');
    int ans = 0;
    for(int i = 0; i < n; ++i) ans = max(ans, sum[i]);
    cout << ans;
}

