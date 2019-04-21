/*
  Problem 145 - How many reversible numbers are there below one-billion?
*/

#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

#define MAX 1000000000

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int sol = 0;
  for(unsigned long long int i=1;i<MAX;i++)
  {
    if( i % 100000 == 0) cout << "i=" << i << endl;
    if( i % 10 == 0) continue;

    char n[1024];
    sprintf(n, "%lld", i);
    int len = strlen( n);

    bool is = true;
    int carry = 0;
    for(int j=len-1;j>=0;j--)
    {
      int rev = (len-j-1);
      int digit = n[j] - '0' + n[rev] - '0' + carry;
      if (digit % 2 == 0) { is =false; break;}

      if( digit >= 10) {
        carry = digit/10;
        if( carry >=2) { cout << "abnormal! carry=" << carry <<" i=" << i << endl; }
      } else {
        carry = 0;
      }
    }

    if( is) sol++;
  }

  cout << "sol=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
