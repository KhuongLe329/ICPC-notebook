const lli Radix = 1e18;
const int gd = 18;
const int nd = 3;
class TNumber: public array<lli, nd>
{
public:
    TNumber& operator = (lli x)
    {
        fill(0);
        self[0] = x;
        return self;
    }
    TNumber& operator += (const TNumber& other)
    {
        for (int i = 0; i < nd; ++i)
        {
            self[i] += other[i];
            if (self[i] > Radix)
            {
                self[i] -= Radix;
                ++self[i + 1];
            }
        }
        return self;
    }
    void Print()
    {
        int i = nd - 1;
        while (i > 0 && self[i] == 0) --i;
        cout << self[i];
        for (--i; i >= 0; --i)
            cout << setw(gd) << setfill('0') << self[i];
    }
};

const int Radix = 1e9;
const int gd = 9;
const int nDigits = 30;
struct TNumber
{
    array<int, nDigits> d;
    TNumber()
    {
    }
    TNumber (int x)
    {
        self = x;
    }
    TNumber& operator = (int x)
    {
        fill(d.begin(), d.end(), 0);
        for (int i = 0; x > 0; ++i, x /= Radix)
            d[i] = x % Radix;
        return self;
    }
    TNumber& operator = (const TNumber& other)
    {
        copy(other.d.begin(), other.d.end(), d.begin());
        return self;
    }
    TNumber& operator += (const TNumber& other)
    {
        for (int i = 0; i < nDigits; ++i)
        {
            d[i] += other.d[i];
            if (d[i] >= Radix)
            {
                d[i] -= Radix;
                ++d[i + 1];
            }
        }
        return self;
    }
    TNumber& operator -= (const TNumber& other)
    {
        for (int i = 0; i < nDigits; ++i)
        {
            d[i] -= other.d[i];
            if (d[i] < 0)
            {
                d[i] += Radix;
                --d[i + 1];
            }
        }
        return self;
    }
    void Print() const
    {
        int i = nDigits - 1;
        while (i > 0 && d[i] == 0) --i;
        cout << d[i];
        for (--i; i >= 0; --i)
        {
            cout << setw (gd) << setfill ('0');
            cout << d[i];
        }
    }
};

inline int Sign(lli x)
{
    if (x < 0) return -1;
    else if (x > 0) return 1;
    else return 0;
}
struct TBigNum
{
    const lli Radix = 1e9;
    const int nd = 4;
    int sgn;
    array<lli, 4> d;
    TBigNum()
    {
        fill(d.begin(), d.end(), 0);
    }
    TBigNum(lli x)
    {
        sgn = Sign(x);
        x = abs(x);
        fill(d.begin(), d.end(), 0);
        for (int i = 0; i < nd; ++i)
        {
            d[i] = x % Radix; x /= Radix;
            if (x == 0) break;
        }
    }
    inline TBigNum operator * (const TBigNum& other) const
    {
        TBigNum res;
        res.sgn = sgn * other.sgn;
        if (res.sgn == 0)
        {
            fill(res.d.begin(), res.d.end(), 0);
            return res;
        }
        for (int i = 0; i < nd; ++i)
            for (int j = 0; j < nd; ++j)
            {
                int k = i + j;
                res.d[k] += d[i] * other.d[j];
                while (k < nd && res.d[k] > Radix)
                {
                    res.d[k + 1] += res.d[k] / Radix;
                    res.d[k] %= Radix;
                    ++k;
                }
            }
        return res;
    }
    inline bool operator > (const TBigNum& other)
    {
        if (sgn != other.sgn) return sgn > other.sgn;
        if (sgn == 0) return 0;
        int cmp = 0;
        for (int i = nd - 1; i >= 0; --i)
            if (d[i] != other.d[i])
            {
                cmp = Sign(d[i] - other.d[i]);
                break;
            }
        return cmp * sgn > 0;
    }
};
