#define Read(t) (sieve[t >> 6] & 1 << (t >> 1 & 31))
static int sieve[(N + 1 >> 1) + 31 >> 5];

int sqrtN = sqrt(N), i, j, k;
for (i = 3; i <= sqrtN; i += 2)
    if (Read(i) == 0)
        for (j = i * i, k = i << 1; j <= N; j += k)
            sieve[j >> 6] |= 1 << (j >> 1 & 31);
