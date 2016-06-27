/*
 	Problem 69 - Totient maximum
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

std::map<int, std::vector<int>> notRelativePrimes;

using namespace std;

bool isRelativePrime( int src, int compare)
{
  if( compare == 1) return true;

  std::map<int, std::vector<int>>::iterator it = notRelativePrimes.find( src);
  if( it == notRelativePrimes.end()) { 
    std::vector<int> v;
    notRelativePrimes.insert( std::map<int, std::vector<int>>::value_type(src, v));
    it = notRelativePrimes.find( src);
  }

  if( std::find( it->second.begin(), it->second.end(), compare) != it->second.end()) return false;

  // else : need calculate;
  for(int i=0; i< it->second.size(); i++)
  {
    if( !isRelativePrime( compare, it->second[ i])) {
      it->second.push_back( compare);
      return false;
    }
  }

  for(int i=2; i<sqrt(src)+1; i++)
  {
    if( src%i ==0 && compare%i ==0) {
      it->second.push_back( compare);
      return false;
    }
  }

  return true;
}

int totient( int src)
{
  int n = 0;
  for(int i=1; i<src; i++)
  {
    if( isRelativePrime( src, i)) {
      n++;
    }
  }
//  cout << "src=" << src << " n=" << n << endl;
  return n;
}


int MAX = 100000;

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */

  int maxn = 0;
  double max = 0;
  for(int i=2; i<=MAX; i++)
  {
    if( i%100 == 0) { cout << "\ti=" << i << endl; }
    double t = totient( i);
    double val = (double)i / t;
    if( val > max) {
      max = val;
      maxn = i;
    }
  }

	/* end of code */
  cout << "max=" << max << endl;
  cout << "maxn=" << maxn << endl;

	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
