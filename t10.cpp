/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/AA.pdf
status: working fine
comments: In APSPany, i was not stopping when a node is explored thus this often
resulted in re-exploring and which in some explorations set
cost[node][goal] = PLUS_INFTY, and thus some start-goal pairs were
unexlored. solved by not exploring any pair if allready explored
and resetting any pair to again un-explored if that is not modified.
*/

#include <bits/stdc++.h>
#define PLUS_INFTY 1000000000

using namespace std;

struct graph
{
	int n;
	char **air_lines;
	int **tkt_prices;
};

struct graph init(int n)
{
	struct graph g;
	g.n = n;
	g.air_lines = (char**)malloc(g.n*sizeof(char*));
	g.tkt_prices = (int**)malloc(g.n*sizeof(int*));

	for(int i=0;i<g.n;i++)
	{
		g.air_lines[i] = (char*)malloc(g.n*sizeof(char));
		g.tkt_prices[i] = (int*)malloc(g.n*sizeof(int));
	}
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		{
			if(i==j)
			{
				g.tkt_prices[i][j] = 0;
				g.air_lines[i][j] = 's';
			}
			else
			{
				g.tkt_prices[i][j] = PLUS_INFTY;
				g.air_lines[i][j] = '-';
			}
		}
	return g;
}

int** init_costmat(int n)
{
	int** c = (int **)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		c[i] = (int *)malloc(n*sizeof(int ));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(i==j)
			{
				c[i][j] = 0;
				continue;
			}
			c[i][j] = PLUS_INFTY;
		}
	return c;
}

struct graph readgraph()
{
	int n;
	cin >> n;
	struct graph g = init(n);
	int s, d, c;
	char a;
	while(1)
	{
		cin >> s;
		if(s == -1)
			break;
		cin >> d >> c >> a;
		g.tkt_prices[s][d] = c;
		g.air_lines[s][d] = a;
	}
	return g;
}

void prngraph(struct graph g)
{
	for(int i=0;i<g.n;i++)
	{
		cout << i << "  ->  ";
		for(int j=0;j<g.n;j++)
		{
			if((g.air_lines[i][j] == '-')||(i==j))
				continue;
			cout << j << " (" << g.tkt_prices[i][j] << ", " << g.air_lines[i][j] << ")  ";
		}
		cout << endl;
	}
}

struct graph getAIgraph(struct graph g)
{
	struct graph h = init(g.n);
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			if(g.air_lines[i][j]=='a')
			{
				h.air_lines[i][j] = 'a';
				h.tkt_prices[i][j] = g.tkt_prices[i][j];
			}
		}
	}
	return h;
}

int** APSP(struct graph g)
{
	int** c = init_costmat(g.n);

	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			c[i][j] = g.tkt_prices[i][j];
		}
	}

	for(int k=0;k<g.n;k++)
	{
		for(int i=0;i<g.n;i++)
		{
			for(int j=0;j<g.n;j++)
			{
				if(c[i][j] > c[i][k] + c[k][j])
					c[i][j] = c[i][k] + c[k][j];
			}
		}
	}
	return c;
}

void prncostmat(int **c, int n)
{
	for(int i=0;i<n;i++)
		cout << "      " << i;
	cout << endl;
	for(int i=0;i<n;i++)
	{
		cout << i << "  ->  ";
		for(int j=0;j<n;j++)
		{
			if(c[i][j] >= PLUS_INFTY)
				cout << "   -   ";
			else
			{
				cout << c[i][j] << "  ";
			}
		}
		cout << endl;
	}
}

int** APSPone(struct graph g, int** c1)
{
	int** c = init_costmat(g.n);

	vector<pair<pair<int, int> , int> > non_ai_edges;

	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			if(g.air_lines[i][j] == 'n')
				non_ai_edges.push_back({{i, j}, g.tkt_prices[i][j]});
		}
	}

	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			if(c1[i][j] < PLUS_INFTY)
				c[i][j] = c1[i][j];
			else
			{
				int min_cost = c1[i][j];
				for(int e=0;e<non_ai_edges.size();e++)
				{
					int k = non_ai_edges[e].first.first;
					int l = non_ai_edges[e].first.second;
					if(c1[i][k] + non_ai_edges[e].second + c1[l][j] < min_cost)
						min_cost = c1[i][k] + non_ai_edges[e].second + c1[l][j];
				}
				c[i][j] = min_cost;
			}
		}
	}
	return c;
}

void dfsp(struct graph g, int node, int goal, int** cost, int** vis)
{
	if(vis[node][goal] == 1)
		return;
	int value = PLUS_INFTY;
	vis[node][goal] = 1;
	for(int n=0;n<g.n;n++)
	{
		if(vis[n][goal] == 0)
			dfsp(g, n, goal, cost, vis);
		else
		{
			if(cost[n][goal] + g.tkt_prices[node][n] < value)
				value = cost[n][goal] + g.tkt_prices[node][n];
		}
	}
	if(value == PLUS_INFTY)
		vis[node][goal] = 0;
	cost[node][goal] = value;
}

int** APSPany(struct graph g, int** c1)
{
	int** c = init_costmat(g.n);

	int** vis = (int**)malloc(g.n*sizeof(int*));
	for(int i=0;i<g.n;i++)
		vis[i] = (int *)malloc(g.n*sizeof(int));

	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		{
			if(c1[i][j]<PLUS_INFTY)
			{
				vis[i][j] = 1;
				c[i][j] = c1[i][j];
			}
			else
				vis[i][j] = 0;
		}

	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			dfsp(g, i, j, c, vis);
		}
	}
	return c;
}

int main()
{
	struct graph g = readgraph();
	cout << "+++ Original graph" << endl;
	prngraph(g);
	struct graph h = getAIgraph(g);
	cout << "+++ AI subgraph" << endl;
	prngraph(h);
	int** c1 = APSP(h);
	cout << "+++ Cheapest AI prices" << endl;
	prncostmat(c1, h.n);
	int** c2 = APSPone(g, c1);
	cout << "+++ Cheapest prices with at most one non-AI leg" << endl;
	prncostmat(c2, g.n);
	int** c3 = APSPany(g, c1);
	cout << "+++ Cheapest prices with any number of non-AI legs" << endl;
	prncostmat(c3, g.n);
}