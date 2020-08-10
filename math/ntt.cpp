#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

const int N = 302;
const int mod = 998244353;

typedef pair<int, int> pii;

struct mod_int {
    int val;

    mod_int(long long v = 0) {
        if (v < 0) v = v % mod + mod;
        if (v >= mod) v %= mod;
        val = v;
    }

    static int mod_inv(int a, int m = mod) {
        // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
        int g = m, r = a, x = 0, y = 1;

        while (r != 0) {
            int q = g / r;
            g %= r; swap(g, r);
            x -= q * y; swap(x, y);
        }

        return x < 0 ? x + m : x;
    }

    explicit operator int() const {
        return val;
    }

    mod_int& operator+=(const mod_int &other) {
        val += other.val;
        if (val >= mod) val -= mod;
        return *this;
    }

    mod_int& operator-=(const mod_int &other) {
        val -= other.val;
        if (val < 0) val += mod;
        return *this;
    }

    static unsigned fast_mod(uint64_t x, unsigned m = mod) {
#if !defined(_WIN32) || defined(_WIN64)
        return x % m;
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in a 32-bit integer.
        unsigned x_high = x >> 32, x_low = (unsigned) x;
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }

    mod_int& operator*=(const mod_int &other) {
        val = fast_mod((uint64_t) val * other.val);
        return *this;
    }

    mod_int& operator/=(const mod_int &other) {
        return *this *= other.inv();
    }

    friend mod_int operator+(const mod_int &a, const mod_int &b) { return mod_int(a) += b; }
    friend mod_int operator-(const mod_int &a, const mod_int &b) { return mod_int(a) -= b; }
    friend mod_int operator*(const mod_int &a, const mod_int &b) { return mod_int(a) *= b; }
    friend mod_int operator/(const mod_int &a, const mod_int &b) { return mod_int(a) /= b; }

    mod_int& operator++() {
        val = val == mod - 1 ? 0 : val + 1;
        return *this;
    }

    mod_int& operator--() {
        val = val == 0 ? mod - 1 : val - 1;
        return *this;
    }

    mod_int operator++(int) { mod_int before = *this; ++*this; return before; }
    mod_int operator--(int) { mod_int before = *this; --*this; return before; }

    mod_int operator-() const {
        return val == 0 ? 0 : mod - val;
    }

    bool operator==(const mod_int &other) const { return val == other.val; }
    bool operator!=(const mod_int &other) const { return val != other.val; }

    mod_int inv() const {
        return mod_inv(val);
    }

    mod_int pow(long long p) const {
        assert(p >= 0);
        mod_int a = *this, result = 1;

        while (p > 0) {
            if (p & 1)
                result *= a;

            a *= a;
            p >>= 1;
        }

        return result;
    }

    friend ostream& operator<<(ostream &stream, const mod_int &m) {
        return stream << m.val;
    }
};
int get(const mod_int &m) {return m.val;}

namespace NTT {
    vector<mod_int> roots = {0, 1};
    vector<int> bit_reverse;
    int max_size = -1;
    mod_int root;

    bool is_power_of_two(int n) {
        return (n & (n - 1)) == 0;
    }

    int round_up_power_two(int n) {
        while (n & (n - 1))
            n = (n | (n - 1)) + 1;

        return max(n, 1);
    }

    // Given n (a power of two), finds k such that n == 1 << k.
    int get_length(int n) {
        assert(is_power_of_two(n));
        return __builtin_ctz(n);
    }

    // Rearranges the indices to be sorted by lowest bit first, then second lowest, etc., rather than highest bit first.
    // This makes even-odd div-conquer much easier.
    void bit_reorder(int n, vector<mod_int> &values) {
        if ((int) bit_reverse.size() != n) {
            bit_reverse.assign(n, 0);
            int length = get_length(n);

            for (int i = 0; i < n; i++)
                bit_reverse[i] = (bit_reverse[i >> 1] >> 1) + ((i & 1) << (length - 1));
        }

        for (int i = 0; i < n; i++)
            if (i < bit_reverse[i])
                swap(values[i], values[bit_reverse[i]]);
    }

    void find_root() {
        max_size = 1 << __builtin_ctz(mod - 1);
        root = 2;

        // Find a max_size-th primitive root of mod.
        while (!(root.pow(max_size) == 1 && root.pow(max_size / 2) != 1))
            root++;
    }

    void prepare_roots(int n) {
        if (max_size < 0)
            find_root();

        assert(n <= max_size);

        if ((int) roots.size() >= n)
            return;

        int length = get_length(roots.size());
        roots.resize(n);

        // The roots array is set up such that for a given power of two n >= 2, roots[n / 2] through roots[n - 1] are
        // the first half of the n-th primitive roots of mod.
        while (1 << length < n) {
            // z is a 2^(length + 1)-th primitive root of mod.
            mod_int z = root.pow(max_size >> (length + 1));

            for (int i = 1 << (length - 1); i < 1 << length; i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * z;
            }

            length++;
        }
    }

