/*
 	Problem 76 - Counting summations
*/
	
#include <iostream>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

int countingSummations( int n)
{
  cout << "n=" << n << endl;
  if( n == 0) return 0;
  if( n <= 2) return 1;

  if( n % 2 == 0) {
    return countingSummations(n-1) + 1;
  } else {
    return countingSummations(n-1) + 2;
  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

  int n = countingSummations(100);
  cout << "summations=" << n << endl;
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
