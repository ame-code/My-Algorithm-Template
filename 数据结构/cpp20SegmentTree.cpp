#include<bits/stdc++.h>

using int32 = int;
using uint32 = unsigned int;

using int64 = long long;
using uint64 = unsigned long long;

using int128 = __int128_t;
using uint128 = __uint128_t;

template<typename Policy>
concept SegmentTreePolicy = requires {
    { Policy::merge(int{}, int{}) } -> std::convertible_to<int>;
    { Policy::defaultVal() } -> std::convertible_to<int>;
} && requires (int val) {
    requires (Policy::updateMod == false) ||
    requires {
        { Policy::update(val,int{},int{},int{}) } -> std::same_as<void> ;
    };
};

template<SegmentTreePolicy Policy>
class SegmentTree
{
private:
    struct node {
        int l = 0;
        int r = 0;
        int val = 0;
        std::conditional<Policy::updateMod,int,char[0]>::type lazyFlag={};
    };
    // constexpr const static int root = 1;
    
    // tree存储线段树
    std::vector<node> tree;
    // inputData存储用于建树的数据
    std::vector<int> inputData;

    // 建树的实现
    // int buildLeftEdge = 0, buildRightEdge = 0;
    void build(const int& i, const int& l, const int& r) {
        tree[i].l = l, tree[i].r = r;
        if(l == r) {
            tree[i].val = inputData[l];
            inputData[l] = i;
            return;
        }
        int mid = l + ( (r - l) >> 1 );
        build(i << 1, l, mid);
        build(i << 1 | 1, mid+1, r);
        tree[i].val = Policy::merge(tree[i << 1].val, tree[i << 1 | 1].val);
    }

    // 单点查询的实现
    // 将单点查询视为退化的区间查询
    // 好吧不用写退化的区间查询了
    // 但是前提是没有修改才能用这个单点查询
    int pointQueryIndex = 0;
    int pointQuery() {
        if constexpr (!Policy::updateMod) {
            return tree[ inputData[pointQueryIndex] ].val;
        } else {
            int i = 1;
            while(tree[i].l != tree[i].r) {
                if(tree[i].lazyFlag != 0) {
                    pushDown(i);
                }
                i <<= 1;
                tree[i].r <= pointQueryIndex ? i : i |= 1;
            }
            return tree[i].val;
        }
    }

    // 区间查询的实现
    int rangeQueryLeftEdge = 0, rangeQueryRightEdge = 0;
    int rangeQuery(const int& i) {
        if( tree[i].r < rangeQueryLeftEdge || tree[i].l > rangeQueryRightEdge ) {
            return Policy::defaultVal();
        } else if ( rangeQueryLeftEdge <= tree[i].l && tree[i].r <= rangeQueryRightEdge ) {
            return tree[i].val;
        }

        if constexpr (Policy::updateMod) {
            if(tree[i].lazyFlag != 0) {
                pushDown(i);
            }
        }

        int leftSubTreeVal = rangeQueryLeftEdge <= tree[i].r ? rangeQuery(i << 1) : Policy::defaultVal();
        int rightSubTreeVal = tree[i].l <=rangeQueryRightEdge ? rangeQuery(i << 1 | 1) : Policy::defaultVal();
        return Policy::merge(leftSubTreeVal, rightSubTreeVal);
    }

    // 单点修改的实现(循环实现)
    std::conditional<Policy::updateMod,int,char[0]>::type pointUpdateVal;
    template<bool UM = Policy::updateMod> requires (UM == true)
    void pointUpdate(const int& i) {
        int idx = inputData[i];
        Policy::update(tree[idx].val, tree[idx].r, tree[idx].l, pointUpdateVal);
        while(idx > 1) {
            idx >>= 1;
            tree[idx].val = Policy::merge(tree[i << 1].val,tree[i << 1 | 1].val);
        }
    }

