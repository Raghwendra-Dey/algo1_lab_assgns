/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A6.pdf
*/

#include <bits/stdc++.h>

using namespace std;

struct node
{
	int key;
	struct node* l_child;
	struct node* r_child;
};

struct node* readtree(int n)
{
	if(n==0)
		return NULL;
	struct node* T = (struct node*)malloc(sizeof(struct node));
	int key1, num_l, num_r;
	cin >> key1 >> num_l >> num_r;
	T->key = key1;
	T->l_child = readtree(num_l);
	T->r_child = readtree(num_r);
	return T;
}

void inorder_prn(struct node* T)
{
	if(T == NULL)
		return;
	inorder_prn(T->l_child);
	cout << T->key << ' ';
	inorder_prn(T->r_child);
}

void preorder_prn(struct node* T)
{
	if(T == NULL)
		return;
	cout << T->key << ' ';
	preorder_prn(T->l_child);
	preorder_prn(T->r_child);
}

void prntree(struct node* T)
{
	cout << "--- Preorder listing" << endl;
	preorder_prn(T);
	cout << endl;
	cout << "--- inorder listing" << endl;
	inorder_prn(T);
	cout << endl;
}

struct node* swapchild(struct node* T)
{
	struct node* temp = T->l_child;
	T->l_child = T->r_child;
	T->r_child = temp;
	return T;
}

struct node* lrotate(struct node* T)
{
	struct node* root = T->r_child;
	T->r_child = root->l_child;
	root->l_child = T;
	return root;
}

struct node* rrotate(struct node* T)
{
	struct node* root = T->l_child;
	T->l_child = root->r_child;
	root->r_child = T;
	return root;
}

struct node* makeskew(struct node* T)
{
	int i=0;
	struct node* root = T;
	while(T->r_child != NULL)
	{
		while(T->r_child->l_child != NULL)
		{
			T->r_child = rrotate(T->r_child);
		}
		if(i == 0)
			root = T->r_child;
		T = T->r_child;
		i++;
	}
	return root;
}

struct node* swap(struct node* parent_k)
{
	parent_k->r_child = swapchild(parent_k->r_child);
	parent_k->r_child = rrotate(parent_k->r_child);
	parent_k->r_child->r_child = swapchild(parent_k->r_child->r_child);
	return parent_k;
}

void bsort(struct node* T, int n)
{
	for(int i=0;i<n;i++)
	{
		struct node* parent_k = T;
		struct node* k = T->r_child;
		struct node* l = k->r_child;
		while(l != NULL)
		{
			if(k->key > l->key)
				parent_k = swap(parent_k);
			parent_k = k;
			k = l;
			l = k->r_child;
		}
	}
}

// flag: 0 ==> left rotations(right skewed) , 1 ==> right rotations(left skewed)
struct node* rebalance(struct node* T, int n, bool flag)
{
	if(n == 0)
		return NULL;
	if(n == 1)
		return (flag?T->l_child:T->r_child);
	int root_idx;
	struct node* root = T;
	if(flag)
	{
		root_idx = ceil(n/2);
		for(int i=0;i<root_idx;i++)
			root = root->l_child;
		while(T->l_child != root)
			T->l_child = rrotate(T->l_child);
	}
	else
	{
		root_idx = (n/2)+1;
		for(int i=0;i<root_idx;i++)
			root = root->r_child;
		while(T->r_child != root)
			T->r_child = lrotate(T->r_child);
	}

	root->l_child = rebalance(root, n/2, 1);
	root->r_child = rebalance(root, n - (n/2) - 1, 0);

	return root;
}

int main()
{
	int n;
	cin >> n;
	struct node* T = readtree(n);
	struct node* T_dummy = (struct node*)malloc(sizeof(struct node));
	T_dummy->r_child = T;
	cout << "+++ Initial tree" << endl;
	prntree(T_dummy->r_child);
	T_dummy->r_child = makeskew(T_dummy);
	cout << "+++ Tree made skew" << endl;
	prntree(T_dummy->r_child);
	bsort(T_dummy, n);
	cout << "+++ Tree after sorting" << endl;
	prntree(T_dummy->r_child);
	T_dummy->r_child = rebalance(T_dummy, n, 0);
	cout << "+++ Tree after rebalancing" << endl;
	prntree(T_dummy->r_child);
}

/*
8
205 4 3
192 1 2
215 0 0
216 0 1
201 0 0
194 1 1
191 0 0
213 0 0
*/