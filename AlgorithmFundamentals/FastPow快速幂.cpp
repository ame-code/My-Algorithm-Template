#pragma once

// 模意义下快速幂
int FastPow(int base, int index,int mod)
{
    if (index == 0)
        return 1;
    if (index == 1)
        return base;
    int half = FastPow(base, index / 2, mod) % mod;
    return (index & 1 ? base : 1 ) * half % mod * half % mod;
}

int FastPow(int n, int k, int p)
{
    int r = 1;
    for (; k; k >>= 1, n = n * n % p) {
        if (k & 1) r = r * n % p;
    }
    return r;
}

// 快速幂
int FastPow(int base, int index)
{
    if (index == 0)
        return 1;
    if (index == 1)
        return base;
    int half = FastPow(base, index / 2);
    return (index & 1 ? base : 1 ) * half * half;
}

int FastPow(int n, int k)
{
    int r = 1;
    for (; k; k >>= 1, n = n * n) {
        if (k & 1) r = r * n;
    }
    return r;
}