    // 区间修改的实现
    std::conditional<Policy::updateMod,int,char[0]>::type rangeUpdateLeftEdge, rangeUpdateRightEdge, rangeUpdateValue;
    template<bool UM = Policy::updateMod> requires (UM == true)
    void rangeUpdate(const int& i) {
        if (tree[i].l > rangeUpdateRightEdge || tree[i].r < rangeUpdateLeftEdge) {
            return;
        } else if (rangeUpdateLeftEdge <= tree[i].l && tree[i].r <= rangeUpdateRightEdge) {
            Policy::update(tree[i].val, tree[i].r, tree[i].l, rangeUpdateValue);
            tree[i].lazyFlag += rangeUpdateValue;
            return;
        }

        if constexpr (Policy::updateMod) {
            pushDown(i);
        }

        if(tree[i << 1].r >= rangeUpdateLeftEdge)
            rangeUpdate(i << 1);
        if(tree[i << 1 | 1].l <= rangeUpdateRightEdge)
            rangeUpdate(i << 1 | 1);
        tree[i].val = Policy::merge(tree[i << 1].val,tree[i << 1 | 1].val);
    }

    // 延迟更新的实现
    // 通过模板实现不需要时不去实现这个函数
    template<bool UM = Policy::updateMod> requires (UM == true)
    void pushDown(const int& i) {
        node& nd = tree[i];
        int& lazy = nd.lazyFlag;
        Policy::update(tree[i << 1].val, tree[i << 1].r, tree[i << 1].l, lazy);
        Policy::update(tree[i << 1 | 1].val, tree[i << 1 | 1].r, tree[i << 1 | 1].l, lazy);
        tree[i << 1].lazyFlag += lazy;
        tree[i << 1 | 1].lazyFlag += lazy;
        lazy = 0;
}
public:
    SegmentTree() = delete;
    SegmentTree(const int& elementCount):tree(std::vector<node>(4*elementCount+5)),inputData(std::vector<int>(elementCount+1)) {}
    SegmentTree(const std::vector<int> inputData):tree(std::vector<node>(4*inputData.size()+5)),inputData(inputData) {
        this->buildLeftEdge = 1, this->buildRightEdge = inputData.size() - 1;
        build(1, 1, inputData.size() - 1);
    }
    SegmentTree(const SegmentTree& segTree):tree(segTree.tree),inputData(segTree.inputData) {}

    void inputDate() {
        for(int i = 1; i < inputData.size(); i++) {
            std::cin >> inputData[i];
        }
    }

    void build() {
        build(1, 1, inputData.size()-1);
    }

    int pointQuery(const int& index) {
        this->pointQueryIndex = index;
        if constexpr (Policy::updateMod) {
            this->rangeQueryLeftEdge = this->rangeQueryRightEdge = index;
            return rangeQuery(1);
        } else {
            this->pointQueryIndex = index;
            return pointQuery();
        }
    }

    int rangeQuery(const int& leftEdge, const int& rightEdge) {
        this->rangeQueryLeftEdge = leftEdge, this->rangeQueryRightEdge = rightEdge;
        return rangeQuery(1);
    }

    template<bool UM = Policy::updateMod> requires (UM == true)
    void pointUpdate(const int& index, const int& updateValue) {
        this->pointUpdateVal = updateValue;
        pointUpdate(index);
    }

    template<bool UM = Policy::updateMod> requires (UM == true)
    void rangeUpdate(const int& left, const int& right ,const int& updateValue) {
        this->rangeUpdateLeftEdge = left, this->rangeUpdateRightEdge = right;
        this->rangeUpdateValue = updateValue;
        rangeUpdate(1);
    }
};

struct MaxPolicy
{
    constexpr const static bool updateMod = false;
    inline static const int& merge(const int& a,const int& b) {
        return std::max(a,b);
    }
    static int defaultVal() {
        return INT_MIN;
    }
};

struct SumPolicy
{
    constexpr const static bool updateMod = true;
    inline static int merge(const int& a,const int&b) {
        return a + b;
    }
    static int defaultVal() {
        return 0;
    }
    inline static void update(int& val, const int& r, const int& l, const int& updateValue) {
        val = val + (r - l + 1) * updateValue;
    }
};