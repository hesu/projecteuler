/*
	 Problem 50 - Consecutive prime sum 
 */
#include <iostream>
#include <ctime>
#include <map>
#include <cmath>
#include <vector>

using namespace std;

std::map<int,int> primes;
bool isprime( int n)
{
	if( n == 2) return true;
	std::map<int,int>::iterator it = primes.find(n);
	if( it != primes.end()) { return true; }

	int s = sqrt( n) + 1;
	for(int i=s; i>1; i--)
	{
		if (n%i ==0) { return false; }
	}

	primes.insert( std::map<int,int>::value_type( n, n));
	return true;
}


int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */ 
	std::vector<int> pList;
	for(int i=2; i<1000000; i++)
	{
		if( isprime(i)) {
			pList.push_back( i);
		}
	}

	std::map<int,int>::iterator it;
	int chainLength = pList.size();
	while( chainLength >= 1) {
		cout << "max chain length :" << chainLength << endl;
		for(int i=pList.size()-1; i>=chainLength; i--)
		{
			unsigned long int sum = 0;
			for(int j=i; j>=i-chainLength; j--)
			{
				sum += pList[j];
				if( sum > 1000000) { break;}
			}
			if (sum < 1000000) {
				it = primes.find(sum);
				if( it != primes.end()) { 
					cout << "found answer = " << sum << " i=" << i << " pList[i]=" << pList[i] << endl;
					goto done;
				}
			}
		}
		chainLength--;
	}

done:
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

