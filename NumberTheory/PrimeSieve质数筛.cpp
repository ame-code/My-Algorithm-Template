#include<vector>
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
    isPrime.assign(n + 1,1);
    isPrime[0] = isPrime[1] = 0;
    for(int i = 2; i * i <= n; i++) {
        if(isPrime[i]) {
            for(int j = i; i * j <= n; j++) {
                isPrime[i * j] = 0;
            }
        }
    }

    std::vector<int> primes;
    for(int i = 2; i <= n; i++) {
        if(isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

std::vector<int> prime; // 这里储存筛出来的全部质数
auto euler_Prime = [&](int n) -> void {
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
};