#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define IOSclose ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(0)
#define all(a) a.begin(),a.end()
#define endl '\n'

class Tree
{
private:
    struct node
    {
        int left=0;
        int right=0;
        int value=0;
        int size=0;
        int cnt=0;
    };
    vector<node> tree;
    int count;
    //插入某一值
    int insertedValue=0;
    void insertAchieve(const int& i)
    {
        tree[i].size++;
        if(tree[i].value==insertedValue)
        {
            tree[i].cnt++;
            return;
        }
        else if(insertedValue<tree[i].value)
        {
            if(tree[i].left==0)
            {
                tree[i].left=++count;
                tree[count]={0,0,insertedValue,1,1};
                return;
            }
            else
            {
                insertAchieve(tree[i].left);
            }
        }
        else
        {
            if(tree[i].right==0)
            {
                tree[i].right=++count;
                tree[count]={0,0,insertedValue,1,1};
                return;
            }
            else
            {
                insertAchieve(tree[i].right);
            }
        }
        return;
    }
    //查询小于某一值的值个数
    int queriedValue=0;
    int queryRankAchieve(const int& i)
    {
        if(tree[i].value==queriedValue)
        {
            if(tree[i].left==0)
                return 0;
            else 
                return tree[tree[i].left].size;
        }
        else if(queriedValue<tree[i].value)
        {
            if(tree[i].left==0)
                return 0;
            else
                return queryRankAchieve(tree[i].left);
        }
        else
        {
            if(tree[i].right==0)
                return tree[i].size;
            else
                return tree[i].size-tree[tree[i].right].size+queryRankAchieve(tree[i].right);
        }
        return 0;
    }
    //查询某一值,该值在树中有n个数小于它
    int queriedRank=0;
    int queryValueAchieve(const int& i)
    {
        if(queriedRank<=tree[tree[i].left].size)
            return queryValueAchieve(tree[i].left);
        else if(queriedRank<=tree[tree[i].left].size+tree[i].cnt)
            return tree[i].value;
        else
        {
            queriedRank-=tree[tree[i].left].size+tree[i].cnt;
            return queryValueAchieve(tree[i].right);
        }
    }
    //查询某一值前驱
    int queriedNum=0,ansQueryPre=INT_MIN;
    int queryPreAchieve(const int& i)
    {
        if(tree[i].value>=queriedNum)
        {
            if(tree[i].left==0)
                return ansQueryPre;
            else
                return queryPreAchieve(tree[i].left);
        }
        else
        {
            ansQueryPre=tree[i].value<queriedNum?tree[i].value:ansQueryPre;
            if(tree[i].right==0)
                return ansQueryPre;
            else
                return queryPreAchieve(tree[i].right);
        }
    }
    //查询某一值后继
    int ansQueryNext=INT_MAX;
    int queryNextAchieve(const int& i)
    {
        if(tree[i].value<=queriedNum)
        {
            if(tree[i].right==0)
                return ansQueryNext;
            else
                return queryNextAchieve(tree[i].right);
        }
        else
        {
            ansQueryNext=tree[i].value>queriedNum?tree[i].value:ansQueryNext;
            if(tree[i].left==0)
                return ansQueryNext;
            else
                return queryNextAchieve(tree[i].left);
        }
    }
public:
    Tree(const int&n):tree(vector<node>(n+10,{0,0,0,0,0})),count(1)
    {
        tree[1].value=INT_MIN;
        insert(INT_MAX);
    }
    Tree() = delete;
    void insert(const int& insertedValue)
    {
        this->insertedValue=insertedValue;
        insertAchieve(1);

    }
    int queryRank(const int& queriedValue)
    {
        this->queriedValue=queriedValue;
        return queryRankAchieve(1);
    }
    int queryValue(const int& queriedRank)
    {
        if(queriedRank==0)
            return INT_MAX;
        this->queriedRank=queriedRank;
        return queryValueAchieve(1);
    }
    int queryPre(const int& queriedNum)
    {
        this->queriedNum=queriedNum;
        this->ansQueryPre=INT_MIN;
        return queryPreAchieve(1);
    }
    int queryNext(const int& queriedNum)
    {
        this->queriedNum=queriedNum;
        this->ansQueryNext=INT_MAX;
        return queryNextAchieve(1);
    }
};

int main()
{
    #ifndef PAUSE
    IOSclose;
    #endif
    
    int n=0;
    cin>>n;
    Tree t(n);
    int q=n;
    while(q--)
    {
        int op,x;
        cin>>op>>x;
        if(op==1)
            cout<<t.queryRank(x)+1<<endl;
        else if(op==2)
            cout<<t.queryValue(x)<<endl;
        else if(op==3)
        {
            int getReturnValue=t.queryPre(x);
            if(getReturnValue==INT_MIN)
                cout<<INT_MIN+1<<endl;
            else
                cout<<getReturnValue<<endl;
        }
        else if(op==4)
            cout<<t.queryNext(x)<<endl;
        else 
            t.insert(x);
    }
    
    #ifdef PAUSE
    cout<<endl;
    system("pause");
    #endif

    return 0;
}