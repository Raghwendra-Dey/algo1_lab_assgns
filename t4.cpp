/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A4.pdf
status: working fine
comments: good question, one good observation about dynamic programming i.e. we can't let the program search indefinitely
we put a check on the number of continous additions, which if breached returns infinity, but this creates problem with the cases
where some check node of the way to minimum is blocked due to breaching of MAX_STEPS. so i put a check that only search if 
dp[n].numsteps is either unexplored or cut down due to breaching. this cleared all the samples :D
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
			if(n == 3)
			{
				num_steps++;
				n--;
				cout << "\tDecrement : " << n << endl;
				n--;
				cout << "\tDecrement : " << n << endl;
				break;
			}
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
	std::vector<int> visited;

	while(n!=1)
	{
		visited.push_back(n);
		num_steps++;
		bool flag = 0;

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
				if(n+a[i] <= 0)
					continue;
				for(int j=0;j<visited.size();j++)
					if(visited[j] == n+a[i])
					{
						flag = 1;
						break;
					}
				if(flag)
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

struct move
{
	int num_steps;
	int process;
};


struct move best(int n, int* a, int k, int cont_adds, int MAX_STEPS, struct move dp[])
{
	struct move res;
	if(cont_adds > 2*MAX_STEPS)
	{
		res.num_steps = 1000000000;
		return res;
	}
	if((dp[n].num_steps != -1)&&(dp[n].num_steps!=1000000000))
	{
		return dp[n];
	}
	if(n == 1)
	{
		res.num_steps = 0;
		dp[1] = res;
		return res;
	}
	if(n == 2)
	{
		res.num_steps = 1;
		res.process = k;
		dp[2] = res;
		return res;
	}
	res.num_steps = 0;

	if(n%2 == 0)
	{
		res.num_steps = best(n/2, a, k, cont_adds, MAX_STEPS, dp).num_steps+1;
		res.process = k;
		for(int i=0;i<k;i++)
		{
			if(n+a[i] <= 0)
				continue;
			struct move inst_res = best(n+a[i], a, k, cont_adds+1, MAX_STEPS, dp);
			if(inst_res.num_steps + 1 < res.num_steps)
			{
				res = inst_res;
				res.num_steps++;
				res.process = i;
			}
		}
	}
	else
	{
		res.num_steps = 1000000000;
		for(int i=0;i<k;i++)
		{
			if(n+a[i] <= 0)
				continue;
			struct move inst_res = best(n+a[i], a, k, cont_adds+1, MAX_STEPS, dp);
			if(inst_res.num_steps + 1 < res.num_steps)
			{
				res = inst_res;
				res.num_steps++;
				res.process = i;
			}
		}
	}
	dp[n] = res;
	return res;
}

void optimal(int n, int *a, int k, int MAX_STEPS)
{
	int num_steps = 0, cons_adds = 0;
	cout << "+++ Optimal" << endl;
	cout << "\tStart     : " << n << endl;


	struct move* dp = (struct move*)malloc((n + 20*MAX_STEPS)*sizeof(struct move));
	for(int i=0;i< n + 20*MAX_STEPS;i++)
		dp[i].num_steps = -1;	
	struct move res = best(n, a, k, 0, MAX_STEPS, dp);
	// for(int i=0;i<n+20*MAX_STEPS;i++)
	// 	cout << "i : " << i << " 	dp[n] : " << dp[i].num_steps << endl;
	while(n>1)
	{
		if(dp[n].process == k)
		{
			n/=2;
			cout << "\tDivide    : " << n << endl;
		}
		else
		{
			cout << "\tAdd " << a[dp[n].process] << "    : " << n + a[dp[n].process] << endl;
			n = n + a[dp[n].process];
		}
	}
	cout << "--- Number of steps = " << res.num_steps << endl;
}

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
	int MAX_STEPS = ceil(log(n)/log(2));
	cout << MAX_STEPS << endl;
	optimal(n, a, k, MAX_STEPS);
}