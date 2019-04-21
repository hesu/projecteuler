/*
 	Problem 65 - Convergents of e
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <string.h>
#include "BigInt.h"

using namespace std;

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	std::vector<int> c;
	c.push_back(2);
	for(int i=1; i<35; i++)
	{
		c.push_back(1);
		c.push_back(i*2);
		c.push_back(1);
	}

	int MAX = 99;
	BigInt n;
	BigInt d;
	for(int i=MAX; i>0; i--)
	{
		if( n.getDigitsLen() == 0 && d.getDigitsLen() == 0) {  // first
			n = BigInt(1);
			d = BigInt(c[i]);
		} else {
			// intermediate
			BigInt adding = BigInt(c[i]) * d;
			BigInt in = adding + n;
			BigInt id = BigInt(d);

			// final
			n = id;
			d = in;
		}
	}

	BigInt last = n + BigInt(2) * d;
	int sum = 0;
	for(int i=0; i<last.getDigitsLen(); i++)
	{
		sum += last.getDigits()[i];
	}
	cout << "sum=" << sum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
