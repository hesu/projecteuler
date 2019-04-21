/*
  Problem 75 - Singular long long integer right triangles 
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1500000


std::map<vector<long long int>, bool> ways;
std::map<long long int,long long int> triangles;

int main(int argc, char** argv)
{
  clock_t begin = clock();
 
  int limit = sqrt(MAX/2) + 1;
  for(long long int n=1; n<=limit; n++)
  {
    for(long long int m=1; m<n; m++)
    {
      long long int a, b, c;
      a = pow(n,2)-pow(m,2);

      // b = 2nm
      b = 2 * m * n;

      // c = n^2 + m^2;
      c = pow(n,2) + pow(m,2);
    
      for(int k=1;; k++)
      {
        cout << "n=" << n << " m=" << m << " k=" << k << endl;

        long long int len = (a+b+c) * k;
        if( len > MAX) { break; }
        else {
          // if already exist continue; 
          std::vector<long long int> v = { k*a, k*b, k*c }; sort( v.begin(), v.end());
          std::map<vector<long long int>,bool>::iterator vit = ways.find( v);
         
          if( vit != ways.end()) continue;
          ways.insert( map<vector<long long int>, bool>::value_type(v, true));
          // increase rectangle counter;
          std::map<long long int,long long int>::iterator mit = triangles.find((long long int)len);
          if( mit != triangles.end()) {
            (mit->second)++;
          } else {
            triangles.insert( std::map<long long int,long long int>::value_type(len, 1));
          }
        }

      }

      if( a+b+c > MAX) break;
    }
//     cout << "!!!!!!!!!!! m=" << m  << endl;
  }

  cout << "try to get solution.." << endl;
  long long int sol = 0;
  for(std::map<long long int,long long int>::iterator it=triangles.begin(); it != triangles.end(); it++)
  {
    if( it->second == 1) {
      //cout << it->first << " has singular long long integer right triangle!" << endl;
      sol++;
    } else {
//      cout << "it->first=" << it->first << " has right triangle=" << it->second << endl;
    }
  }

  cout << "solution=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
