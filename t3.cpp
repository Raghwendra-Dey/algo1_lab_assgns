/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A3.pdf
*/

#include <bits/stdc++.h>

#define point pair<double, double>
#define line pair<int, pair<double, double> >

using namespace std;

pair<point, line> find_inter(line l1, line l2)
{
	pair<point, line> ans;
	ans.second = l1;
	ans.first.first = (l1.second.second - l2.second.second) / (l2.second.first - l1.second.first);
	ans.first.second = (l1.second.first * ans.first.first) + l1.second.second;
	return ans;
}

void print_res(vector<pair<pair<point, point>, line> > res)
{
	cout << "Line\t" << res[0].second.first << ": From MINUS_INFINITY to (" << res[0].first.second.first << "," << res[0].first.second.second << ")" << endl; 
	for(int i=1;i<res.size()-1;i++)
	{
		cout << "Line\t" << res[i].second.first << ": From (" << res[i].first.first.first << "," << res[i].first.first.second << ") to (" << res[i].first.second.first << "," << res[i].first.second.second << ")" << endl;
	}
	cout << "Line\t" << res[res.size()-1].second.first << ": From (" << res[res.size()-1].first.first.first << "," << res[res.size()-1].first.first.second << ") to PLUS_INFINITY" << endl;
}

void method1(vector<line> l_bundle)
{
	double min_slope = l_bundle[0].second.first;
	int min_slope_idx = 0;

	for(int i=0;i<l_bundle.size();i++)
	{
		if(l_bundle[i].second.first < min_slope)
		{
			min_slope = l_bundle[i].second.first;
			min_slope_idx = i;
		}
	}

	vector<pair<pair<point, point>, line> > res;

	// initialize with the min slope line
	point Q = make_pair(-INFINITY, -INFINITY);
	line K = l_bundle[min_slope_idx];
	bool vis[l_bundle.size()] = {0};
	vis[K.first] = 1;

	while(1)
	{
		vector<pair<point, line> > inter_pts;

		for(int i=0;i<l_bundle.size();i++)
		{
			if(!vis[l_bundle[i].first])
			{
				pair<point, line> inter = find_inter(l_bundle[i], K);
				if(inter.first.first > Q.first)
					inter_pts.push_back(inter);
			}
		}
		if(inter_pts.size() == 0)
		{
			pair<pair<point, point>, line> ans;
			ans.first.first = Q;
			ans.first.second = make_pair(INFINITY, INFINITY);
			ans.second = K;
			res.push_back(ans);
			break;
		}

		pair<point, line> min_inter_pt = inter_pts[0];

		for(int i=0;i<inter_pts.size();i++)
		{
			if(min_inter_pt.first.first > inter_pts[i].first.first)
				min_inter_pt = inter_pts[i];
		}

		pair<pair<point, point>, line> ans;
		ans.first.first = Q;
		ans.first.second = min_inter_pt.first;
		ans.second = K;

		res.push_back(ans);

		Q = min_inter_pt.first;
		K = min_inter_pt.second;
		vis[K.first] = 1;
	}

	print_res(res);

}

vector<line> merge_sort(vector<line> l_bundle, int st_idx, int ed_idx)
{
	vector<line> res;

	int len = (ed_idx - st_idx);
	if(len == 2)
	{
		if(l_bundle[st_idx].second.first < l_bundle[st_idx+1].second.first)
		{
			res.push_back(l_bundle[st_idx]);
			res.push_back(l_bundle[st_idx+1]);
		}
		else
		{
			res.push_back(l_bundle[st_idx+1]);
			res.push_back(l_bundle[st_idx]);
		}
		return res;
	}
	if(len == 1)
	{
		res.push_back(l_bundle[st_idx]);
		return res;
	}
	else if(len == 0)
	{
		return res;
	}

	vector<line> l1 = merge_sort(l_bundle, st_idx, st_idx+(len/2)+1);
	vector<line> l2 = merge_sort(l_bundle, st_idx+(len/2)+1, ed_idx);

	int i=0,j=0,flag=0;

	while(1)
	{
		if(i == l1.size())
		{
			flag = 1;
			break;
		}
		else if(j == l2.size())
		{
			flag = 2;
			break;
		}
		else
		{
			if(l1[i].second.first < l2[j].second.first)
			{
				res.push_back(l1[i]);
				i++;
			}
			else
			{
				res.push_back(l2[j]);
				j++;
			}
		}
	}

	if(flag == 1)
	{
		while(j != l2.size())
		{
			res.push_back(l2[j]);
			j++;
		}
	}
	else if(flag == 2)
	{
		while(i != l1.size())
		{
			res.push_back(l1[i]);
			i++;
		}
	}
	return res;
}

bool lies_bet(point p1, pair<point, point > pp2)
{
	bool ans_x = 0, ans_y = 0;
	if(((p1.first) <= max(pp2.first.first, pp2.second.first))&&((p1.first) > min(pp2.first.first, pp2.second.first)))
		ans_x = 1;
	if(((p1.second) <= max(pp2.first.second, pp2.second.second))&&((p1.second) > min(pp2.first.second, pp2.second.second)))
		ans_y = 1;
	return (ans_x&ans_y);
}

void method2(vector<line> l_bundle)
{
	stack<pair<pair<point, point> , line> > res;
	res.push(make_pair(make_pair(make_pair(-INFINITY, INFINITY), make_pair(INFINITY, -INFINITY)), l_bundle[0]));

	for(int i=1;i<l_bundle.size();i++)
	{
		while(1)
		{
			if(res.empty())
			{
				cout << "empty h bsdk!!" << endl;
				break;
			}
			pair<pair<point, point> ,line> elem = res.top();
			res.pop();
			pair<point, line > inter1 = find_inter(l_bundle[i], elem.second);
			point inter = inter1.first;
			if(lies_bet(inter, elem.first))
			{
				cout << i << endl;
				res.push(make_pair(make_pair(elem.first.first, inter), elem.second));
				res.push(make_pair(make_pair(inter, make_pair(INFINITY, INFINITY)), l_bundle[i]));
				break;
			}
		}
	}

	vector<pair<pair<point, point> , line> > v(res.size());
	for(int i=v.size()-1;i>=0;i--)
	{
		pair<pair<point, point> ,line> elem = res.top();
		res.pop();
		v[i] = elem;
	}
	print_res(v);
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	vector<line> l_bundle;
	line l;
	double a, b;
	for(int i=0;i<n;i++)
	{
		l.first = i;
		cin >> a >> b;
		l.second.first = a;
		l.second.second = b;
		l_bundle.push_back(l);
	}
	cout << "+++ Lines before sorting" << endl;
	for(int i=0;i<l_bundle.size();i++)
	{
		if(l_bundle[i].second.second > 0)
			cout << "Line\t" << l_bundle[i].first << ": y =\t" << l_bundle[i].second.first << " x +" << l_bundle[i].second.second << endl;
		else
			cout << "Line\t" << l_bundle[i].first << ": y =\t" << l_bundle[i].second.first << " x " << l_bundle[i].second.second << endl;
	}

	cout << "+++ Method 1" << endl;
	method1(l_bundle);

	l_bundle = merge_sort(l_bundle, 0, l_bundle.size());

	cout << "+++ Method 2" << endl;
	method2(l_bundle);
}



/*
n=9

.4 3
-.2 9
1.12 -2.8
0 1.5
-1 12
-.4 7
-2.3076923077 15 
3.75 -35.625
.7 -3.5

*/