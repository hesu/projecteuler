/*
 	Problem 41 - Pandigital prime
*/
	
#include <iostream>
#include <ctime>
#include <vector>
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

void permutation( std::vector<int>nums, std::vector<int> now)
{
	if (nums.size() == 0) {

		int pandigitalNum = 0;
		for(int i=0;i<now.size();i++)
		{
			pandigitalNum += now[i] * pow(10, i);
		}
		if (isprime( pandigitalNum)) {
			cout << "pandigital prime : " << pandigitalNum << endl;
			if ( largest < pandigitalNum) {
				largest = pandigitalNum;
			}
		}
		return;
	}
	
	for(int i=0; i<nums.size(); i++)
	{
		std::vector<int> newone( now);
		std::vector<int> newnums( nums);
		int val = newnums[i];
		newone.push_back( val); 
		newnums.erase( newnums.begin() + i);
		permutation( newnums, newone);
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	for(int i=1; i<=9; i++) 
	{
		std::vector<int> nums;
		for(int j=1; j<=i; j++)
		{
			nums.push_back( j);
		}
		std::vector<int> now;
		permutation( nums, now);
	}

	cout << endl << "largest pandigital Num = " << largest << endl;
	
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
