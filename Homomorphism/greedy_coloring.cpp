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
	/*int v,a;
	cin >> v >> a;
	while(a--)
	{
		int from,to;
		cin >> from >>to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}*/
	string s;
	int from = 0;
	bool first = 1;
	int num_graph;
	int num_vertex = 100;
	while(getline(cin,s))
	{
		istringstream iss(s);
		string aux;
		bool p_first = 0;
		//cout << "oi\n";
		//cout << "numeri de vertices " << num_vertex << '\n';
		while(iss >> aux)
		{
			//cout << aux << " //\n";
			if(aux == "Graph" || aux == "")
			{
				if(!first)
				{
					int melhor = INT_MAX;
					int cor_aux[num_vertex];
					//cout << "numero de vertices: " << num_vertex << '\n';
					for(int i = 0; i < num_vertex; i++)
					{
						for(int k = 0; k < num_vertex; k++)
							cor[k] = -1;
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
						if(melhor > val_bfs)
						{
							melhor = val_bfs;	
							for(int i = 0; i < num_vertex; i++)
								cor_aux[i] = cor[i];
						}
					}
						
					cout << "O grafo " << num_graph << " colorido com " << melhor  << " cores\n";
					cout << "As cores atribuidas aos vértices são: ";
					for(int i = 0; i < num_vertex; i++)
					{
						cout << cor_aux[i] << " ";
					}
					cout << "\n\n";
				}
				first = 0;
				for(int i = 0; i < 1000; i++)
				{
					graph[i].clear();
				}
				iss >> aux;
				if(isdigit(aux[0]))
				{
					stringstream(aux) >> num_graph;
				}
				for(int i = 0; i < 2; i++)
					iss >> aux;
				if(isdigit(aux[0]))
				{
					stringstream(aux) >> num_vertex;
				}
			//	cout << num_graph << ' ' << num_vertex << '\n';
				continue;
			}
			if(isdigit(aux[0]))
			{
				//cout << aux << " entrei\n";
				if(!p_first)
				{
					from = stoi(aux);
				//	cout << from << " ****\n";
				}
				else
				{
					graph[from].push_back(stoi(aux));
					//cout << from << " **** "<< stoi(aux)-1 << " \n";
				}
				
				p_first = 1;
			}
		}
	}
	return 0;
}
