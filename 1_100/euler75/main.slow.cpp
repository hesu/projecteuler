/*
  Problem 75 - Singular integer right triangles 
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1500000
//#define MAX 48


std::map<int,int> m;

int main(int argc, char** argv)
{
  clock_t begin = clock();

  for(int i=1; i<= (MAX/2); i++)
  {
    for(int j=i+1; j<=(MAX/2); j++)
    {
      double sqrted = sqrt( pow(i,2) + pow(j,2));
      if( sqrted == ceil(sqrted)) {

        int len = sqrted + i + j;
        if( len > MAX) break;

        cout << "a=" << i << " b=" << j << "c=" << sqrted << endl;

        std::map<int,int>::iterator mit = m.find(len);
        if( mit != m.end()) {
          (mit->second)++;
        } else {
          m.insert( std::map<int,int>::value_type(len, 1));
        }
      }
      
    }
  }

  int sol = 0;
  for(std::map<int,int>::iterator it=m.begin(); it != m.end(); it++)
  {
    if( it->second == 1) {
      cout << it->first << " has singular integer right triangle!" << endl;
      sol++;
    }
  }

  cout << "solution=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
