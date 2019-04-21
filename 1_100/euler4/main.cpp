
/*
   A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

   Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <iostream>
#include <cmath>
#include <cstring>

#include <stdio.h>

using namespace std;
bool is_palidromic(int n)
{
	
	char cs;
	char ce;
	char buf[1024] = {0,};

	sprintf( buf, "%d", n);	
	//cout << "buf=" << buf << endl;

	int len = strlen(buf);
	for(int i=0; i<len; i++)
	{
		cs = buf[i];
		ce = buf[ len-i-1];
		//cout << "s:" << cs << " e:" << ce << endl;

		if( cs != ce){
			return false;
		}	
	}

	return true;
}

int main(int argc, char** argv)
{

	int max= 0;
	for( int i=999; i>100; i--) {
		for( int j = 999; j > 100; j--) {
			bool b = is_palidromic( i*j);
			if( b && max< i*j) {
				max = i*j;
			}
		}
	}
	cout << "max = " << max<< endl;
	return 0;
}
