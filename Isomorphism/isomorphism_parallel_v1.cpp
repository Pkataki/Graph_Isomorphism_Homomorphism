#include<bits/stdc++.h>
using namespace std;
/*matrizes de adjacência dos grafos A e B*/
bool A[1000][1000];
bool B[1000][1000];
int length_graph_A;
int length_graph_B;
bool ok;
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

void findPermutation(int n, long long k)
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
  
  	#pragma omp critical
	{
   		ok = test_isomorphic(numbers);
    }
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





main()
{
	const clock_t begin_time = clock();
	
	read_graphB();
	read_graphA();
	cout << "Iniciando o processamento\n";


	vector<int>v(length_graph_B);
	for(int i = 0; i < length_graph_B; i++)
	{
		v[i] = i;
	}
	bool are_isomorphiscs;
	long long factorial = (long long)length_graph_B;
	cout << factorial << " \n";
	vector<int> permut; 
	bool found = 0;

	ok = 0;
	long long ans = 1LL;
	for(long long i = 2LL; i <= factorial; i++)
	{
		ans *= i;
	}
	cout << ans << '\n';
	
	#pragma omp parallel for
	for(long long i = 0; i < ans; i++)
	{
		if(ok)
			continue;
		findPermutation(length_graph_B, i);
	}
	if(!ok )
		cout << "A e B não são isomorfos\n";	
	else 
		cout << "Sao isomorfos\n";
	cout << "Tempo: "<< fixed << setprecision(5)<<  float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " segundos.\n";
}
