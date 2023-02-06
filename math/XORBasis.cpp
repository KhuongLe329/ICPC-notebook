struct TXORBasis { // M = log(value)
    int basis[M], sz, mx;
    TXORBasis() {
        fill(basis, basis + M, 0);
        sz = 0; mx = -1;
    }
    void insert(int x) {
        for(int i = M - 1; i >= 0; --i) {
            if(!((x >> i) & 1)) continue;
            if(!basis[i]) {
                basis[i] = x;
                ++sz;
                return;
            }
            x ^= basis[i];
        }
    }
    void mergeBasis(TXORBasis& other) {
        for(int i = M - 1; i >= 0; --i) {
            if(!other.basis[i]) continue;
            insert(other.basis[i]);
        }
    }
    int kQuery(int k) {
        int ans = 0, tot = 1 << sz;
        for (int low, i = M - 1; i >= 0; --i) {
            if (basis[i]) {
                low = tot / 2;
                if ((low < k && (ans & 1 << i) == 0) ||
                    (low >= k && (ans & 1 << i) > 0)) ans ^= basis[i];
                if (low < k) k -= low;
                tot /= 2;
            }
        }
        return ans;
    }
    int getMax() {
        if(mx != -1) return mx;
        mx = 0;
        for(int i = M - 1; i >= 0; --i) {
            if(!basis[i]) continue;
            if((mx >> i) & 1) continue;
            mx ^= basis[i];
        }
        return mx;
    }
};