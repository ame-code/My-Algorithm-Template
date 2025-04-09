#include<bits/stdc++.h>

using int64 = long long;
using uint64 = unsigned long long;

using int128 = __int128_t;
using uint128 = __uint128_t;

class UnionFindSet
{
private:
    std::vector<int> parent,rank;
public:
    UnionFindSet() = delete;
    explicit UnionFindSet(size_t n):parent(n, 0),rank(n, 0){
        for(size_t i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    UnionFindSet(const UnionFindSet& ufs):parent(ufs.parent),rank(ufs.rank){}
    UnionFindSet(UnionFindSet&&) = default;
    UnionFindSet& operator=(UnionFindSet&&) = default;

    int root(int x) {
        assert(x >= 0 && x < parent.size());
        return parent[x] = (parent[x] == x ? x : root(parent[x]));
    }

    void merge(int x, int y) {
        x = root(x), y = root(y);
        if(x == y)
            return;
        if(rank[x] < rank[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if(rank[x] == rank[y]) {
                rank[x]++;
            }
        }
    }
};