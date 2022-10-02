//  tested on https://codeforces.com/gym/101667/attachments problem H

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

/// this is also a solution for finding a position where t matches s as many as posible
string s, t;
void solve(char cs, char ct) { ///usage multiply two polynomial n-th degree and m-th degree
    vector<int> a(n + m, 0), b(m, 0), res;
    for(int i = 0; i < n; ++i) a[i] = s[i] == cs;
    for(int i = 0; i < m; ++i) b[i] = t[i] == ct;
    multiply(a, b, res);
    for(int i = m - 1; i < n + m - 1; ++i) sum[i - m + 1] += res[i];
}
