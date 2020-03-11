/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A1.pdf
*/

#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

struct h_l
{
    double h,l;
};

double lorec(int n);

double hirec(int n)
{
	if(n==0)
	{
		return 1;
	}
	else
	{
		return (2*hirec(n-1) + lorec(n-1));
	}
}

double lorec(int n)
{
	if(n==0)
	{
		return 0;
	}
	else
	{
		return (hirec(n-1) + lorec(n-1));
	}
}

struct h_l hilorec(int n)
{
	struct h_l res;
	if(n==0)
	{
		res.h = 1;
		res.l = 0;
	}
	else
	{
		struct h_l prev_res;
		prev_res = hilorec(n-1);
		res.h = 2*prev_res.h + prev_res.l;
		res.l = prev_res.h + prev_res.l;
	}
	return res;
}

struct h_l hiloformula(int n)
{
	struct h_l res;
	double root_5 = sqrt(5);
	res.h = ((5 + root_5)/10)*pow(((3-root_5)/2), n+1) + ((5-root_5)/10)*pow(((3+root_5)/2), n+1);
	res.l = ((-5 - 3*root_5)/10)*pow(((3-root_5)/2), n+1) + ((-5+3*root_5)/10)*pow(((3+root_5)/2), n+1);
	return res;
}

int main()
{
    int n;
    cout << "n = ";
    cin >> n;
    cout << "+++ Method 0" << endl;
    cout << "	hi(" << n << ") = " << hirec(n) << ", lc(" << n << ") = " << lorec(n) << endl;
    cout << "+++ Method 1" << endl;
    struct h_l res = hilorec(n);
    cout << "	hi(" << n << ") = " << res.h << ", lc(" << n << ") = " << res.l << endl;
    cout << "+++ Method 2" << endl;
    res = hiloformula(n);
    cout << "	hi(" << n << ") = " << res.h << ", lc(" << n << ") = " << res.l << endl;
    return 0;
}
