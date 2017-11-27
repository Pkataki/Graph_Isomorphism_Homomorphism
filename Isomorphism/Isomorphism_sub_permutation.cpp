#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> >v,v2;
map<int, int> mapa;
vector<int> v1[100];

bool A[1000][1000];
bool B[1000][1000];
int length_graph_A;
int length_graph_B;

/*vetor e mapa para armazenar o grau de cada vértice dos grafos A e B*/
vector<int>deg_graphA(1000,0);
map<int,int>degree_graphA;
map<int,int>degree_graphB;
vector<int>deg_graphB(1000,0);
/*Função que testa se os grafos A e B são isomorfos*/
bool test_isomorphic(vector<int>permut)
{

	for(int i = 0; i < length_graph_A; i++)
	{
		for(int j = 0; j < length_graph_B; j++)
		{
			if(A[v2[i].second][v2[j].second] != B[permut[i]][permut[j]])
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


vector<int>  findPermutation(int n, long long k)
{
	vector<int> numbers(n);
	int indices[n];
	memset(indices,0,sizeof(indices));
	//memset(numbers,0,sizeof(numbers));
    
    // initialise the numbers 1, 2, 3...
    for (long long i = 0; i < n; i++)
    	numbers[i] = i ;
    
    long long divisor = 1;
    for (long long place = 1; place <= n; place++)
    {
    	if((k / divisor) == 0LL)
    		break;	// all the remaining indices will be zero
    		
    	// compute the index at that place:
    	indices[n-place] = (k / divisor) % place;
    	divisor *= place;
    }
    
    // permute the numbers array according to the indices:
	for (int i = 0; i < n; i++)
    {
    	long long index = indices[i] + i;
    	// take the element at index and place it at i, moving the rest up
    	if(index != i)
    	{
    		long long temp = numbers[index];
    		for(int j = index; j > i; j--)
    		   numbers[j] = numbers[j-1];
    		numbers[i] = temp;
    	}
    	
    }
	return numbers;
}

long long factorial(int x)
{
	long long aux = (long long)x;
	long long ans = 1;
	for(long long i = 2; i <= aux; i++)
	{
		ans *= i;
	}
	return ans;
}
bool found; 


void solve(int depth, vector< vector<int> > sub_permut, int cont)
{
	if(depth == cont)
	{
		vector<int> permut;
		for(int i = 0; i < cont; i++)
		{
			for(int j = 0; j < sub_permut[i].size(); j++)
			{
				permut.push_back(sub_permut[i][j]);
			}
		}
		if(test_isomorphic(permut))
		{

			found = 1;
			cout << "Os grafos A e B são isomorfos\n";
			exit(0);
		}
		return;
	}
	long long fat = factorial(v1[depth].size());
	vector<int> p;
	vector<int>aux(v1[depth].size());
	for(long long  k = 0; k < fat; k++)
	{
		p = findPermutation(v1[depth].size(), k);
		for(int j = 0; j < v1[depth].size(); j++)
		{
			aux[j] = v1[depth][p[j]];
		}
		sub_permut[depth] = aux;
		solve(depth+1, sub_permut, cont);
	}
}


int separate()
{
	
	sort(v.begin(), v.end());
	int cont = 0;
	int idx = 0;
	long long num_permut = 1;
	for (map<int,int>::iterator it = mapa.begin(); it != mapa.end(); ++it)
	{
		cout << "grupo de grau " << it->first << " tamanho do grupo: " << it->second << '\n'; 
		for(int i = 0; i < it->second; i++)
		{
			v1[cont].push_back(v[idx].second);
	
			idx++;
		}
		num_permut *= factorial(it->second);		
		cont++;
	}
	cout << "O número de permutações que serão geradas é: " << num_permut << '\n';
	return cont;
}

int main()
{
	read_graphA();
	read_graphB();
	mapa.clear();
	if(!have_same_length())
	{
		cout << "Não são isomorfos pois tem os grafos tem o número de vértices diferentes\n";
		return 0;
	}
	
	
	have_vertexes_degree_equals();


	v = vector<pair<int,int> >(length_graph_B);
	v2 = vector<pair<int,int> >(length_graph_B);
	for(int i = 0;i < length_graph_B; i++)
	{

		v[i].second = i;

		v[i].first = degree_graphB[i];

		v2[i].second = i;

		v2[i].first = degree_graphA[i];

		mapa[v[i].first]++;
	}
	sort(v2.begin(),v2.end());

	int cont = separate();

	vector<vector<int> >aux(cont);
	found = 0; 

	cout << "iniciando processamento\n";
	

	solve(0, aux, cont);
	if(!found)
		cout << "Nao sao isomorfos\n";
	return 0;
}
