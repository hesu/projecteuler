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


std::map<int,int,int> all_ways;
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
//        cout << "find! a=" << i << " b=" << j << " c=" << sqrted << endl;

        int len = sqrted + i + j;
        if( len > MAX) continue;

        std::vector<int> ways = { i, j, (int)sqrted };
        sort( ways.begin(), ways.end());

        std::map<int,int,int>::iterator it = all_ways.find( ways[0], ways[1], ways[2]);
        if( it == all_ways.end()) {
          all_ways.insert( std::map<int,int,int>::value_type(ways[0], ways[1], ways[2]));
          // 이거뿐만 아니라 배수를 모두 넣어준다.
          for(int mul=2;;mul++)
          {
            int newi = i*mul;
            int newj = j*mul;
            int newsq = (int)sqrted * mul;
            if( newi + newj + newsq > MAX) continue;
            std::map<int,int,int>::iterator it2 = all_ways.find( newi, newj, newsq);
            if( it2 == all_ways.end()) { 
              all_ways.insert( std::map<int,int,int>::value_type( newi, newj, newsq));
            }
          }
        }

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

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
