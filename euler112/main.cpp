/*
 	Problem 112 - Bouncy numbers
*/

#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

bool isBouncy( int n)
{
  char buf[100] = {0,};
  sprintf( buf, "%d", n);

  bool up = false;
  bool down = false;

  for(int i=1; i<strlen(buf); i++)
  {
    int a = buf[i-1] - '0';
    int b = buf[i] - '0';

    if( up == true) {
      // check if is down
      if( a > b) return true;
    } else if( down == true) {
      // check if is up
      if( a < b) return true;
    } else {
      // check whether up or down
      if (a>b) down = true;
      else if( a<b) up = true;
    }

  }
  return false;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  int nBouncy = 0;
  int n = 1;

  while( true)
  {
    if( isBouncy( n)) { nBouncy++;}
    if( nBouncy * 100 / n == 99) break;
    n++;
  }

  cout << "n=" << n << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

