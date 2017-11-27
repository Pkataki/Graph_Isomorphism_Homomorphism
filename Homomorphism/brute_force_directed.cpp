#include <bits/stdc++.h>
using namespace std;

bitset<100> used[100];


int n ;

vector <int> graph[100];
vector <int> reverse_graph[100];

bool testa_coloracao(int *cor)
{
	for(int i = 1; i <= n; i++)
	{
		used[i].reset();
	}
	for(int v = 1; v <= n ; v++)
	{	
		//cout << "\nno atual: " << v << endl;
		for(int i = 0 ; i < graph[v].size(); i++)
		{
			
			int u = graph[v][i];
			//cout << " no do graph: " << u << endl;
			if(cor[v] == cor[u])
			{
				//cout << v << " e " << u << " tem a mesma cor\n";
				return false;
			}
			if(used[cor[v]].test(cor[u]) == 1)
			{
				//cout << "ja usei no used graph as cores " << cor[v] << ' ' << cor[u] << '\n';
				return false;
			}
			used[cor[v]][cor[u]] = 1;
		}
	
	}
	return true;
}
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int b;
			cin >> b;
			if(b)
			{
				graph[i].push_back(j);
				//reverse_graph[i].push_back(j);
			}
		}
	}

	int temp;
	int numbers = n;
	int a[numbers], upto = n, temp2;
	int result[numbers];
	for( temp2 = 1 ; temp2 <= numbers; temp2++){
		a[temp2]=1;
	}
	int num_min = INT_MAX;
	a[numbers]=0;
	temp=numbers, temp2;
	while(1)
	{
		if(a[temp]==upto)
		{
			temp--;
			if(temp==0)
				break;
		}
		else
		{
			a[temp]++;
			while(temp<numbers)
			{
				temp++;
				a[temp]=1;
			}
 			
			if(testa_coloracao(a))
			{
				
				//cout << "entrei\n";
				
				set<int>s;
				for(int i = 1; i <= n; i++) s.insert(a[i]); 
				if(num_min > s.size())
				{
					num_min = s.size();
					for(int i = 1; i <= n; i++)
						result[i] = a[i];
				}
			}
		}
	}
	
	
	cout << "colorivel com " << num_min << "\n";
	for(int i = 1; i <=n ;i++)
	{
		cout << i << " -> "<< result[i] << '\n';
	}
	//cout << "deu ruim " << '\n';
	return 0;
}

