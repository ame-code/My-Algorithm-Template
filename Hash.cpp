#include<bits/stdc++.h>

class Hash {
private:
    using uint64 = unsigned long long;
    int base = 233;
    std::vector<uint64> hashValue;
public:
    Hash():hashValue(0) {}
    Hash(const std::string& s) {
        calculateHash(s);
    }
    Hash(const std::string& s, int base):base(base) {
        calculateHash(s);
    }
    Hash(const Hash& h):hashValue(h.hashValue), base(base) {}

    void calculateHash(const std::string& s) {
        hashValue.assign(s.length() + 1,0);
        int l = s.length();
        for(int i = 0; i < l; i++) {
            hashValue[i + 1] = hashValue[i] * base + s[i];
        }
    }

    uint64 getHash(int l, int r) {
        return hashValue[r] - hashValue[l - 1];
    }

    void setBase(int base) {
        this->base = base;
    }
};

class HashTwice {
private:
    using uint64 = unsigned long long;
    int base1 = 233;
    int base2 = 137;
    std::vector<std::pair<uint64, uint64>> hashValue;
public:
    HashTwice():hashValue(0) {}
    HashTwice(const int& base1, const int& base2):base1(base1), base2(base2){}
    HashTwice(const std::string s) {

    }

    void calculteateHashTwice(const std::string& s) {
        hashValue.assign(s.length() + 1, std::pair<uint64, uint64>(0 ,0));
        int l = s.length();
        for(int i = 0; i < l; i++) {
            hashValue[i + 1].first = hashValue[i].first * base1 + s[i];
            hashValue[i + 1].second = hashValue[i].second * base2 + s[i];
        }
    }

    std::pair<uint64,uint64> getHashPair(int l, int r) {
        return std::pair<uint64, uint64>(hashValue[r].first - hashValue[l - 1].first, hashValue[r].second - hashValue[l - 1].second);
    }
};