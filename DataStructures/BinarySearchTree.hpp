#pragma once
#ifndef BINARYSEARCHTREE_HEADER
#define BINARYSEARCHTREE_HEADER

#include<vector>
#include<climits>

class BinarySearchTree
{
private:
    struct node
    {
        int left = 0;
        int right = 0;
        int value = 0;
        // size表示左子树+右子树+本身共多少元素
        int size = 0;
        // cnt表示有多少个相同的值
        int cnt = 0;
    };
    std::vector<node> tree;
    // count表示现在二叉搜索树上有几个节点
    int count = 0;
    //插入某一值
    int insertedValue = 0;
    void insertAchieve(int i)
    {
        // 如果能搜索到该点,说明一定能在该点或者其左右子树中插入一个值
        tree[i].size++;
        // 如果值相等,说明找到了该值,则直接让该点存储的值的数量+1
        if(tree[i].value == insertedValue)
        {
            tree[i].cnt++;
            return;
        }
        // 如果不相等,则搜索的值一定大于当前节点或者小于当前节点
        // 那么我们继续向左子树或者右子树寻找

        // 如果搜索的值比当前节点的值小,说明搜索的值应当要插入左子树
        // 则进入判断,尝试在左子树中插入值
        else if(insertedValue < tree[i].value)
        {
            // 如果左子树不存在,则不可能再向下寻找
            // 同时也意味着应当在该处插入值,因为根据二叉搜索树的性质不可能找到更小的值了
            if(tree[i].left == 0)
            {
                // 先让节点数+1,然后让当前节点的左子树指向节点数
                tree[i].left = ++count;
                // 初始化该节点的左子树,即插入搜索的值
                tree[count] = {0, 0, insertedValue, 1, 1};
                return;
            }
            // 如果存在左子树
            else
            {
                // 则继续在左子树中寻找
                // 直到该搜索值在左子树中寻找到等于其的值
                // 或者发现不存在该值后插入,然后插入结束
                insertAchieve(tree[i].left);
            }
        }
        // 如果不是小于当前节点,根据二叉搜索树的性质则该搜索值一定大于当前节点值
        // 说明我们应当在右子树中寻找并尝试插入
        else
        {
            // 与上面左子树同理,如果不存在右子树,说明该值不存在于树中,需要插入
            if(tree[i].right == 0)
            {
                tree[i].right = ++count;
                tree[count]={0, 0, insertedValue , 1, 1};
                return;
            }
            // 存在右子树则在右子树中继续寻找
            else
            {
                insertAchieve(tree[i].right);
            }
        }
        return;
    }
    //查询小于某一值的值个数
    int queriedValue=0;
    int queryRankAchieve(int i)
    {
        // 查询到了树中某个节点表示的值与查询的值相等
        // 根据二叉搜索树性质可知左子树中的节点存储的值都是小于查询值的值
        // 所以答案就是左子树的大小
        if(tree[i].value == queriedValue)
        {
            // 如果不存在左子树, 则返回0
            if(tree[i].left == 0)
                return 0;
            // 如果存在,则返回左子树大小
            else 
                return tree[tree[i].left].size;
        }
        // 如果当前节点值与查询值不相等,则考虑查询值大于当前节点值或者小于的情况
        // 考虑小于的情况
        // 如果小于,则进入对左子树的判断中
        else if(queriedValue < tree[i].value)
        {
            // 如果左子树不存在,那么就是0
            if(tree[i].left == 0)
                return 0;
            // 如果左子树存在,那么答案就是查询到的左子树中小于查询值的值个数
            else
                return queryRankAchieve(tree[i].left);
        }
        // 进入对查询值大于节点值情况的判断
        else
        {
            // 不存在右子树,则当前节点与当前节点的左子树都是小于查询值的值
            // 直接返回当前节点和左子树大小的和
            // 但是因为右子树不存在所以tree[i].size就是答案
            if(tree[i].right == 0)
                return tree[i].size;
            // 如果存在右子树,则答案为当前节点与左子树大小的和(tree[i].size-tree[tree[i].right].size),加上在右子树中查找到的小于查询值的值个数
            else
                return tree[i].size - tree[tree[i].right].size + queryRankAchieve(tree[i].right);
        }
        return 0;
    }
    //查询某一值,该值在树中有n个数小于它
    // 查询某个值小于他的元素个数,其实相当于找到第rank大的值,然后他的根节点表示的值就是查询的答案
    // 所以该处的queriedrank相当于树的大小,我们需要去找一个左子树节点恰好为queriedRank的节点
    int queriedRank=0;
    int queryValueAchieve(int i)
    {
        // 如果当前节点的左子树大小 小于等于查询的大小
        if(queriedRank <= tree[tree[i].left].size)
            // 那么我们继续尝试在左子树中查询,因为我们这个判断条件无法得知是不是左子树恰好为查询的大小
            return queryValueAchieve(tree[i].left);
        // 如果当前节点左子树大小比查询的大小更大,但是加上当前节点的大小后就小于等于查询大小了,说明我们找的就是当前节点的值
        // 因为如果满足了该条件后仍然尝试在右子树中寻找,无论如何都是都是比查询大小更大的，所以只能是当前节点的值
        else if(queriedRank <= tree[tree[i].left].size+tree[i].cnt)
            return tree[i].value;
        // 两个条件都不满足,说明需要左子树+当前节点+部分右子树才能满足
        // 所以我们继续在右子树中寻找，但是需要将查询值删掉一部分，因为我们无法直接访问到根节点的大小，没办法实时维护根节点-当前节点+当前节点左子树
        else
        {
            // 删除已经查询到的排名
            queriedRank -= tree[tree[i].left].size + tree[i].cnt;
            return queryValueAchieve(tree[i].right);
        }
    }
    //查询某一值前驱
    int queriedNum = 0,ansQueryPre = INT_MIN;
    int queryPreAchieve(int i)
    {
        // 如果当前节点的值大于等于查询值
        // 说明答案在左子树中或者当前节点就是答案
        if(tree[i].value >= queriedNum)
        {
            // 如果左子树不存在,那么就不需要更新答案
            if(tree[i].left == 0)
                return ansQueryPre;
            // 如果左子树存在,那么就尝试在左子树中寻找答案
            else
                return queryPreAchieve(tree[i].left);
        }
        // 如果当前节点的值小于查询值
        // 说明答案在右子树中,我们应当在右子树中寻找答案
        else
        {
            // ？我为什么要写这一句，都能进入这个分支了肯定会小于查询值啊？
            // 总之既然当前值小于查询值，那么当前节点的值就是可能的一种答案
            // 这时既然能进入当前分支，意味着比当前节点小的值我们都考虑过了
            // 当前节点的值已经是查询到的值中的最优解,于是我们更新答案
            // 根据二叉搜索树的性质，当前节点的左子树一定都是小于当前节点的值，所以不需要考虑
            // 因为左子树都比当前节点小，而当前节点已经小于查询值，所以左子树不可能存在答案
            ansQueryPre = tree[i].value < queriedNum ? tree[i].value : ansQueryPre;
            // 如果右子树不存在，那么当前节点就是答案，无需再对答案进行更新，直接返回；
            if(tree[i].right == 0)
                return ansQueryPre;
            // 如果右子树存在，这就说明可能存在比当前节点的值更大的值在右子树中
            // 即当前值可能不是查询值的前驱，可能前驱存在于右子树中，于是我们继续查询右子树
            // 并尝试在右子树中寻找前驱
            else
                return queryPreAchieve(tree[i].right);
        }
    }
    //查询某一值后继
    // 查询后继与查询前驱原理相同，只是将查询前驱中的判断条件逆转，并且将前驱中的左子树和右子树互换
    int ansQueryNext = INT_MAX;
    int queryNextAchieve(int i)
    {
        if(tree[i].value <= queriedNum)
        {
            if(tree[i].right == 0)
                return ansQueryNext;
            else
                return queryNextAchieve(tree[i].right);
        }
        else
        {
            ansQueryNext=tree[i].value > queriedNum ? tree[i].value : ansQueryNext;
            if(tree[i].left==0)
                return ansQueryNext;
            else
                return queryNextAchieve(tree[i].left);
        }
    }
public:
    BinarySearchTree(int n): tree(std::vector<node>(n+10,{0, 0, 0, 0, 0})), count(1)
    {
        tree[1].value = INT_MIN;
        insert(INT_MAX);
    }
    BinarySearchTree() = delete;
    void insert(int insertedValue)
    {
        this->insertedValue = insertedValue;
        insertAchieve(1);

    }
    int queryRank(int queriedValue)
    {
        this->queriedValue = queriedValue;
        return queryRankAchieve(1);
    }
    int queryValue(int queriedRank)
    {
        if(queriedRank == 0)
            return INT_MAX;
        this->queriedRank = queriedRank;
        return queryValueAchieve(1);
    }
    int queryPre(int queriedNum)
    {
        this->queriedNum = queriedNum;
        this->ansQueryPre = INT_MIN;
        return queryPreAchieve(1);
    }
    int queryNext(int queriedNum)
    {
        this->queriedNum = queriedNum;
        this->ansQueryNext = INT_MAX;
        return queryNextAchieve(1);
    }
};

#endif