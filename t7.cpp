/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A7.pdf
status: working fine
*/

#include <bits/stdc++.h>

using namespace std;

long long combs(long long n, long long r)
{
	long long p = 1, k = 1; 
  
	// C(n, r) == C(n, n-r), 
	// choosing the smaller value 
	if (n - r < r) 
		r = n - r; 
  
	if (r != 0) { 
		while (r) { 
			p *= n; 
			k *= r; 
  
			// gcd of p, k 
			long long m = __gcd(p, k); 
  
			// dividing by gcd, to simplify product 
			// division by their gcd saves from the overflow 
			p /= m; 
			k /= m; 
  
			n--; 
			r--; 
		} 
  
		// k should be simplified to 1 
		// as C(n, r) is a natural number 
		// (denominator should be 1 ) . 
	} 
  
	else
		p = 1; 
  
	// if our approach is correct p = ans and k =1 
	return p;
}

long long countseq(vector<long long> a, long long n)
{
	if(n<3)
		return 1;
	vector<long long> l;
	vector<long long> r;
	for(long long i=1;i<n;i++)
	{
		if(a[i]<a[0])
			l.push_back(a[i]);
		else
			r.push_back(a[i]);
	}

	return (countseq(l, l.size())*countseq(r, r.size())*combs(n-1, l.size()));
}

long long count_ones(std::vector<bool> v)
{
	long long ans = 0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i])
			ans++;
	}
	return ans;
}

std::vector<bool> find_bin_repr(long long n, long long length)
{
	if(n<2)
	{
		std::vector<bool> ans1;
		for(int i=0;i<length-1;i++)
		{
			ans1.push_back(0);
		}
		ans1.push_back(n);
		return ans1;
	}
	vector<bool> ans = find_bin_repr(n/2, length);
	ans.push_back(n%2);
	ans.erase(ans.begin());
	return ans;
}

vector<vector<long long> > findallseq(vector<long long> a,long long n)
{
	vector<vector<long long> > res;
	if(n<3)
	{
		res.push_back(a);
		return res;
	}

	vector<long long> l;
	vector<long long> r;
	for(long long i=1;i<n;i++)
	{
		if(a[i]<a[0])
			l.push_back(a[i]);
		else
			r.push_back(a[i]);
	}

	std::vector<std::vector<long long> > bl = findallseq(l, l.size());
	std::vector<std::vector<long long> > br = findallseq(r, r.size());

	for(long long i=0;i<(long long )pow(2, n-1);i++)
	{
		std::vector<bool> bin_repr = find_bin_repr(i, n-1);

		if(count_ones(bin_repr) == r.size())
		{
			for(long long l_seq = 0;l_seq<bl.size();l_seq++)
			{
				for(long long r_seq = 0;r_seq<br.size();r_seq++)
				{
					std::vector<long long> ans;
					ans.push_back(a[0]);

					long long iter_l = 0, iter_r = 0;

					for(long long bit=0;bit<bin_repr.size();bit++)
					{
						if(bin_repr[bit])
						{
							ans.push_back(br[r_seq][iter_r]);
							iter_r++;
						}
						else
						{
							ans.push_back(bl[l_seq][iter_l]);
							iter_l++;
						}
					}
					res.push_back(ans);
				}
			}
		}
	}

	return res;
}

void printallseqs(std::vector<std::vector<long long> > res)
{
	for(long long i=0;i<res.size();i++)
	{
		cout << "\tSequence " << i+1 << "\t: ";

		for(long long j=0;j<res[i].size();j++)
		{
			cout << res[i][j] << ' ';
		}
		cout << endl;
	}
}

struct node
{
	long long key;
	struct node* l;
	struct node* r;
};

void BSTins(struct node* T, long long x)
{
	if(T->key > x)
	{
		if(T->l == NULL)
		{
			struct node* ptr = (struct node*)malloc(sizeof(struct node));
			ptr->l = NULL;
			ptr->r = NULL;
			T->l = ptr;
			ptr->key = x;
			return;
		}
		else
		{
			BSTins(T->l, x);
			return;
		}
	}
	else
	{
		if(T->r == NULL)
		{
			struct node* ptr = (struct node*)malloc(sizeof(struct node));
			T->r = ptr;
			ptr->l = NULL;
			ptr->r = NULL;
			ptr->key = x;
			return;
		}
		else
		{
			BSTins(T->r, x);
			return;
		}
	}
}

struct node* BSTcons(std::vector<long long > a, long long n)
{
	struct node* T = (struct node*)malloc(sizeof(struct node));
	T->l = NULL;
	T->r = NULL;
	T->key = a[0];
	for(int i=1;i<n;i++)
	{
		BSTins(T, a[i]);
	}
	return T;
}

void preorder_prn(struct node* T)
{
	if(T == NULL)
		return;
	cout << T->key << ' ';
	preorder_prn(T->l);
	preorder_prn(T->r);
}

void inorder_prn(struct node* T)
{
	if(T == NULL)
		return;
	inorder_prn(T->l);
	cout << T->key << ' ';
	inorder_prn(T->r);
}

void BSTprn(struct node* T)
{
	cout << "+++ BST constructed from input array";
	cout << "\t\nPreorder: ";
	preorder_prn(T);
	cout << "\t\nInorder: ";
	inorder_prn(T);
	cout << endl;
}

bool BSTsame(struct node* T1, struct node* T2)
{
	if((T1 == NULL)&&(T2 == NULL))
		return 1;
	else if((T1 == NULL)||(T2 == NULL))
		return 0;
	if(T1->key == T2->key)
	{
		if((T1->l, T2->l)&&(T1->r, T2->r))
			return 1;
		else return 0;
	}
	else return 0;
}

void BSTfree(struct node* T)
{
	if(T == NULL)
		return;
	BSTfree(T->l);
	BSTfree(T->r);
	free(T);
}

void checkall(struct node* T, std::vector<std::vector<long long> > v)
{
	long long ans = 0;
	for(int i=0;i<v.size();i++)
	{
		struct node* T2 = BSTcons(v[i], v[i].size());
		if(BSTsame(T, T2) == 0)
			ans++;
		BSTfree(T2);
	}
	if(ans == 0)
		cout << "\tAll trees match" << endl;
	else
		cout << "\tNumber of trees not matched: " << ans << endl;
}

int main()
{
	long long n;
	cout << "n = ";
	cin >> n;
	vector<long long> a(n);
	for(long long i=0;i<n;i++)
	{
		cin >> a[i];
	}

	cout << "+++ Sequence count\n\t";
	cout << "Total number of sequences = " << countseq(a, n) << endl;

	cout << "+++ All sequences\n";
	std::vector<std::vector<long long> > res = findallseq(a, n);
	printallseqs(res);

	struct node* T = BSTcons(a, n);
	BSTprn(T);

	cout << "+++ Checking all sequences" << endl;
	checkall(T, res);

}