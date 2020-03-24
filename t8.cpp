/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A8.pdf
status: working fine
comments: three bugs were there. first := while deleting the max of root if was not making sure that the substituted value is
the last one from the last node keys array. second := while heapifying i was just checking first that the qmin is less than the
lmax or not and if yes the swapping them, but this would be always true since atleast one key is out of order for sure.
third := atlast when only one node is left out i was not deleting the max value of the keys array of root node, instead only
deleting the last value of the keys array :/ (i know stupid mistake xd)
Result of all these bugs => one more uncompleted, bugged assignment :/
*/

#include <bits/stdc++.h>

using namespace std;

struct node
{
	int num_keys;
	int* keys;
};

struct heap
{
	int node_capacity;
	int num_keys;
	int num_nodes;
	struct node* arr_nodes;
};

struct heap* initheap(int p, int nmax)
{
	struct heap* h = (struct heap*)malloc(sizeof(struct heap));
	h->node_capacity = p;
	h->num_keys = nmax;
	h->num_nodes =  ceil((1.0*nmax)/p);
	h->arr_nodes = (struct node*)malloc(h->num_nodes*sizeof(struct node));
	for(int i=0;i<h->num_nodes;i++)
	{
		h->arr_nodes[i].num_keys = 0;
		h->arr_nodes[i].keys = (int*)malloc(p*sizeof(int));
	}
	return h;
}

bool check_prop(struct heap* h, int curr_node)
{
	if(curr_node == 0)
		return 1;
	int qmax=0, rmin=INT_MAX;
	for(int k=0;k<h->arr_nodes[curr_node].num_keys;k++)
	{
		if(h->arr_nodes[curr_node].keys[k] > qmax)
			qmax = h->arr_nodes[curr_node].keys[k];
	}
	for(int k=0;k<h->arr_nodes[(curr_node-1)/2].num_keys;k++)
	{
		if(h->arr_nodes[(curr_node-1)/2].keys[k] < rmin)
			rmin = h->arr_nodes[(curr_node-1)/2].keys[k];
	}
	return (rmin >= qmax);
}

struct heap* climb_up(struct heap* h, int curr_node)
{
	int tot_keys = (h->arr_nodes[(curr_node-1)/2].num_keys + h->arr_nodes[curr_node].num_keys);
	int* a = (int *)malloc(tot_keys*sizeof(int));
	int iter = 0;

	for(int i=0;i<h->arr_nodes[curr_node].num_keys;i++)
	{
		a[iter] = h->arr_nodes[curr_node].keys[i];
		iter++;
	}
	for(int i=0;i<h->arr_nodes[(curr_node-1)/2].num_keys;i++)
	{
		a[iter] = h->arr_nodes[(curr_node-1)/2].keys[i];
		iter++;
	}

	sort(a, a+tot_keys);

	iter = 0;
	for(int i=0;i<h->arr_nodes[curr_node].num_keys;i++)
	{
		h->arr_nodes[curr_node].keys[i] = a[iter];
		iter++;
	}
	for(int i=0;i<h->arr_nodes[(curr_node-1)/2].num_keys;i++)
	{
		h->arr_nodes[(curr_node-1)/2].keys[i] = a[iter];
		iter++;
	}
	return h;
}

// child of 'i' == '2i+1', and '2i+2'
struct heap* insert(struct heap* h, int x)
{
	for(int i=0;i<h->num_nodes;i++)
	{
		if(h->arr_nodes[i].num_keys<h->node_capacity)
		{
			h->arr_nodes[i].keys[h->arr_nodes[i].num_keys] = x;
			h->arr_nodes[i].num_keys++;
			int j = i;
			while(j>0)
			{
				if(check_prop(h, j))
					break;
				else
					h = climb_up(h, j);
				j = (j-1)/2;
			}
			break;
		}
	}
	return h;
}

int findmax(struct heap* h)
{
	int ans = 0;
	for(int i=0;i<h->arr_nodes[0].num_keys;i++)
		if(ans < h->arr_nodes[0].keys[i])
			ans = h->arr_nodes[0].keys[i];
	return ans;
}

