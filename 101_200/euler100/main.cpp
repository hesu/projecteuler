/*
 	Problem 100 - Arranged probability
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

#define BIG 1000000000000

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
  unsigned int a = 1;
  unsigned int b = 1;
  bool done = false;

  while(done != true)
  {
    a++;
    while(true)
    {
      unsigned int lvalue = 2 * a * (a-1);
      unsigned int rvalue = (a+b) * (a+b-1);

      if (lvalue == rvalue)
      {
        if (a+b >= BIG)
          done = true;

        cout << "a=" << a << " , b=" << b << endl;
        break;
      }

      if (lvalue > rvalue)
        b++;
      else
        a++;
    }
  }

  cout << "LAST a=" << a << " , b=" << b << endl;
	/* end of code */
	
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
