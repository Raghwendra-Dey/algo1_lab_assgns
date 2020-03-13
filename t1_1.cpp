/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A1.pdf
status: method 3 not implemented yet
*/

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string>

using namespace std;

string met0(int *seq, int n)
{

	int i,j,k;
	for(int a = 1;a<=n;a++)
		for(int b=a+1;b<=n;b++)
			for(int c=b+1;c<=n;c++)
			{
				for(int it=0;it<n;it++)
				{
					if(seq[it] == a)
						j = it;
					else if(seq[it] == b)
						k = it;
					else if(seq[it] == c)
						i = it; 
				}
				if((i<j)&&(j<k))
					return "Unalgolicious";
			}
	
	return "Algolicious";
}

string met1(int *seq, int n)
{
	int a,b,c;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			for(int k=j+1;k<n;k++)
			{
				a = seq[j];
				b = seq[k];
				c = seq[i];
				if((a<b)&&(b<c))
					return "Unalgolicious";
			}
	return "Algolicious";
}

string met2(int *seq, int n)
{
	int c, prev_min;
	for(int i=0;i<n;i++)
	{
		c = seq[i];
		prev_min = c;
		for(int j=i+1;j<n;j++)
		{
			if(seq[j] < c)
			{
				if(prev_min > seq[j])
					prev_min = seq[j];
				else
					return "Unalgolicious";
			}
		}
	}
	return "Algolicious";
}

string met3(int *seq, int n)
{
	
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	int *seq = (int *)malloc(n*sizeof(int));
	cout << "+++ Sequence: ";
	for(int i=0;i<n;i++)
	{
		cin >> seq[i];
	}
	cout << "	Method 0: " << met0(seq, n) << endl;
	cout << "	Method 1: " << met1(seq, n) << endl;
	cout << "	Method 2: " << met2(seq, n) << endl;
/*	cout << "	Method 3: " << met3(seq, n) << endl;*/
	

}