struct heap* heapify(struct heap* h, int curr_root)
{
	if(curr_root > h->num_nodes-1)
		return h;
	if(h->arr_nodes[curr_root].num_keys == 0)
		return h;

	int qmin = INT_MAX, lmax = 0, rmax = 0, qidx,lidx,ridx;

	for(int i=0;i< h->arr_nodes[curr_root].num_keys;i++)
		if(qmin >= h->arr_nodes[curr_root].keys[i])
		{
			qmin = h->arr_nodes[curr_root].keys[i];
			qidx = i;
		}

	if((2*curr_root+1)<h->num_nodes)
		for(int i=0;i< h->arr_nodes[2*curr_root+1].num_keys;i++)
			if(lmax <= h->arr_nodes[2*curr_root+1].keys[i])
			{
				lmax = h->arr_nodes[2*curr_root+1].keys[i];
				lidx = i;
			}

	if((2*curr_root+2)<h->num_nodes)
		for(int i=0;i< h->arr_nodes[2*curr_root+2].num_keys;i++)
			if(rmax <= h->arr_nodes[2*curr_root+2].keys[i])
			{
				rmax = h->arr_nodes[2*curr_root+2].keys[i];
				ridx = i;
			}

	if((qmin >= rmax)&&(qmin >= lmax))
		return h;
	else if(lmax > rmax)
	{
		int temp = h->arr_nodes[curr_root].keys[qidx];
		h->arr_nodes[curr_root].keys[qidx] = h->arr_nodes[2*curr_root+1].keys[lidx];
		h->arr_nodes[2*curr_root+1].keys[lidx] = temp;
		return heapify(h, 2*curr_root+1);
	}
	else
	{
		int temp = h->arr_nodes[curr_root].keys[qidx];
		h->arr_nodes[curr_root].keys[qidx] = h->arr_nodes[2*curr_root+2].keys[ridx];
		h->arr_nodes[2*curr_root+2].keys[ridx] = temp;
		return heapify(h, 2*curr_root+2);
	}
}

void prnheap(struct heap* h)
{
	cout << "+++ " << h->num_keys << " insertions made" << endl;
	for(int i=0;i<h->num_nodes;i++)
	{
		if(h->arr_nodes[i].num_keys == 0)
			break;
		cout << "\t[ ";
		for(int j=0;j<h->arr_nodes[i].num_keys;j++)
			cout << h->arr_nodes[i].keys[j] << " ";
		cout << " ]" << endl;
	}
}

struct heap* delmax(struct heap* h)
{
	int qmax = 0, qidx;
	for(int i=0;i<h->arr_nodes[0].num_keys;i++)
	{
		if(qmax < h->arr_nodes[0].keys[i])
		{
			qmax = h->arr_nodes[0].keys[i];
			qidx = i;
		}
	}
	int last_idx = 0;
	for(int i=0;i<h->num_nodes;i++)
	{
		if((h->arr_nodes[i].num_keys <= h->node_capacity)&&(h->arr_nodes[i].num_keys>0))
			last_idx = i;
	}
	if(last_idx == 0)
	{
		h->arr_nodes[0].keys[qidx] = h->arr_nodes[0].keys[h->arr_nodes[0].num_keys-1];
		h->arr_nodes[0].num_keys--;
		return h;
	}
	else
	{
		h->arr_nodes[0].keys[qidx] = h->arr_nodes[last_idx].keys[h->arr_nodes[last_idx].num_keys-1];
		h->arr_nodes[last_idx].num_keys--;
		return heapify(h, 0);
	}
}


int main()
{
	int p, nmax;
	cin >> p;
	cin >> nmax;
	int* a = (int *)malloc(nmax*sizeof(int));
	for(int i=0;i<nmax;i++)
		cin >> a[i];
	struct heap* h = initheap(p, nmax);
	for(int i=0;i<nmax;i++)
		h = insert(h, a[i]);
	prnheap(h);

	for(int i=nmax-1;i>=0;i--)
	{
		a[i] = findmax(h);
		delmax(h);
	}
	cout << "+++ " << nmax << " deletions made" << endl;
	cout << "+++ Input array sorted" << endl;
	for(int i=0;i<nmax;i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
}