/*
 	Problem 97 - Large non-Mersenne prime
*/
	
#include <iostream>
#include <ctime>
#include "BigInt.h"

using namespace std;

int MAX = 7830457;

int main(int argc, char** argv)
{
	clock_t begin = clock();

	BigInt n = BigInt(2);
	for(int i=1; i<MAX; i++)
	{
		BigInt mul = BigInt(2);
		n = n.multiply( mul, 10);
	}

	BigInt mul2 = BigInt(28433);
	BigInt one = BigInt(1);
	n = mul2 * n + one;

	string number = n.toString();
	cout << "number=" << number << endl;

	if (number.size() >= 10) cout << "solution=" << number.substr( number.size()-10, number.size()) << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
