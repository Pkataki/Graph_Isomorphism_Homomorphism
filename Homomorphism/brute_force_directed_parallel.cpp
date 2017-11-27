#include <bits/stdc++.h>
using namespace std;
int ans = 0;
void gera_permutacao(int init, int qt, int usa_qt)
{
	int temp;
	int numbers = qt;
	int a[numbers], upto = usa_qt, temp2;
	for( temp2 = 1 ; temp2 <= numbers; temp2++)
	{
		a[temp2]=init;
	}
	a[numbers]=0;
	temp = numbers, temp2;
	while(1)
	{
		if(a[temp] == upto)
		{
			temp--;
			if(temp == 0)
				break;
		}
		else
		{
			a[temp]++;
			while(temp < numbers)
			{
				temp++;
				a[temp] = init;

			}
			#pragma omp critical
			{
			    ans++;
			}
		}
	}
}
int main()
{	
	int n = 5;
	#pragma omp parallel for
	for(int i = 1; i < n; i++)
		gera_permutacao(i,n,n);

	cout << ans << '\n';
	return 0;
}
