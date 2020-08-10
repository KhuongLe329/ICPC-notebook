typedef array<array<ull, S>, S> TMatrix;
static TMatrix A, B, C, D;
inline void Mul(TMatrix &A, const TMatrix &B, TMatrix &C)
{
    for (int i = 0, cnt; i < s; ++i)
        for (int j = 0; j < s; ++j)
        {
            ull val = cnt = 0;
            for (int k = 0; k < s; ++k)
            {
                val += (ull)A[i][k] * B[k][j];
                if (++cnt == Lim) cnt = 0, val %= Mod;
            }
            C[i][j] = val % Mod;
        }
    A = C;
}
inline void Pow(TMatrix A, int b, TMatrix &C)
{
    for (int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j)
            C[i][j] = (i == j);
    for (; b > 0; b >>= 1)
    {
        if (b & 1) Mul(C, A, D);
        Mul(A, A, D);
    }
}
inline void Mul(TMatrix &A, const TMatrix &B, TMatrix &C)
{
    for (int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j) C[i][j] = 0;
    for (int i = 0; i < s; ++i)
    {
        int cnt = 0;
        for (int k = 0; k < s; ++k)
        {
            ull a = A[i][k];
            for (int j = 0; j < s; ++j) C[i][j] += a * B[k][j];
            if (++cnt == Lim)
            {
                cnt = 0;
                for (int j = 0; j < s; ++j) C[i][j] %= Mod;
            }
        }
        if (cnt) for (int j = 0; j < s; ++j) C[i][j] %= Mod;
    }
    A = C;
}
