#include<bits/stdc++.h>
using namespace std;
/*matrizes de adjacência dos grafos A e B*/
bool A[10][10];
bool B[10][10];
int length_graph_A;
int length_graph_B;

/*vetor e mapa para armazenar o grau de cada vértice dos grafos A e B*/
vector<int>deg_graphA(1000,0);
map<int,int>degree_graphA;
map<int,int>degree_graphB;
vector<int>deg_graphB(1000,0);

/*Função que testa se os grafos A e B são isomorfos*/
bool test_isomorphic(vector<int>v)
{
	
	for(int i = 0; i < length_graph_A; i++)
	{
		for(int j = 0; j < length_graph_B; j++)
		{
			if(A[i][j] != B[v[i]][v[j]])
			{
				return false;
			}
		}
	}
	return true;
}
/*Função para ler a matriz de adjacência do grafo A do arquivo*/
void read_graphA()
{
	ifstream graphA ("graphA.txt");
	string line;
	bool first = 1;
	int lin = 0;
	if(graphA.is_open())
	{
		while(getline(graphA,line))
		{
			if(first)
			{
				length_graph_A = stoi(line);	
				first = 0;
			}
			else
			{
				int column = 0;
				for(int i = 0; line[i] ;i++)
				{
					if(isdigit(line[i]))
					{
						A[lin][column] = line[i] - '0';
						column++;
					}
				}
				lin++;
			}
		}
	}
	else
	{
		cout << "Unable to open file\n";
		exit(0);
	}
}
/*Função para ler a matriz de adjacência do grafo B do arquivo*/
void read_graphB()
{
	ifstream graphB ("graphB.txt");
	string line;
	bool first = 1;
	int lin = 0;
	if(graphB.is_open())
	{
		while(getline(graphB,line))
		{
			if(first)
			{
				length_graph_B = stoi(line);	
				first = 0;
			}
			else
			{
				int column = 0;
				for(int i = 0; line[i] ;i++)
				{
					if(isdigit(line[i]))
					{
						B[lin][column] = line[i] - '0';
						column++;
					}
				}
				lin++;
			}
		}
	}
	else
	{
		cout << "Unable to open file\n";
		exit(0);
	}
}
/*Função para verificar se os grafos tem o mesmo tamanho.*/
bool have_same_length()
{
	return (length_graph_A == length_graph_B);
}
/*Função para verificar se os graus de todos os vértices do grafo A são iguais ao do grafo B*/
bool have_vertexes_degree_equals()
{
	deg_graphA = vector<int>(length_graph_B);
	deg_graphB = vector<int>(length_graph_A);
	
	for(int i = 0; i < length_graph_A; i++)
	{
		for(int j = 0; j < length_graph_A; j++)
			deg_graphA[i] += A[i][j];
		degree_graphA[i] = deg_graphA[i];
	}
	for(int i = 0; i < length_graph_B; i++)
	{
		for(int j = 0; j < length_graph_B; j++)
			deg_graphB[i] += B[i][j];
		degree_graphB[i] = deg_graphB[i];
	}
	
	sort(deg_graphA.begin(), deg_graphA.end());
	
	sort(deg_graphB.begin(), deg_graphB.end());
	
	return (deg_graphB == deg_graphA);
}
void complete(bool mat[][10],int mask, int d)
{

			for(int i = 0; i < d; i++)
			{
				if(i <= 2)
				{
					if(mask & (1 << i))
						mat[i][i+1] = 1;
					else
						mat[i+1][i] = 1;
				}
				else if(i == 3)
				{
					if(mask & (1 << i))
						mat[0][3] = 1;
					else
						mat[3][0] = 1;
				}
				else if(i == 4)
				{
					if(mask & (1 << i))
						mat[0][2] = 1;
					else
						mat[2][0] = 1;
				}
				else
				{
					if(mask & (1 << i))
						mat[1][3] = 1;
					else
						mat[3][1] = 1;
				}
			}
}
main()
{
	const clock_t begin_time = clock();
/*	
	read_graphB();
	read_graphA();
	cout << "Iniciando o processamento\n";
	if(!have_same_length())
	{
		cout << "Fim do processamento\n";
		cout << "A e B não são isomorfos, pois nao tem o mesmo número de vertices\n";
		exit(0);
	}
	if(!have_vertexes_degree_equals())
	{
		cout << "Fim do processamento\n";
		cout << "A e B não são isomorfos, pois os vértices não tem o mesmo grau\n";
		exit(0);
	}

	vector<int>v(length_graph_B);
	for(int i = 0; i < length_graph_B; i++)
		v[i] = i;
	bool are_isomorphiscs;
	
	*//*Realiza todas as permutações*/
	int f,d;
	cin >> f >> d;
	length_graph_B = length_graph_A = f;
	
	vector<int>v(length_graph_B);
	
	for(int i = 0; i < length_graph_B; i++)
		v[i] = i;
	
	bool are_isomorphiscs;
	int cont = 0;
	int aux = 0;
	for(int mask = 0; mask < (1 << d); mask++)
	{
		cont = 0;
		for(int mask1 = 0; mask1 < (1 << d); mask1++)
		{
			if(mask == mask1)
				continue;
			memset(A,0,sizeof(A));
			memset(B,0,sizeof(B));
			complete(A,mask,d);
			complete(B,mask1,d);
			do
			{
				bool have_same_degree = 1;
				are_isomorphiscs = 0;
				if(have_same_degree)
				{
					if(test_isomorphic(v))
						are_isomorphiscs = 1;
				}
				if(are_isomorphiscs)
				{
					break;
				}
			}while(next_permutation(v.begin(),v.end()));
			
			cont += are_isomorphiscs;
			
		}
		if(!cont)
			aux++;
		cout << "grafo " << mask << " --> " << cont << "\n";
	}
	cout << aux/2 << " grafos isomorfos com " << f << " vertices e " << d << " arestas\n"; 
	
	cout << "Tempo: "<< fixed << setprecision(5)<<  float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " segundos.\n";
	
}
