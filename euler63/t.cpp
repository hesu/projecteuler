/*
 	Problem 63 - Powerful digit counts
*/
	
#include <iostream>
#include <ctime>
#include <math.h>
#include <string.h>
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
		bool made = false;
		for(int j=1; ; j++)
		{
			unsigned long int powed = pow(i, j);
			int digitlen = log10( powed) + 1;
			if (digitlen == j) {
					cout << "i=" << i << " j=" << j << " digitlen=" << digitlen << " powed=" << powed << endl;
					cnt++;
					made = true;
			}

			// TODO j finite condition
			//if( made && powed > 10) {
			if( powed > 10) {
				unsigned long int left = powed/10;
				if( j >= 10 && log10(left * i)+1 < digitlen) {
					cout << "powed=" << powed << " left*i=" << left*i << " digitlen=" << digitlen << endl;
					break;
				}
			}
		}
		i++;
	}

	cout << "cnt=" << cnt << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
