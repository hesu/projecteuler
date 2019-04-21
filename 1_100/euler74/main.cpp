/*
 	Problem 74 - Digit factorial chains
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int factorial( int n)
{
  int f = 1;
  for(int i=1; i<=n; i++) f*=i;
  return f;
}

int factorialDigitSum( int n)
{
  int ret = 0;
  char buf[1000] = {0,};
  sprintf( buf, "%d", n);
  for(int j=0; j<strlen( buf); j++) ret += factorial(buf[j] - '0');
  return ret;
}

int getChainLength( int that, std::vector<int> memo)
{
  if( std::find( memo.begin(), memo.end(), that) != memo.end()) {
    return 1;
  } 

  int next = factorialDigitSum( that);
  if( std::find( memo.begin(), memo.end(), next) != memo.end()) {
    return 1;
  } else {
    memo.push_back( that);
    return 1+getChainLength( next, memo);
  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */

int howmany = 0;
  for(int i=1; i<10000*100; i++)
  {
    std::vector<int> memo;
    int chainLength = getChainLength( i, memo);

    if( chainLength == 60 ) {
      cout << "find : i=" << i << endl;
      howmany++;
    }
  }

  cout << "howmany=" << howmany << endl;

	/* end of code */
	
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
