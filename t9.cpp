/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A9.pdf
status: working fine
*/

#include <bits/stdc++.h>

using namespace std;

struct graph
{
	int num_vert;
	vector<char> col_vert;
	vector<int> vert_ids;
	vector<vector<int> > adj_list;
};

struct graph readgraph()
{
	struct graph g;
	cin >> g.num_vert;
	char c;
	for(int i=0;i<g.num_vert;i++)
	{
		cin >> c;
		g.col_vert.push_back(c);
		g.vert_ids.push_back(i);
	}
	int u, v;
	g.adj_list.resize(g.num_vert, vector<int> ());
	while(1)
	{
		cin >> u;
		if(u == -1)
			break;
		cin >> v;
		g.adj_list[u].push_back(v);
		g.adj_list[v].push_back(u);
	}
	return g;
}

void prngraph(struct graph g)
{
	for(int i=0;i<g.vert_ids.size();i++)
	{
		cout << "\t[" << g.col_vert[g.vert_ids[i]] << "]  " << g.vert_ids[i] << " ->  ";
		for(int j=0;j<g.adj_list[g.vert_ids[i]].size();j++)
		{
			cout << g.adj_list[g.vert_ids[i]][j];
			if(j!=g.adj_list[g.vert_ids[i]].size()-1)
				cout << ", ";
		}
		cout << endl;
	}
}

struct graph getcolgraph(struct graph g, char col)
{
	struct graph res;
	int count=0;
	res.adj_list.resize(g.num_vert, vector<int> ());
	res.col_vert.resize(g.num_vert);
	for(int i=0;i<g.num_vert;i++)
	{
		if(g.col_vert[i] == col)
		{
			count++;
			res.vert_ids.push_back(i);
			res.col_vert[i] = col;
			for(int j=0;j<g.adj_list[i].size();j++)
			{
				if(g.col_vert[g.adj_list[i][j]] == col)
					res.adj_list[i].push_back(g.adj_list[i][j]);
			}
		}
	}
	res.num_vert = count;
	return res;
}

void prncycle(struct graph g, int parent[], int start_node, int end_node)
{
	int curr_node = start_node;
	vector<char> colors;
	cout << "\t(";
	while(curr_node != end_node)
	{
		cout << curr_node << ", ";
		colors.push_back(g.col_vert[curr_node]);
		curr_node = parent[curr_node];
	}

	cout << curr_node << ", ";
	colors.push_back(g.col_vert[curr_node]);

	cout << "), Color: (";
	for(int i=0;i<colors.size();i++)
		cout << colors[i] << ", ";
	cout << ")" << endl;
}

void dfs(struct graph g, int node_id, int parent[], int level[], int vis[])
{
	vis[node_id] = 1;
	for(int i=0;i<g.adj_list[node_id].size();i++)
	{
		if(g.adj_list[node_id][i] == parent[node_id])
			continue;
		if((vis[g.adj_list[node_id][i]] == 1)&&(level[g.adj_list[node_id][i]] < level[node_id]))
			prncycle(g, parent, node_id, g.adj_list[node_id][i]);
		else if(vis[g.adj_list[node_id][i]] == 0)
		{
			parent[g.adj_list[node_id][i]] = node_id;
			level[g.adj_list[node_id][i]] = level[node_id] + 1;
			dfs(g, g.adj_list[node_id][i], parent, level, vis);
		}
	}
}

void multi_dfs(struct graph g, int n, int parent[])
{
	int *level = (int *)malloc(n*sizeof(int));
	int *vis = (int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		vis[i] = 0;
		parent[i] = -1;
		level[i] = -1;
	}
	for(int i=0;i<g.vert_ids.size();i++)
	{
		level[g.vert_ids[i]] = 0;
		dfs(g, g.vert_ids[i], parent, level, vis);
	}
}

struct graph getrbgraph(struct graph g, int fr[], int fb[])
{
	struct graph grb;
	grb.num_vert = g.num_vert;
	grb.col_vert = g.col_vert;
	grb.vert_ids = g.vert_ids;
	grb.adj_list.resize(g.num_vert, vector<int> ());

	for(int i=0;i<g.num_vert;i++)
	{
		if(fr[i] == -1)
			continue;
		grb.adj_list[i].push_back(fr[i]);
		grb.adj_list[fr[i]].push_back(i);
	}
	for(int i=0;i<g.num_vert;i++)
	{
		if(fb[i] == -1)
			continue;
		grb.adj_list[i].push_back(fb[i]);
		grb.adj_list[fb[i]].push_back(i);
	}
	for(int i=0;i<g.num_vert;i++)
	{
		if(g.col_vert[i] == 'r')
		{
			for(int j=0;j<g.adj_list[i].size();j++)
			{
				if(g.col_vert[g.adj_list[i][j]] == 'b')
					grb.adj_list[i].push_back(g.adj_list[i][j]);
			}
		}
		else
		{
			for(int j=0;j<g.adj_list[i].size();j++)
			{
				if(g.col_vert[g.adj_list[i][j]] == 'r')
					grb.adj_list[i].push_back(g.adj_list[i][j]);
			}
		}
	}
	return grb;
}

int main()
{
	struct graph g = readgraph();
	cout << "+++ Original graph (G)" << endl;
	prngraph(g);
	struct graph gr = getcolgraph(g, 'r');
	cout << "+++ Red subgraph (GR)" << endl;
	prngraph(gr);
	struct graph gb = getcolgraph(g, 'b');
	cout << "+++ Blue subgraph (GB)" << endl;
	prngraph(gb);
	int *fr = (int *)malloc(g.num_vert*sizeof(int));
	int *fb = (int *)malloc(g.num_vert*sizeof(int));
	cout << "+++ Red cycles" << endl;
	multi_dfs(gr, g.num_vert, fr);
	cout << "+++ Blue cycles" << endl;
	multi_dfs(gb, g.num_vert, fb);
	struct graph grb = getrbgraph(g, fr, fb);
	cout << "+++ Nonmonochromatic graph (GRB)" << endl;
	prngraph(grb);
	cout << "+++ Multi-color cycles" << endl;
	int *a = (int *)malloc(g.num_vert*sizeof(int));
	multi_dfs(grb, g.num_vert, a);
}