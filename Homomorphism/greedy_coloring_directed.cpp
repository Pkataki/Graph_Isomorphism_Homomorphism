#include <bits/stdc++.h>
using namespace std;
#define debug(s) (cout << s << endl)
int n ;

vector <int> graph[100];
vector <int> reverse_graph[100];

bitset<102> used[105];

vector<int>cor(105);

bool vis[105];

bool can_color(int vertice, int _cor)
{
//	 cout << "dentro da can_color\n";
//	 cout << "vertice " << vertice << " cor " << _cor << endl;
	for(int i = 0; i < graph[vertice].size(); i++)
	{
		int v = graph[vertice][i];
//		cout << "v: " << v << " cor[v] " << cor[v] << " used: " << used[_cor].test(cor[v]) << endl;
		if(cor[v] && (used[_cor].test(cor[v]) == 1 || cor[v] == _cor))
			return false;
			//cout << " no reverse \n";
		
	}
//	cout << "no reverse\n";
	for(int j = 0; j < reverse_graph[vertice].size(); j++)
	{
		int u  = reverse_graph[vertice][j];
//		cout << "u: " << u << " cor[u] " << cor[u] << " used: " << used[cor[u]].test(_cor) << endl;
		if(cor[u] && (_cor == cor[u] || used[cor[u]].test(_cor) == 1))
			return false;
	}
	return true;
}

int bfs(int init)
{
	queue<int>q;
	q.push(init);
	bitset<100>ans;
	bitset<100>used_colors;
	memset(vis,0,sizeof(vis));
	while(!q.empty())
	{
		int at = q.front();
		vis[at] = 1;
		q.pop();
		
		if(cor[at] )
			continue;
		used_colors.reset();
		//cout << "atual: " << at << endl;
		for(int i = 0 ; i < graph[at].size() ; i++)
		{
			int v = graph[at][i];
			//cout << v << ' ';
 			if(cor[v] != 0)
			{
				used_colors[cor[v]] = 1;
				ans[cor[v]] = 1;
			}
			else if(!vis[v])
			{
				//cout << "enfilei " << v << '\n';
				q.push(v);
			}
		}
		//cout << "\n\n\n";
		for(int i = 0 ; i < reverse_graph[at].size() ; i++)
		{
			int v = reverse_graph[at][i];
			if(cor[v] != 0)
			{
				ans[cor[v]] = 1;
			}

		}
		for(int _cor = 1; _cor <= n ;_cor++)
		{
			
			if(can_color(at,_cor))
			{
//				 cout << "sai da can_color\n";
//				 cout << " consegui com a cor " << _cor << "\n\n";
				cor[at] = _cor;
				for(int j = 0 ; j < graph[at].size(); j++)
				{	
					int v = graph[at][j];
					if(cor[v])
					{
						used[cor[at]][cor[v]] = 1;
					}
				}
				for(int j = 0 ; j < reverse_graph[at].size(); j++)
				{	
					int v = reverse_graph[at][j];
					if(cor[v])
					{
						used[cor[v]][cor[at]] = 1;
					}
				}

				ans[_cor] = 1;
				break;
			}
		}
	
	}	
	return ans.count();
}
int main()
{
	while(cin >> n)
	{
		vector<int>result(105);
		cor.clear();
		for(int i = 0 ; i <= 100 ; i++)
		{
			used[i].reset();
			graph[i].clear();
			reverse_graph[i].clear();
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				int b;
				cin >> b;
				if(b == 1)
				{
					graph[i].push_back(j);
					reverse_graph[j].push_back(i);
				}
			}
		}
		// for(int i = 1 ; i <= n ; i++)
		// {
		// 	for(int j = 0 ; j < reverse_graph[i].size(); j++)
		// 	{
		// 		cout << reverse_graph[i][j] << ' ';
		// 	}
		// 	cout << '\n';
		// }

		int ans = INT_MAX;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= 100; j++)
			{
				used[i].reset();
				cor[j] = 0;
			}	
			int aux = bfs(i);
		
			int cont = 0;
			for(int j = 1; j <= n ; j++)
			{
				cont += (cor[j] != 0);
			}
			if(cont < n)
			{

				for(int j = 1; j <= n; j++)
				{
					if(i == j)
						continue;
					int aux1 = bfs(j);
					aux = max(aux,aux1);
				}
			}
			cont = 0;
			for(int j = 1; j <= n ; j++)
			{
//				cout << j << " --> " << cor[j] << endl;
				if(cor[j] != 0) 
					cont++;
			}
//			cout << "\n\n\n";
			if(cont == n && aux < ans)
			{
				ans = aux;
				for(int i = 1; i <= n ; i++ )
					result[i] = cor[i];

			}	
		}
//		cout << "numero minimo " << ans << '\n';
//		for(int i = 1; i <= n ; i++)
//			cout << i << " --> " << result[i] << endl; 
	}
	return 0;
}

