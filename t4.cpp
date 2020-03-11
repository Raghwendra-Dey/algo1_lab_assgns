/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A4.pdf
*/

#include <bits/stdc++.h>
#define vi pair<vector<int>, int>

using namespace std;

void greedy1(int n)
{
	int num_steps = 0;
	cout << "+++ Greedy 1" << endl;
	cout << "\tStart     : " << n << endl;

	while(n!=1)
	{
		num_steps++;

		if(n%2!=0)
		{
			n--;
			cout << "\tDecrement : " << n << endl; 
		}
		else
		{
			n/=2;
			cout << "\tDivide    : " << n << endl;
		}
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

int num_facs(int n)
{
	int res = 0;
	while(n%2==0)
	{
		n/=2;
		res++;
	}
	return res;
}

void greedy2(int n)
{
	int num_steps = 0;
	cout << "+++ Greedy 2" << endl;
	cout << "\tStart     : " << n << endl;
	while(n!=1)
	{
		num_steps++;

		if(n%2!=0)
		{
			int dec_facs = num_facs(n-1);
			int inc_facs = num_facs(n+1);
			if(dec_facs<inc_facs)
			{
				n++;
				cout << "\tIncrement : " << n << endl;
			}
			else
			{
				n--;
				cout << "\tDecrement : " << n << endl;
			}
		}
		else
		{
			n/=2;
			cout << "\tDivide    : " << n << endl;
		}
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

void greedy3(int n, int *a, int k)
{
	int num_steps = 0;
	cout << "+++ Greedy 3" << endl;
	cout << "\tStart     : " << n << endl;

	while(n!=1)
	{
		num_steps++;

		if(n%2==0)
		{
			n/=2;
			cout << "\tDivide    : " << n << endl;
		}
		else
		{
			int res, max_facs = -1;
			for(int i=0;i<k;i++)
			{
				if(n+a[i] < 0)
					continue;
				int facs = num_facs(n+a[i]);
				if(facs > max_facs)
				{
					res = n+a[i];
					max_facs = facs;
				}
				else if((facs == max_facs)&&(n+a[i] < res))
					res = n+a[i];
			}
			cout << "\tAdd " << res - n << "    : " << res << endl;
			n = res;
		}
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

void optimal(int n, int *a, int k, int MAX_STEPS)
{
	int num_steps = 0, cons_adds = 0;
	cout << "+++ Greedy 3" << endl;
	cout << "\tStart     : " << n << endl;

	while(n!=1)
	{
		num_steps++;

		if(n%2==0)
		{
			int res = n/2, max_facs = num_facs(n/2);
			for(int i=0;i<k;i++)
			{
				if(n+a[i] < 0)
					continue;
				int facs = num_facs(n+a[i]);
				if(facs > max_facs)
				{
					res = n+a[i];
					max_facs = facs;
				}
				else if((facs == max_facs)&&(n+a[i] < res))
					res = n+a[i];
			}
			if(cons_adds > MAX_STEPS)
			{
				res = n/2;
			}
			if(res*2 == n)
			{
				n/=2;
				cout << "\tDivide    : " << n << endl;
			}
			else
			{
				cons_adds++;
				cout << "\tAdd " << res-n << "     : " << res << endl;
				n = res;
			}
		}
		else
		{
			int res, max_facs = -1;
			for(int i=0;i<k;i++)
			{
				if(n+a[i] < 0)
					continue;
				int facs = num_facs(n+a[i]);
				if(facs > max_facs)
				{
					res = n+a[i];
					max_facs = facs;
				}
				else if((facs == max_facs)&&(n+a[i] < res))
					res = n+a[i];
			}
			
			cons_adds++;
			cout << "\tAdd " << res - n << "     : " << res << endl;
			n = res;
		}
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

int best(int n, int* a, int k	)

int main()
{
	int n, k;
	cout << "n = ";
	cin >> n;
	greedy1(n);
	greedy2(n);
	cout << "k = ";
	cin >> k;
	int * a = (int *)malloc(k*sizeof(int ));
	for(int i=0;i<k;i++)
	{
		cin >> a[i];
	}
	greedy3(n, a, k);
	vi res;
	res.second = 0;
	int MAX_STEPS = (int )(log(n)/log(2));
	optimal(n, a, k, MAX_STEPS);
}