/*
 	Problem 206 - Concealed Square
*/

#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

bool isConcealedSquare( unsigned long int n)
{
  char buf[100] = {0,};
  sprintf( buf, "%lu", n*n);

  if( strlen( buf) == 19) {
    for(int i=0; i<=9; i++)
    {
      if( buf[i*2] != i+1 + '0') return false;
    }
    return true;
  }
  return false;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  int n = 1000000000;
  while( !isConcealedSquare( n * 10)) { 
    cout << "n=" << n * 10 << endl; 
    n++;
  }
  cout << "solved n=" << n * 10<< endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

