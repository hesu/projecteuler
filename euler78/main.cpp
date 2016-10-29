/*
  Problem 78 - Coin partitions
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

#define MAX 1000000

long long int waysfor( long long int n, long long int maxd)
{
//  cout << "waysfor n=" << n << " maxd=" << maxd << endl;
  if( maxd <= 0) return 0;
  if( n == 0) return 1;
  if( n < 0) return 0;
  return waysfor(n, maxd-1) + waysfor( n-maxd, maxd);
}

map<pair<long long int,long long int>, long long int> waysmap;

long long int coin_partition( long long int n)
{
  // TODO
  long long int sum=0;
  for(long long int i=n; i>=1; i--)
  {
    if( i == 1 || i == n) sum++;
    else {
      pair<long long int,long long int> wf = make_pair( n-i, i);
      map<pair<long long int,long long int>,long long int>::iterator it = waysmap.find( wf);
      long long int val;

      if( it != waysmap.end()) {
        val = it->second;
        cout << "find second : " << val << endl;
      } else {
        val = waysfor(n-i, i);
        waysmap.insert( map<pair<long long int,long long int>,long long int>::value_type( wf, val));
      }
      sum += waysfor( n-i, i);
    }
  }
  
  return sum;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

/*
  cout << "waysfor(4, 2) = " << waysfor( 4, 2) << endl;
  cout << "waysfor(3, 2) = " << waysfor( 3, 2) << endl;
  
  cout << "waysfor(4, 1) = " << waysfor( 4, 1) << endl;
  cout << "waysfor(3, 1) = " << waysfor( 3, 1) << endl;
  cout << "waysfor(2, 1) = " << waysfor( 2, 1) << endl;

  cout << "coinpart t(1) = " << coin_partition(1) << endl;
  cout << "coinpart t(2) = " << coin_partition(2) << endl;
  cout << "coinpart t(3) = " << coin_partition(3) << endl;
  cout << "coinpart t(4) = " << coin_partition(4) << endl;
  cout << "coinpart t(5) = " << coin_partition(5) << endl;
  */

long long int sol=1;
  while(true)
  {
    //if( sol % 10000 == 0) { cout << "now n=" << sol << endl; }
    long long int par = coin_partition( sol);
    if( par<0) { cout << "overflow. break" << endl; break; }
    cout << "now n=" << sol << " << partition=" << par << endl;
    if( par >= MAX && par % MAX == 0) break;
    sol++;
  }

  cout << "sol=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