    void fft_iterative(int N, vector<mod_int> &values) {
        assert(is_power_of_two(N));
        prepare_roots(N);
        bit_reorder(N, values);

        for (int n = 1; n < N; n *= 2)
            for (int start = 0; start < N; start += 2 * n)
                for (int i = 0; i < n; i++) {
                    mod_int even = values[start + i];
                    mod_int odd = values[start + n + i] * roots[n + i];
                    values[start + n + i] = even - odd;
                    values[start + i] = even + odd;
                }
    }

    const int FFT_CUTOFF = 150;

    vector<mod_int> mod_multiply(vector<mod_int> left, vector<mod_int> right) {
        int n = left.size();
        int m = right.size();

        // Brute force when either n or m is small enough.
        if (min(n, m) < FFT_CUTOFF) {
            const uint64_t ULL_BOUND = numeric_limits<uint64_t>::max() - (uint64_t) mod * mod;
            vector<uint64_t> result(n + m - 1, 0);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    result[i + j] += (uint64_t) ((int) left[i]) * ((int) right[j]);

                    if (result[i + j] > ULL_BOUND)
                        result[i + j] %= mod;
                }

            for (uint64_t &x : result)
                if (x >= mod)
                    x %= mod;

            return vector<mod_int>(result.begin(), result.end());
        }

        int N = round_up_power_two(n + m - 1);
        left.resize(N);
        right.resize(N);

        bool equal = left == right;
        fft_iterative(N, left);

        if (equal)
            right = left;
        else
            fft_iterative(N, right);

        mod_int inv_N = mod_int(N).inv();

        for (int i = 0; i < N; i++)
            left[i] *= right[i] * inv_N;

        reverse(left.begin() + 1, left.end());
        fft_iterative(N, left);
        left.resize(n + m - 1);
        return left;
    }

    vector<mod_int> mod_power(const vector<mod_int> &v, int exponent) {
        assert(exponent >= 0);
        vector<mod_int> result = {1};

        if (exponent == 0)
            return result;

        for (int k = 31 - __builtin_clz(exponent); k >= 0; k--) {
            result = mod_multiply(result, result);

            if (exponent >> k & 1)
                result = mod_multiply(result, v);
        }

        return result;
    }

    vector<mod_int> mod_multiply_all(vector<vector<mod_int>> &polynomials) {
        if (polynomials.empty())
            return {1};
        for(int i = 0 ; i + 1 < polynomials.size() ; i += 2){
            polynomials.pb(mod_multiply(polynomials[i],polynomials[i+1]));
        }
        return polynomials.back();
    }
}

#define int         int64_t

int Pow(int x, int y) {
    if(y < 0) y += mod - 1;
    int res = 1;
    while(y) {
        if(y & 1) res = res * x % mod;
        x = x * x % mod; y >>= 1;
    }
    return res;
}

int Sum(int p, int l, int r, int j) {
    if(p == 1) {
        return (r - l + 1) % mod;
    }
    int res = 0;
    res = Pow(p, (r + 1) * j) - Pow(p, l * j);
    if(res < 0) res += mod;
    int tmp = Pow(p, j) - 1;
    if(tmp == 0) return r % mod;
    if(tmp < 0) tmp += mod;
    res = res * Pow(tmp, mod - 2) % mod;
    return res;
}

vector<vector<mod_int>> f;
vector<mod_int> res;

int n, p, r;

void Solve() {
    cin >> n >> p >> r;
    if(p == 1){
        if(r == 1) cout << (n + 1) % mod << '\n';
        else cout << "0\n";
        return;
    }
    f.clear(); f.reserve(r);
    for(int i = 0; i < r ; ++i) f.push_back(vector<mod_int>{mod - i, 1});
    res = NTT::mod_multiply_all(f);
    int cur = 1;
    for(int i = 0; i <= n; ++i) {
        if(cur >= r) {
           int ans = 0;
           for(int j = 0; j < int(res.size()); ++j) {
               ans = (ans + Sum(p, i, n, j) * get(res[j])) % mod;
           }
           if(ans < 0) ans += mod;
           int fac = 1;
           for(int i = 2; i <= r; ++i) fac = fac * i % mod;
           cout << ans * Pow(fac, mod - 2) % mod << '\n';
           return;
        }
        cur *= p;
    }
    cout << "0\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    int nTest; cin >> nTest;
    while(nTest --) Solve();
}
