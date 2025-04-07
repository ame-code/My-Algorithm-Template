#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define all(a) a.begin(),a.end()

class SegumentTree
{
private:
	struct node
	{
		int l=0;
		int r=0;
		int num=0;
		int lazy_flag=0;
	};
	vector<node> tree;
	vector<int> input;

	//单点查询
	int point_query_i;
	inline int point_query_achieve()
	{
		range_query_l=range_query_r=point_query_i;
		range_query_achieve(1);
	}

	//单点修改（增加)
	int point_update_i,point_update_add_var;
	inline void point_update_achieve(int i)
	{
		if(tree[i].l==tree[i].r)
		{
			tree[i].num+=point_update_add_var;
			return;
		}
		if(point_update_i<=tree[i].r)
			point_update_achieve(2*i);
		else
			point_update_achieve(2*i+1);
		tree[i].num=tree[2*i].num+tree[2*i+1].num;
	}

	//区间查询
	int range_query_l,range_query_r;
	inline int range_query_achieve(int i)
	{
		if(range_query_l<=tree[i].l&&tree[i].r<=range_query_r)
			return tree[i].num;
		if(tree[i].r<range_query_l||tree[i].l>range_query_r)
			return 0;
		int sum=0;
		if(range_query_l<=tree[2*i].r)
			sum+=range_query_achieve(2*i);
		if(range_query_r>=tree[2*i+1].l)
			sum+=range_query_achieve(2*i+1);
		return sum;
	}
	
	//区间修改
	inline void range_update_achieve(int i,int l,int r,int k)
	{
		if(tree[i].r<=r&&tree[i].l>=l)
		{
			tree[i].num+=k*(tree[i].r-tree[i].l+1);
			tree[i].lazy_flag+=k;
			return;
		}
		push_down(i);
		if(tree[i*2].r>=l)
        	range_update_achieve(i*2,l,r,k);
		if(tree[i*2+1].l<=r)
			range_update_achieve(i*2+1,l,r,k);
		tree[i].num=tree[i*2].num+tree[i*2+1].num;
	}
	void push_down(int i)
	{
		if(tree[i].lazy_flag)
		{
			tree[2*i].lazy_flag+=tree[i].lazy_flag;
			tree[2*i+1].lazy_flag+=tree[i].lazy_flag;
			tree[2*i].num+=tree[i].lazy_flag*(tree[2*i].r-tree[i].l+1);
			tree[2*i+1].num+=tree[i].lazy_flag*(tree[2*i+1].r-tree[2*i+1].l+1);
			tree[i].lazy_flag=0;
		}
	}
public:
	SegumentTree():tree(vector<node>(0)),input(vector<int>(0)){};
	SegumentTree(int n):tree(vector<node>(4*n+5)),input(vector<int>(n+1,0)){};
	inline void input(const int& i)
	{
		cin>>this->input[i];
	}
	inline void build(int i,int l,int r)
	{
		tree[i].l=l,tree[i].r=r;
		if(l==r)
		{
			tree[i].num=input[l];
			return;
		}
		int mid=l+(r-l>>1);
		build(2*i,l,mid);
		build(2*i+1,mid+1,r);
		tree[i].num=tree[2*i].num+tree[2*i+1].num;
	}
	inline int point_query(int i)
	{
		point_query_i=i;
		return point_query_achieve();
	}
	inline int interval_query(int l,int r)
	{
		this->range_query_l=l,this->range_query_r=r;
		return range_query_achieve(1);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	
	
	
	return 0;
}