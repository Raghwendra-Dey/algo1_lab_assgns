/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A5.pdf
*/

#include <bits/stdc++.h>
#define pii pair<int, int >
#define pdi pair<double, int >

using namespace std;

double comp_prof(double p, int s, int m, int t)
{
	double e;
	e = (1-pow(p, m))*s + pow(p, m)*t;
	return e;
}

void optimalbuy1(int n,int C,int *c,int *s,int *t,double *p)
{
	double T[n][C+1];
	int M[n][C+1];

	for(int j=0;j<C+1;j++)
	{
		if(j<c[0])
		{
			T[0][j] = -INFINITY;
		}
		else
		{
			T[0][j] = comp_prof(p[0], s[0], j/c[0], t[0]);
			M[0][j] = j/c[0];
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<C+1;j++)
		{
			if(j<c[i])
			{
				T[i][j] = -INFINITY;
			}
			else
			{
				double max_prof = -INFINITY;
				for(int m_i = 1;m_i <= (int)(j/c[i]);m_i++)
				{
					double e = comp_prof(p[i], s[i], m_i, t[i]);
					double expt_prof = T[i-1][j-m_i*c[i]] + e;
					if(expt_prof >= max_prof)
					{
						max_prof = expt_prof;
						M[i][j] = m_i;
					}
				}
				T[i][j] = max_prof;
			}
		}
	}

	int m_val[n];
	m_val[n-1] = M[n-1][C];
	int prev = m_val[n-1]*c[n-1];

	for(int i=n-2;i>=0;i--)
	{
		m_val[i] = M[i][C-prev];
		prev += m_val[i]*c[i];
	}

	int tot_buy_cost = 0;
	for(int i=0;i<n;i++)
	{
		cout << "\tMachine   " << i << ":   " << m_val[i] << " copies, cost =     " << m_val[i]*c[i] << endl;
		tot_buy_cost += m_val[i]*c[i];
	}
	cout << "--- Total buying cost = " << tot_buy_cost << endl;
	cout << "--- Expected total profit = " << T[n-1][C] << endl;
}

void optimalbuy2(int n,int C,int *c,int *s,int *t,int *r,double *p,double *q)
{
	double T[n][C+1];
	pii M[n][C+1];

	for(int j=0;j<C+1;j++)
	{
		if(j<c[0])
		{
			T[0][j] = -INFINITY;
		}
		else
		{
			double temp1, temp2;
			temp1 = comp_prof(p[0], s[0], j/c[0], t[0]);
			temp2 = comp_prof(q[0], s[0], j/c[0], t[0])- (int)(j/c[0])*r[0];
			if(temp1 < temp2)
			{
				T[0][j] = temp2;
				M[0][j] = make_pair(j/c[0], 1);
			}
			else
			{
				T[0][j] = temp1;
				M[0][j] = make_pair(j/c[0], 0);
			}
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<C+1;j++)
		{
			if(j<c[i])
			{
				T[i][j] = -INFINITY;
			}
			else
			{
				double max_prof = -INFINITY;
				for(int m_i = 1;m_i <= (int)(j/c[i]);m_i++)
				{
					pdi expt_prof;
					double e = comp_prof(p[i], s[i], m_i, t[i]);
					double expt_prof1 = T[i-1][j-m_i*c[i]] + e;
					e = comp_prof(q[i], s[i], m_i, t[i]);
					double expt_prof2 = T[i-1][j-m_i*c[i]] + e - m_i*r[i];
					if(expt_prof1 < expt_prof2)
					{
						expt_prof = make_pair(expt_prof2, 1);
					}
					else
					{
						expt_prof = make_pair(expt_prof1, 0);
					}
					if(expt_prof.first >= max_prof)
					{
						max_prof = expt_prof.first;
						M[i][j] = make_pair(m_i, expt_prof.second);
					}
				}
				T[i][j] = max_prof;
			}
		}
	}

	pii m_val[n];
	m_val[n-1] = M[n-1][C];
	int prev = m_val[n-1].first*c[n-1];

	for(int i=n-2;i>=0;i--)
	{
		m_val[i] = M[i][C-prev];
		prev += m_val[i].first*c[i];
	}

	int tot_buy_cost = 0;
	for(int i=0;i<n;i++)
	{
		cout << "\tMachine   " << i << ":   " << m_val[i].first << " copies, cost =     " << m_val[i].first*c[i];
		if(m_val[i].second)
			cout << " [Maintenance needed]" << endl;
		else
			cout << " [Maintenance not needed]" << endl;
		tot_buy_cost += m_val[i].first*c[i];
	}
	cout << "--- Total buying cost = " << tot_buy_cost << endl;
	cout << "--- Expected total profit = " << T[n-1][C] << endl;
}

int main()
{
	int n, C;
	cout << "n : ";
	cin >> n;
	cout << "Capital(C) : ";
	cin >> C;

	int * c = (int *)malloc(n*sizeof(int));
	int * s = (int *)malloc(n*sizeof(int));
	int * t = (int *)malloc(n*sizeof(int));
	int * r = (int *)malloc(n*sizeof(int));
	double * p = (double *)malloc(n*sizeof(double));
	double * q = (double *)malloc(n*sizeof(double));
	cout << "Costs (c) : ";
	for(int i=0;i<n;i++)
	{
		cin >> c[i];
	}
	cout << "Selling price (s) : ";
	for(int i=0;i<n;i++)
	{
		cin >> s[i];
	}
	cout << "Selling price (t) : ";
	for(int i=0;i<n;i++)
	{
		cin >> t[i];
	}
	cout << "Maintenance cost (r) : ";
	for(int i=0;i<n;i++)
	{
		cin >> r[i];
	}
	cout << "Probabilities (p) : ";
	for(int i=0;i<n;i++)
	{
		cin >> p[i];
	}
	cout << "Probabilities (q) : ";
	for(int i=0;i<n;i++)
	{
		cin >> q[i];
	}
	cout << "+++ Part 1: Best buying option" << endl;
	optimalbuy1(n,C,c,s,t,p);
	cout << "\n+++ Part 2: Best buying option" << endl;
	optimalbuy2(n,C,c,s,t,r,p,q);
}