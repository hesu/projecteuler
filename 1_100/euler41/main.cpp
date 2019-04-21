/*
 	Problem 41 - Pandigital prime
*/
	
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

int largest = 0; // solution

bool isprime( int n)
{
  if( n == 2) return true;

  int s = sqrt( n) + 1;
  for(int i=s; i>1; i--)
  {
    if (n%i ==0) { return false; }
  }

  return true;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	for(int i=9; i>=1; i--) 
	{
		int nums[9] = {0,};

		int sumcheck = 0;
		for(int j=0; j<i; j++)
		{
			nums[j] = i-j;
			sumcheck += nums[j];
		}

		if (sumcheck%3 == 0) continue;

		std::sort( nums, nums+i);
		do {
			int pandigital = 0;
			for(int j=0; j<i; j++)
			{
				pandigital += nums[j] * pow(10, j);	
				//cout << nums[j];
			}
			cout << "pan = " << pandigital << endl;
			if( isprime( pandigital)) {
				if( largest < pandigital) {
					largest = pandigital;
				}
			}
			//cout << endl;
		} while( std::next_permutation( nums, nums+i));

		if (largest != 0) {
			break;
		}
	}

	cout << endl << "largest pandigital Num = " << largest << endl;
	
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
