/*
	Problem 34 - Digit factorials
*/

#include <iostream>
#include <ctime>
#include <map>
#include <stdio.h>

using namespace std;

std::map<int,int> fmap;
int factorial( int n)
{
	std::map<int,int>::iterator it = fmap.find(n);
	if( it != fmap.end()) { return it->second; }

	int f = 1;
	for(int i=n; i>0; i--) { f *= i; }
	fmap.insert( std::map<int,int>::value_type( n, f));
	return f;
}

int digit_sum_factorial(char* str, int size)
{
	int sum = 0;
	for(int i=0; i<size; i++) 
	{
		if (str[i] != 0) {sum += factorial(str[i] - '0'); }
	}
	return sum;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	int sum = 0;

	int max = 200 * 10000;
	for(int i=3; i<=max; i++)
	{
		char buf[8] = {0,};
		sprintf( buf, "%d", i);
		int dsf = digit_sum_factorial( buf, 8);

		if (i == dsf) {
			cout << "find : " << i << ", buf=" << buf << endl;
			sum += dsf;
		}
	}

	cout << "sum=" << sum << endl;
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
