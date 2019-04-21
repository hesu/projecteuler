
/*
   Special Pythagorean triplet
*/

#include <iostream>
//#include <cmath>
#include <cstring>
#include <stdio.h>
#include <string.h>

using namespace std;


bool ispyta( int a, int b, int c)
{
	return (a*a + b*b == c*c ? true:false);
}

bool sum1000( int a,int b,int c)
{
	return (a+b+c == 1000 ? true:false);
}

int main(int argc, char** argv)
{
	int a = 0;
	int b = 0;
	int c = 0;

	for(int i=1; i<1000; i++)
	{
		for( int j=1; j<1000; j++){
			for(int k=1; k<1000; k++) {
				if (ispyta(i,j,k) && sum1000(i,j,k)) {
					cout << "i=" << i << " j=" << j << " k=" << k << endl;
					a = i;
					b = j;
					c = k;
					break;
				}
			}
		}
	}

	cout << "solution=" << a*b*c << endl; 
	return 0;
}
