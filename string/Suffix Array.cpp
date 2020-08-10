struct SuffixArray
{
    int n;
    int a[maxn] , b[maxn] , mark[maxn];
    int rnk[maxn] , head[maxn] , key[maxn] , l[maxn];
    int modn(int x)
    {
        if(x >= n)x -= n;
        if(x < 0)x += n;
        return x;
    }
    void Build(string s)
    {
        s += 1;
        n = s.size();
        for(int i = 0 ; i < n ; ++i)a[i] = i;
        sort(a,a+n,[&](const int & x , const int & y){
                return s[x] < s[y];
             });
        for(int i = 1 ; i < n ; ++i)
            mark[i] = s[a[i - 1]] != s[a[i]];
        int nKey = 0;
        mark[0] = 1;
        for(int len = 1 ; len <= n ; len *= 2)
        {
            nKey = head[0] = 0;
            for(int i = 0 ; i < n ; ++i)
            {
                b[i] = modn(a[i] - len);
                if(mark[i])
                    head[nKey++] = i;
                key[a[i]] = nKey - 1;
            }
            if(nKey == n)break;
            for(int i = 0 ; i < n ; ++i)
                a[head[key[b[i]]]++] = b[i];
            for(int i = 1 ; i < n ; ++i)
                mark[i] |= key[modn(a[i] + len)] != key[modn(a[i - 1] + len)];
        }
        for(int i = 0 ; i < n ; ++i)
            rnk[a[i]] = i;
    }
    void BuildLCP()
    {
        int q = 0;
        l[0] = 0;
        for (int i = 0; i < n - 1 ; ++i)
        {
            int j = a[rnk[i] - 1];
            while (s[i + q] == s[j + q]) ++q;
            l[rnk[i]] = q;
            if (q > 0) --q;
        }
    }
}Suf;
