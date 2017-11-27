#include<bits/stdc++.h>
using namespace std;
/*matriz de adjacencia*/
int mat[1000][1000];

/*vetor com as cores finais do grafo*/
vector<int>result;

/*numero minimo de cores*/
int num_min_colors;

/*Função que verifica se eu posso colorir o vertice vertex com a cor color_vertex*/
bool can_color(vector<int>colors, int color_vertex, int vertex, int num_vertex)
{
	for(int i = 0; i < num_vertex; i++)
	{
		if(mat[vertex][i])
		{
			if(colors[i] == color_vertex)
				return false;
		}	
	}
	return true;
}

/*função que colore o grafo*/
void coloring_graph(vector<int>colors, int depth, int vertex, int num_vertex)
{
	if(depth == num_vertex)
	{
		bitset<100>b;
		
		for(int i = 0; i < num_vertex; i++)
		{
			b[colors[i]] = 1;	
		}
		/*verifica se o estado atual é melhor do que o melhor estado ate agora*/
		if((int) b.count() < num_min_colors)
		{
			result = colors;
			num_min_colors = (int)(b.count());
		}
		return;
	}
	/*colore os vizinhos de vertex*/
	for(int i = 0; i < num_vertex; i++)
	{
		if(mat[vertex][i] && colors[i] == -1)
		{
			for(int color = 1; color <= num_vertex; color++)
			{
				if(can_color(colors,color,i,num_vertex))
				{
					colors[i] = color;
					coloring_graph(colors, depth+1, i, num_vertex);
					colors[i] = -1;
				}
			}
		}
	}
}
main()
{
	int num_vertex;
	cin >> num_vertex;
	
	for(int i = 0; i < num_vertex; i++)
	{
		for(int j = 0; j < num_vertex; j++)
		{
			cin >> mat[i][j];
		}
	}
	cout << "Iniciando a coloração\n";
	
	vector<int>colors(num_vertex,-1);
	/*Colore o primeiro vertice com a cor 1*/
	colors[0] = 1;

	/*determina que o numero minimo de cores é inicialmente o numero de vertices*/
	num_min_colors = num_vertex;

	coloring_graph(colors,1,0,num_vertex);
	
	cout << "Numero minimo: " << num_min_colors << '\n';
	for(int i = 0; i < num_vertex; i++)
	{
		cout << "vertice: " << i << " -> cor : " << result[i] << '\n';
	}

	bool h_graph[num_min_colors + 1][num_min_colors+ 1];
		
	vector<vector<int> > col(num_min_colors+1);
	memset(h_graph,0,sizeof(h_graph));
	
	for(int color = 1; color <= num_min_colors; color++)
	{
		for(int i = 0; i < num_vertex; i++)
		{
			if(result[i] == color)
			{
				col[color].push_back(i);
				vector<int>colored_vertexes;
				for(int j = 0; j < num_vertex; j++)
				{
					if(mat[i][j])	
					{
						colored_vertexes.push_back(result[j]);
					}
				}
				for(int j = 0; j < colored_vertexes.size(); j++)
				{
					h_graph[color][colored_vertexes[j]] = 1;
				}
			}
		}	
	}
	cout << "Homomorphic graph:\n";
	for(int i = 1; i <= num_min_colors; i++)
	{
		for(int j = 1; j <= num_min_colors; j++)
		{
			cout << h_graph[i][j] << ' ';
		}
		cout << '\n';
	}
	for(int i = 1; i <= num_min_colors; i++)
	{
		cout << "color:  " << i  << '\n';
		for(int j = 0 ;j < col[i].size(); j++)
			cout << col[i][j] << ' ';
		cout << '\n';
	}
	cout << '\n';
	
}
