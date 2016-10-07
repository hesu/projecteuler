/*
  Problem 75 - Singular integer right triangles 
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;


#define MAX 1500000

int main(int argc, char** argv)
{
  clock_t begin = clock();

  for(int i=1; i<= (MAX/2); i++)
  {
    for(int j=i+1; j<=(MAX/2); j++)
    {
      double sqrted = sqrt( pow(i,2) + pow(j,2));
      if( sqrted == ceil(sqrted)) {
        cout << "find! a=" << i << " b=" << j << " c=" << sqrted << endl;
      }
      
    }
  }

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
