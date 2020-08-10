#include <bits/stdc++.h>
using namespace std;

typedef long long lli;
typedef deque <lli> BigInt;
const lli LEN = 9;
const lli BASE = pow(10, LEN);
const BigInt Zero(1, 0), One(1, 1);
BigInt Max;

//Refine function
BigInt& Fix(BigInt &a)
{
    a.push_back(0);
    int len = a.size() - 2;
    for (int i = 0; i <= len; ++i)
    {
        lli &ai = a[i];
        a[i + 1] += ai / BASE;
        ai %= BASE;
        if (ai < 0) ai += BASE, --a[i + 1];
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

//Convert from lli or string to BigInt function
BigInt& BIGINT(lli x, BigInt& y)
{
    y.clear();
    while (x > 0)
    {
        y.push_back(x % BASE);
        x /= BASE;
    }
    return Fix(y);
}

BigInt& BIGINT(string s, BigInt& y)
{
    y.clear();
    y.resize(s.size() / LEN + 1);
    for (int i = 0; i < s.size(); ++i)
    {
        int pos = (s.size() - i - 1) / LEN;
        y[pos] = y[pos] * 10 + s[i] - '0';
    }
    return Fix(y);
}

//Convert from BigInt to lli or string function
lli LLI(BigInt& x)
{
    lli y = 0;
    for (int i = x.size() - 1; i >= 0; --i)
        y = y * BASE + x[i];
    return y;
}

//I/O routines
istream& operator >>(istream& cin, BigInt &a)
{
    string s;
    cin >> s;
    BIGINT(s, a);
    return cin;
}

ostream& operator <<(ostream& cout, const BigInt &a)
{
    cout << a.back();
    for (int i = a.size() - 2; i >= 0; --i)
        cout << setw(LEN) << setfill('0') << a[i];
    return cout;
}

//Compare Operators
int Distance(BigInt& a, BigInt& b)
{
    if (a.size() != b.size()) return a.size() - b.size();
    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i]) return a[i] - b[i];
    return 0;
}

#define OP(x) bool operator x (BigInt &a, BigInt &b) {return Distance(a, b) x 0;}
OP(==); OP(!=); OP(>); OP(<); OP(<=); OP(>=);
#undef OP

#define OP(x) bool operator x (BigInt &a, lli b) {BigInt c; return Distance(a, BIGINT(b, c)) x 0;}
OP(==); OP(!=); OP(>); OP(<); OP(<=); OP(>=);
#undef OP

//Arithmetic operators
void operator +=(BigInt& a, BigInt b)
{
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); ++i) a[i] += b[i];
    Fix(a);
}

void operator +=(BigInt& a, lli b)
{
    BigInt c;
    a += BIGINT(b, c);
}

void operator -=(BigInt& a, BigInt b)
{
    for (int i = 0; i < b.size(); ++i) a[i] -= b[i];
    Fix(a);
}

void operator -=(BigInt& a, lli b)
{
    BigInt c;
    a -= BIGINT(b, c);
}

void operator *=(BigInt& a, int b)
{
    for (int i = 0; i < a.size(); ++i) a[i] *= b;
    Fix(a);
}

BigInt operator +(BigInt a, BigInt b)
{
    a += b;
    return a;
}

BigInt operator +(BigInt a, lli b)
{
    a += b;
    return a;
}

BigInt operator -(BigInt a, BigInt b)
{
    a -= b;
    return a;
}

BigInt operator -(BigInt a, lli b)
{
    a -= b;
    return a;
}

BigInt operator *(BigInt a, int b)
{
    a *= b;
    return a;
}

BigInt operator *(BigInt a, BigInt b)
{
    BigInt ans (a.size() + b.size());
    for (int i = 0; i < a.size(); ++i)
    {
        lli carry = 0, s;
        for (int j = 0; j < b.size() || carry > 0; ++j)
        {
            if (j < b.size()) s = ans[i + j] + carry + a[i] * b[j];
            else s = ans[i + j] + carry;
            ans[i + j] = s % BASE;
            carry = s / BASE;
        }
    }
    return Fix(ans);
}

void operator *=(BigInt& a, BigInt b)
{
    a = a * b;
}

void DivideInt(BigInt& a, int b, BigInt& q, lli& r)
{
    for (int i = a.size() - 1; i >= 0; --i)
    {
        r = r * BASE + a[i];
        q.push_front(r / b);
        r %= b;
    }
    Fix(q);
}

BigInt operator /(BigInt a, int b)
{
    BigInt q;
    lli r = 0;
    DivideInt(a, b, q, r);
    return q;
}

void operator /=(BigInt& a, int b)
{
    a = a / b;
}

int operator %(BigInt a, int b)
{
    lli r = 0;
    for (int i = a.size() - 1; i >= 0; --i)
    {
        r = r * BASE + a[i];
        r %= b;
    }
    return r;
}

void DivideBigInt(BigInt& a, BigInt& b, BigInt& q, BigInt& r)
{
    if (b < Max)
    {
        lli t = 0;
        DivideInt(a, LLI(b), q, t);
        BIGINT(t, r);
        return;
    }
    for (int i = a.size() - 1; i >= 0; --i)
    {
        r.push_front(a[i]);
        if (r < b) {q.push_front(0); continue;}
        int low = 2, high = BASE - 1; //thuong nam trong doan 1 den BASE - 1
        BigInt temp;
        while (low <= high)
        {
            int mid = (low + high) >> 1;
            temp = b * mid;
            int x = Distance(temp, r);
            if (x > 0) high = mid - 1;
            else if (x == 0) high = mid, low = mid + 1;
            else low = mid + 1;
        }
        q.push_front(high);
        r -= b * high;
    }
    Fix(q);
}

BigInt operator /(BigInt a, BigInt b)
{
    BigInt q, r;
    DivideBigInt(a, b, q, r);
    return q;
}

BigInt operator %(BigInt a, BigInt b)
{
    BigInt q, r;
    DivideBigInt(a, b, q, r);
    return r;
}

void operator /=(BigInt& a, BigInt b)
{
    BigInt q, r;
    DivideBigInt(a, b, q, r);
    a = q;
}

void operator %=(BigInt& a, BigInt b)
{
    BigInt q, r;
    DivideBigInt(a, b, q, r);
    a = r;
}

BigInt GCD(BigInt a, BigInt b)
{
    while (b != Zero)
    {
        BigInt r = a % b;
        a = b;
        b = r;
    }
    return a;
}

BigInt sqrt(BigInt a)
{
    BigInt d = a, x = (a + 1) / 2;
    while (x < d)
    {
        d = x;
        x = (x + a / x) / 2;
    }
    return d;
}

BigInt pow(BigInt a, BigInt b)
{
    if (b == Zero) return One;
    BigInt t = pow(a, b / 2);
    if (b % 2 == 0) return t * t;
    return t * t * a;
}

int log(int n, BigInt a) // log_n(a)
{
    int ans = 0;
    while (a > One)
    {
        ++ans;
        a /= n;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("TEST.INP", "r", stdin);
    freopen("TEST1.OUT", "w", stdout);
    BIGINT(INT_MAX - 1, Max);
    BigInt x, y, z, t;
    cin >> x >> y;
    //cout << x * y;
    cout << sqrt(x);
}
