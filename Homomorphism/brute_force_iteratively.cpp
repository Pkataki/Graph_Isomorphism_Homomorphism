#include <bits/stdc++.h>
using namespace std;

bitset<100> used[100];


int n ;

vector <int> graph[100];

bool testa_coloracao(int *cor)
{
	for(int i = 1; i <= n ; i++)
	{
		for(int j = 0; j < graph[i].size(); j++)
		{
			if(cor[i] == cor[graph[i][j]])
			{	
				//cout << "As cores sao iguais\n";
				return false;
			}
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
				//graph[j].push_back(i);
			}
		}
	}
	int temp;
	int numbers = n;
	int cor[numbers+2];
	int result[numbers+2];
	int upto = n, temp2;
	int num_min = n*n;
	for( temp2 = 1 ; temp2 <= numbers; temp2++)
	{
		cor[temp2] = 1;
	}
	cor[numbers+1] = 0;
	temp = numbers, temp2;
	cout << "iniciando a coloração\n";
	while(1)
	{
		if(cor[temp] == upto)
		{
			temp--;
			if(temp == 0)
				break;
		}
		else
		{
			
			cor[temp]++;
			
			while(temp < numbers)
			{
				temp++;
				cor[temp] = 1;
			}

			if(testa_coloracao(cor))
			{
				set<int>s;
				for(int i = 1; i <= n; i++) s.insert(cor[i]); 
				if(num_min > s.size())
				{
					num_min = s.size();
					for(int i = 1; i <= n; i++)
						result[i] = cor[i];
				}
				
				//return 0;
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

