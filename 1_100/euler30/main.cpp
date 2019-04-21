/*
 	Problem 30 - Digit fifth powers 
*/

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	long long int sum_of_fifth_powers = 0;
	char num[8] = {0,};
	cout << "sum_of_fifth_powers=" << sum_of_fifth_powers << endl;
	for(int i=0; i<300000; i++)
	{
		sprintf(num, "%d", i);
		int n = 0;
		for(int j=0; j<6; j++)
		{
			if (num[j] == 0) continue;
			n+= pow( (int)(num[j] - '0'), 5);
		}
		if( i == n) {
			cout << "same! i=" << i << endl;
			sum_of_fifth_powers += i;		
		} 
	}
	cout << "sum_of_fifth_powers=" << sum_of_fifth_powers << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

