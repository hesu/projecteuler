/*
 	Problem 97 - Large non-Mersenne prime
*/
	
#include <iostream>
#include <ctime>

using namespace std;

int MAX = 7830457;

int main(int argc, char** argv)
{
	clock_t begin = clock();

	unsigned long long n = 2;
	for(unsigned int i=1; i<=MAX; i++)
	{
		n = (n << 1) % 10000000000;
	}

	n *= 28433;
	n += 1;

	cout << "n=" << n << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
