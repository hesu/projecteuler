/*
 	Problem 206 - Concealed Square
*/

#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

bool isConcealedSquare( unsigned long long int n)
{
  char buf[100] = {0,};
  sprintf( buf, "%llu", n);

  if( strlen( buf) == 19) {
    cout << "try n*n=" << n << " buf=" << buf << endl;
    int cnt=1;
    for(int i=0; i<=18; i++)
    {
      if( i%2 == 0 && cnt <= 9) {
        if (buf[i] - '0' != cnt) return false;
        cnt++;
      }
    }
    cout << "find : ";
    return true;
  }
  return false;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */
  unsigned long long int n = 1000 * 1000 * 10;
  while( true) {
    if( isConcealedSquare( n*n)) break;

    char buf[100] = {0,}; sprintf( buf, "%llu", n*n);
    if( strlen(buf) > 19) { cout << "over.." << endl; break; }
    n+=10;
  }
  cout << "solved n=" << n << " for sqaure=" << n*n << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
