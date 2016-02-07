/*
	 Problem 52 - Permuted multiples 
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

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
	int buf[MAX] = {0,};

	while(true)
	{
		int ntoi = toint( n, MAX);
		int d = int(log10(ntoi)+1);
		int ratio = (ntoi/(pow(10, d-2)));
		memcpy( buf, n, sizeof(int)*MAX);
		if( ratio < 18 && ntoi > 99) {
			cout << "n=" << ntoi << ", d=" << d << endl;
			std::sort( n, n+d);

			bool foundMultiples[6] = {0,};
			do{
				int converted = toint( n, MAX);
				int left = converted%ntoi;
				if( left == 0) {
					int q = converted/ntoi;
					if( q <=6 && q > 0) {
						foundMultiples[q-1] = true;
					}
				}
			} while( std::next_permutation(n, n+d));

			bool found = true;
			for(int i=0; i<6; i++)
			{
				if (foundMultiples[i] == false) {
					found = false;
					break;
				}
			}

			if( found) {
				cout << "ntoi =" << ntoi << endl;
				break;
			}

			//cout << "ntoi=" << ntoi << " ratio=" << ratio << endl;
		}
		memcpy( n, buf, sizeof(int)*MAX);
		inc( n, MAX);	
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

