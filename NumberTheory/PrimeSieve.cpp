#pragma once
#ifndef PRIMESIEVE_HEADER
#define PRIMESIEVE_HEADER

#include<vector>

namespace aleaf {
    std::vector<bool> isPrime;
    void primeSieve(int n)
    {
        isPrime.assign(n + 1,1);
        isPrime[0] = isPrime[1] = 0;
        for(int i = 2; i * i <= n; i++) {
            if(isPrime[i]) {
                for(int j = i; i * j <= n; j++) {
                    isPrime[i * j] = 0;
                }
            }
        }
    }
    
    std::vector<int> getPrime(int n)
    {
        primeSieve(n);
    
        std::vector<int> primes;
        for(int i = 2; i <= n; i++) {
            if(isPrime[i]) {
                primes.push_back(i);
            }
        }
        return primes;
    }
    
    std::vector<int> eulerPrimeSieve(int n) {
        std::vector<int> prime;
        std::vector<int> v(n + 1);
        for (int i = 2; i <= n; ++i)
        {
            if (!v[i]) 
            {
                v[i] = i;
                prime.push_back(i);
            }
            for (int j = 0; j < prime.size(); ++j)
            {
                if (prime[j] > v[i] || prime[j] > n / i) break;
                v[i * prime[j]] = prime[j];
            }
        }
        return prime;
    }
}

#endif