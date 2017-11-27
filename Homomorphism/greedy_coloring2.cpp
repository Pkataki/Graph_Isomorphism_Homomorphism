#include<bits/stdc++.h>
using namespace std;
vector<int> graph[1000];
#define ull unsigned long long
int cor[1001];
bool in_queue[1001];
int bfs(int u)
{	
	ull ans = 0;
	queue<int>q;
	q.push(u);
	ull cores = 0;
	in_queue[u] = 1;
	while(!q.empty())
	{
		
		int at = q.front();
		q.pop();
		if(cor[at] != -1)
			continue;
		cores = 0LL;
		for(int i = 0; i < graph[at].size(); i++)
		{
			int v = graph[at][i];
			if(cor[v] != -1)
			{
				cores |= (1ULL << cor[v]);
			}
			else
				q.push(v);
		}
		for(int i = 0; i < 64; i++)
		{
			if(!(cores & (1ULL<< i)))
			{
				cor[at] = i;
				ans |= (1ULL << i);
				break;
			}
		}
	}

	return __builtin_popcountll(ans);
}
main()
{
	memset(cor,-1,sizeof(cor));
	
	string s,s1,s2;
	int from = 0;
	bool first = 1;
	int num_graph;
	int num_vertex;
	while(cin >> s >> s1 >> s2 >> num_vertex)
	{
		for(int i = 0; i < num_vertex; i++)
		{
			cin >> s;
			for(int j = 0; j < num_vertex; j++)
			{
				if(s[j] == '1')
				{
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
		}
		int menor = INT_MAX;
		int cor_aux[num_vertex];
		for(int i = 0; i < num_vertex; i++)
		{
			memset(cor,-1,sizeof(cor));
			memset(in_queue,0,sizeof(in_queue));
			int val_bfs = bfs(i);
			int ok = 1;
			for(int i = 0 ; i < num_vertex; i++)
			{
				if(cor[i] == -1)
				{
					ok = 0;
					break;
				}
			}
			if(!ok)
				continue;
			if(menor > val_bfs)
			{
				menor = val_bfs;	
				for(int i = 0; i < num_vertex; i++)
					cor_aux[i] = cor[i];
			}
		}
		cout << "numero de vertices: " << menor << '\n';
		for(int i = 0; i < num_vertex; i++)
		{
			cout << i << " ---> " << cor[i] << "\n";
		}
		for(int i = 0; i <= num_vertex; i++)
		{
			graph[i].clear();
		}
	}
	
	return 0;
}
