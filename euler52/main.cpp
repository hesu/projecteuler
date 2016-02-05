/*
	 Problem 52 - Permuted multiples 
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

int toint( int n[], int size)
{
	int toi = 0;
	for(int i=0; i<size; i++)
	{
		toi += pow(10, i) * n[i];
	}
	return toi;
}

void inc( int n[], int size)
{
	n[0]++;
	for(int i=0; i<size; i++)
	{
		if(n[i] >= 10) {
			if(i+1 < size) {
				n[i+1] += n[i]/10;
			}
			n[i] = n[i]%10;
		} else {
			break;
		}
	}
}

#define MAX 10 
int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */ 
	int n[MAX] = {0,};

	while(true)
	{
		// TODO
		int ntoi = toint( n, MAX);
		int d = int(log10(ntoi)+1);

		int ratio = (ntoi/(pow(10, d-2)));
		if( ratio < 18) {
			cout << "ntoi=" << ntoi << " ratio=" << ratio << endl;
		}
		inc( n, MAX);	
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

