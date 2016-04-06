/*
 	Problem 63 - Powerful digit counts
*/
	
#include <iostream>
#include <ctime>
#include <math.h>
#include <string.h>

#include "BigInt.h"

using namespace std;
int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	int cnt = 1; // 1^1
	int prev_ilen = 1;

	unsigned long int i=2;
	while( i < 10)
	{
		for(int j=1; ; j++)
		{
			BigInt powed = BigInt(1);
			for(int k=0; k<j; k++) { 
				BigInt operand(i);
				powed = powed * operand;
			}
			cout << endl;
			
			int digitlen = powed.getDigitsLen();
			if( digitlen == j) {
					cnt++;
					cout << "i=" << i << " j=" << j << " powed="; powed.print(); cout << " cnt=" << cnt << endl;
			}
			
			if( digitlen < j) {
				break;
			}

			/*
			if( digitlen >= 2) {
				BigInt left; left.copy( powed);
				left.shift(1);
				BigInt operand(i);
				left = left * operand;
				if( j >= 10 && left.getDigitsLen() < digitlen) {
					break;
				}
			} 
			*/
			
		}
		i++;
	}

	cout << "cnt=" << cnt << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
