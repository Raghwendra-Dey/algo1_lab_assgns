/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A2.pdf
status: giving wrong outputs
*/

#include <bits/stdc++.h>
#define vsci vector<pair<string, pair<char, int> > >

using namespace std;

vsci findallexpr(int n)
{
	vsci res;
	if(n==1)
	{
		res.push_back(make_pair("1", make_pair('M', 1)));
		return res;
	}
	if(n==2)
	{
		res.push_back(make_pair("1+1", make_pair('A', 2)));
		return res;
	}

	int i=1;
	int j = n-1;

	vsci l_i = findallexpr(i);
	vsci l_j = findallexpr(j);
	for(vsci::iterator it1 = l_i.begin();it1< l_i.end();it1++)
	{
		for(vsci::iterator it2=l_j.begin();it2<l_j.end();it2++)
		{
			res.push_back(make_pair(it1->first+"+"+it2->first,make_pair('A',it1->second.second+it2->second.second)));
		}
	}

	i=n-1;
	j=1;

	l_i = findallexpr(i);
	l_j = findallexpr(j);
	for(vsci::iterator it1 = l_i.begin();it1< l_i.end();it1++)
	{
		for(vsci::iterator it2=l_j.begin();it2<l_j.end();it2++)
		{
			if(it1->second.first != 'A')
				res.push_back(make_pair(it1->first+"+"+it2->first,make_pair('A',it1->second.second+it2->second.second)));
		}
	}

	for(int i=2;i<=(int)sqrt(n);i++)
	{
		if(n%i==0)
		{
			j=n/i;
			vsci l_i = findallexpr(i);
			vsci l_j = findallexpr(j);

			for(vsci::iterator it1 = l_i.begin();it1< l_i.end();it1++)
			{
				for(vsci::iterator it2=l_j.begin();it2<l_j.end();it2++)
				{
					pair<string, pair<char, int> > temp1 = *it1;
					pair<string, pair<char, int> > temp2 = *it2;
					if(temp1.second.first == 'A')
						temp1.first = "(" + temp1.first + ")";
					if(temp2.second.first == 'A')
						temp2.first = "(" + temp2.first + ")";
					res.push_back(make_pair(temp1.first+"*"+temp2.first,make_pair('M',it1->second.second+it2->second.second)));
				}
			}
		}
	}
	return res;
}

void printallexpr(vsci v, int n)
{
	set<string> s;
	for(int i=0;i<v.size();i++)
	{
		s.insert(v[i].first);
	}
	cout << n;
	for(set<string>::iterator it=s.begin();it<s.end();it++)
	{
		cout << "  = " << *it << endl;
	}
	cout << "... " << v.size() << " expressions" << endl;
}

vsci sort_list(vsci v, int n)
{
	vsci res = v;
	pair<string, pair<char, int> > temp;

	// for sorting according to the number of ones in the expr 
	for(vsci::iterator it1=v.begin();it1<v.end();it1++)
	{
		for(vsci::iterator it2= it1+1;it2<v.end();it2++)
		{
			if(it1->second.second < it2->second.second)
			{
				temp = *it1;
				*it1 = *it2;
				*it2 = temp;
			}
		}
	}

	// for sorting among same number of ones according to the length of expr
	for(vsci::iterator it1=v.begin();it1<v.end();it1++)
	{
		for(vsci::iterator it2= it1+1;it2<v.end();it2++)
		{
			if(it1->second.second == it2->second.second)
			{
				if(it1->first.size()<it2->first.size())
				{
					temp = *it1;
					*it1 = *it2;
					*it2 = temp;
				}
			}
		}
	}
	return res;
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;

	vsci v = findallexpr(n);
	cout << "+++ Before sorting" << endl;
	printallexpr(v, n);

	cout << endl;
	vsci v_sorted = sort_list(v, n);
	cout << "+++ After sorting" << endl;
	printallexpr(v_sorted, n);
}