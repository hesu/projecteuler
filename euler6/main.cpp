
/*
   Sum square difference
*/

#include <iostream>
#include <cmath>
#include <cstring>

#include <stdio.h>

using namespace std;

int snat( int n)
{
	int sum = 0;
	for(int i=0; i<=n; i++)
	{
		sum += i*i;
	}
	return sum;
}

int ssum(int n)
{
	int sum = 0;
	for( int i=0; i<=n; i++)
	{
		sum += i;
	}
	return sum*sum;
}

int main(int argc, char** argv)
{
	cout << "diff=" << ssum(100) - snat(100) << endl;
	return 0;
}
