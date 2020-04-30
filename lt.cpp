/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/LT.pdf
status: hag die dada ;-;
*/

#include <bits/stdc++.h>
#define INF 1000000000

using namespace std;

int max(int a, int b)
{
	return ((a>b)?a:b);
}

int min(int a, int b)
{
	return ((a<b)?a:b);
}

bool ischessboard(int f[][50], int st_i, int st_j, int k, int l)
{
	int st_col=!f[st_i][st_j];
	int curr_col;
	for(int i=0;i<k;i++)
	{
		if(f[st_i+i][st_j]==st_col) return 0;
		st_col=(!st_col);
		curr_col=st_col;
		for(int j=1;j<l;j++)
		{
			if(f[st_i+i][st_j+j]==curr_col) return 0;
			curr_col=(!curr_col);
		}
	}
	return 1;
}

void prn_sol(int f[][50], int m, int n, int st_i, int st_j, int k, int l)
{
	for(int i=0;i<m;i++)
	{
		cout << "\t";
		for(int j=0;j<n;j++)
		{
			if((i>=st_i)&&(i<st_i+k)&&(j>=st_j)&&(j<st_j+l))
				cout << ((f[i][j])?"W ":"B ");
			else cout << ". ";
		}
		cout << endl;
	}
	cout << "Area = " << k*l << endl;
}

struct rec
{
	int st_i, st_j, k, l;
};

void essquare(int f[][50], int m, int n)
{
	struct rec mx;
	mx.st_i=0;
	mx.st_j=0;
	mx.k=1;
	mx.l=1;

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			int l_max=(((m-i)>(n-j))?(n-j):(m-i));
			for(int l=l_max;l>0;l--)
			{
				if(ischessboard(f, i, j, l, l))
				{
					if(l*l>=mx.k*mx.l)
					{
						mx.st_i=i;
						mx.st_j=j;
						mx.k=l;
						mx.l=l;
					}
					break;
				}
			}
		}
	}
	cout << "+++ Exhaustive search: Square" << endl;
	prn_sol(f, m, n, mx.st_i, mx.st_j, mx.k, mx.l);
}

void esrectangle(int f[][50], int m, int n)
{
	struct rec mx;
	mx.st_i=m-1;
	mx.st_j=n-1;
	mx.k=1;
	mx.l=1;

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			int k_max=(m-i);
			int l_max=(n-j);
			for(int k=k_max;k>0;k--)
			{
				for(int l=l_max;l>0;l--)
					if(ischessboard(f, i, j, k, l))
					{
						if(k*l>=mx.k*mx.l)
						{
							mx.st_i=i;
							mx.st_j=j;
							mx.k=k;
							mx.l=l;
						}
						break;
					}
			}
		}
	}
	cout << "+++ Exhaustive search: Rectangle" << endl;
	prn_sol(f, m, n, mx.st_i, mx.st_j, mx.k, mx.l);
}

void dpsquare(int f[][50], int m, int n)
{
	int t[50][50];
	t[m-1][n-1]=1;

	for(int i=m-1;i>=0;i--)
	{
		for(int j=n-1;j>=0;j--)
		{
			if((i==m-1)&&(j==n-1)) continue;
			if(((i+1<m)&&(f[i][j]==f[i+1][j]))||((j+1<n)&&(f[i][j]==f[i][j+1])))
			{
				t[i][j]=1;
				continue;
			}
			int l1;
			if(i+1<m) l1=t[i+1][j];
			else l1=0;
			int l2;
			if(j+1<n) l2=t[i][j+1];
			else l2=0;
			if(l1>l2) t[i][j]=l2+1;
			else if(l1<l2) t[i][j]=l1+1;
			else
			{
				if(f[i][j]==f[i+l1][j+l1]) t[i][j]=l1+1;
				else t[i][j]=l1;
			}
		}
	}
	struct rec mx;
	mx.st_i=m-1;
	mx.st_j=n-1;
	mx.k=1;
	mx.l=1;

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(mx.k*mx.l<=t[i][j]*t[i][j])
			{
				mx.st_i=i;
				mx.st_j=j;
				mx.k=t[i][j];
				mx.l=t[i][j];
			}
		}
	}
	cout << "+++ Dynamic Programming: Square" << endl;
	prn_sol(f, m, n, mx.st_i, mx.st_j, mx.k, mx.l);
}

struct rect
{
	int mx_ar, mx_rw, mx_cl, k, l;
};

void dprectangle(int f[][50], int m, int n)
{
	struct rect t[50][50];
	t[m-1][n-1].mx_ar=1;
	t[m-1][n-1].mx_rw=1;
	t[m-1][n-1].mx_cl=1;
	t[m-1][n-1].k=1;
	t[m-1][n-1].l=1;

	for(int i=m-1;i>=0;i--)
	{
		for(int j=n-1;j>=0;j--)
		{
			// for (i, j+1)
			int min_col=INF, min_row=INF;
			bool flag_down=1, flag_side=1;
			t[i][j].mx_ar=1;
			if((j==n-1)||(f[i][j]==f[i][j+1]))
			{
				min_col=1;
				t[i][j].mx_cl=1;
				flag_side=0;
			}
			else
			{
				min_col=t[i][j+1].mx_cl+1;
				t[i][j].mx_ar=t[i][j+1].mx_cl+1;
			}
			if((i==m-1)||(f[i][j]==f[i+1][j]))
			{
				min_row=1;
				t[i][j].mx_rw=1;
				flag_down=0;
			}
			else
			{
				min_row=t[i+1][j].mx_rw+1;
				t[i][j].mx_ar=max(t[i+1][j].mx_rw+1, t[i][j].mx_ar);
			}
			if(flag_side)
			{
				t[i][j].mx_cl=t[i][j+1].mx_cl+1;
				for(int l=1;l<t[i][j+1].mx_cl+1;l++)
				{
					min_row=min(min_row, t[i][j+l].mx_rw);
					if(t[i][j].mx_ar<(l+1)*min_row)
					{
						t[i][j].mx_ar=(l+1)*min_row;
						t[i][j].k=min_row;
						t[i][j].l=(l+1);
					}
				}
			}
			if(flag_down)
			{
				t[i][j].mx_rw=t[i+1][j].mx_rw+1;
				for(int k=1;k<t[i+1][j].mx_rw+1;k++)
				{
					min_col=min(min_col, t[i+k][j].mx_cl);
					if(t[i][j].mx_ar<(k+1)*min_col)
					{
						t[i][j].mx_ar=(k+1)*min_col;
						t[i][j].l=min_col;
						t[i][j].k=(k+1);
					}
				}
			}
		}
	}

	struct rec mx;
	mx.st_i=m-1;
	mx.st_j=n-1;
	mx.k=1;
	mx.l=1;
	int mx_ar=1;

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(t[i][j].mx_ar>mx_ar)
			{
				mx.st_i=i;
				mx.st_j=j;
				mx.k=t[i][j].k;
				mx.l=t[i][j].l;
				mx_ar=t[i][j].mx_ar;
			}
		}
	}
	cout << "+++ Dynamic Programming: Rectangle" << endl;
	prn_sol(f, m, n, mx.st_i, mx.st_j, mx.k, mx.l);
}

int main()
{
	int m, n;
	cin >> m >> n;
	int f[50][50];
	for(int i=0; i<m; i++)
	{
		for(int j=0;j<n;j++)
			cin >> f[i][j];
	}
	essquare(f, m, n);
	esrectangle(f, m, n);
	dpsquare(f, m, n);
	dprectangle(f, m, n);
}